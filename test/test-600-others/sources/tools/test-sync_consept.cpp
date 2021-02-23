// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_SYNC_CONSEPT
#if defined(_MSC_VER) && _MSC_VER >= 1700
// #pragma message("build for msvc2010 (or older)")

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) sync_consept_##n
#include <cstdint>
#include <future>
#include <thread>

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    const size_t count_experimant = 1000000;

    volatile long value = 0;
    void loop(const bool dir, const size_t limit)
    {
        dprint(std::cout << "started: " << dir << " " << limit << std::endl);

        for (size_t i = 0; i < limit; ++i)
        {
            if (dir)
                ++value;
            else
                --value;
        }
    }

#if 0
    // asm("LOCK");
    int loop(bool dir, size_t limit)
    {
        dprint(std::cout << "started: " << inc << " " << limit << std::endl);
        for (size_t i = 0; i < limit; ++i)
        {
            if (dir)
            {
                asm("LOCK");
                ++value;
            }
            else
            {
                asm("LOCK");
                --value;
            }
        }
        return 0;
    }
#endif

#if 0
    // atomic
    int loop(bool dir, size_t limit) 
    {
        std::cout << "started: " << inc << " " << limit << std::endl;
        for (size_t i = 0; i < limit; ++i)
        {
            if (dir)
                atomic_inc32(&value);
            else
                atomic_dec32(&value);
        }
        return 0;
    }
#endif

#if 0
    // spinlock
    int loop(bool dir, size_t limit) 
    {
        std::cout << "started: " << inc << " " << limit << std::endl;
        for (size_t i = 0; i < limit; ++i) 
        {
            std::lock_guard<boost::detail::spinlock> guard(lock);
            if (dir)
                ++value;
            else
                --value;
        }
        return 0;
    }
#endif

#if 0
    // mutex
    int loop(bool dir, size_t limit) 
    {
        std::cout << "started: " << inc << " " << limit << std::endl;
        for (size_t i = 0; i < limit; ++i)
        {
            std::lock_guard<std::mutex> guard(mutex);
            if (dir)
                ++value;
            else
                --value;
        }
        return 0;
    }
#endif

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    // без синхронизации
    bool success = false;
    for (size_t i = 0; !success && i != 10; ++i)
    {
        value = 0;

        // --- два парралельных потока 
        // --- будут одновремено менять значение 
        // --- волатильной переменной

        auto f = std::async(
            std::launch::async, 
            std::bind(loop, true, 2 * count_experimant)
        );
        loop(false, count_experimant);
        f.wait();

        // --- так как нет никакой синхронизации,
        // --- то в результате должен получиться мусор
        dprint(std::cout << value << '\n');

        success = value != count_experimant;
    }
    ASSERT_TRUE(success);
}

namespace
{
    char memory[2 * 1024];
    volatile uint32_t* test = 0;
    volatile uint32_t stop = 0;
 
    void thread1() 
    {
        for (;;)
        {
            *test = 0;
            const uint32_t check = stop;
            if (check != 0)
                break;
        }
    }
 
    void thread2() 
    {
        for (;;)
        {
            *test = uint32_t(-1); // 0xFFFFFFFF
            const uint32_t check = stop;
            if (check != 0)
                break;
        }
    }

    size_t aligned_address()
    {
        // остаток от деления на 1024 начального адреса массива <memory>
        size_t offset = size_t(memory) % 1024;

        // вычисляем смещение в массиве до адреса кратного 1024
        if (offset != 0)
            offset = 1024 - offset;

        // если смещение получилось слишком маленьким, то берём следующее кратное 1024
        if (offset < 100)
            offset += 1024;

        return offset;
    }

} // namespace

TEST_COMPONENT(001)
{
    const size_t offset = ::aligned_address();
 
    std::thread t1(thread1);
    std::thread t2(thread2);
    stop = 0;
    for (size_t i = 0; i != count_experimant; ++i)
    {
        test = reinterpret_cast<uint32_t*>(&memory[offset]); 
        const uint32_t t = *test;
        const auto success = t == 0 || t == uint32_t(-1);
        ASSERT_TRUE(success)
            << std::hex << t << std::endl;
    }
    stop = 1;
    dprint(std::cout << "done\n");
    t1.join();
    t2.join();
}

TEST_COMPONENT(002)
{
    // not worked
    stop = 0;
    const size_t offset = ::aligned_address();
    test = reinterpret_cast<uint32_t*>(&memory[offset - 2]); 
 
    std::thread t1(thread1);
    std::thread t2(thread2);

    size_t i = 0;
    bool success = false;
    for (i = 0; i != count_experimant; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        const uint32_t t = *test;
        success = t != 0 && t != uint32_t(-1);
        if (success)
            break;
    }
    stop = true;
    t1.join();
    t2.join();

    dprint(std::cout << "number of attempts: " << i << '\n');
    ASSERT_TRUE(success);
}


//==============================================================================
#endif // !(defined(_MSC_VER) && _MSC_VER >= 1700)
#endif // !TEST_TOOLS_SYNC_CONSEPT

 
 
