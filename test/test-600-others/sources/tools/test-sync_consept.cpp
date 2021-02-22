// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_THREAD_SAFE
#if defined(_MSC_VER) && _MSC_VER >= 1700
// #pragma message("build for msvc2010 (or older)")

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) sync_consept_##n
#include <future>
//==============================================================================
//=== TDD ======================================================================
namespace 
{
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
    int loop(bool inc, int limit)
    {
        dprint(std::cout << "Started " << inc << " " << limit << std::endl);
        for (int i = 0; i < limit; ++i)
        {
            if (inc)
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
    int loop(bool inc, int limit) 
    {
        std::cout << "Started " << inc << " " << limit << std::endl;
        for (int i = 0; i < limit; ++i)
        {
            if (inc)
                atomic_inc32(&value);
            else
                atomic_dec32(&value);
        }
        return 0;
    }
#endif

#if 0
    // spinlock
    int loop(bool inc, int limit) 
    {
        std::cout << "Started " << inc << " " << limit << std::endl;
        for (int i = 0; i < limit; ++i) 
        {
            std::lock_guard<boost::detail::spinlock> guard(lock);
            if (inc)
                ++value;
            else
                --value;
        }
        return 0;
    }
#endif

#if 0
    // mutex
    int loop(bool inc, int limit) 
    {
        std::cout << "Started " << inc << " " << limit << std::endl;
        for (int i = 0; i < limit; ++i)
        {
            std::lock_guard<std::mutex> guard(mutex);
            if (inc)
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
        // --- будут одновремено мен€ть значение 
        // --- волатильной переменной

        auto f = std::async(
            std::launch::async, 
            std::bind(loop, true, 20000000)
        );
        loop(false, 10000000);
        f.wait();

        // --- так как нет никакой синхронизации,
        // --- то в результате должен получитьс€ мусор
        dprint(std::cout << value << '\n');

        success = value != 10000000;
    }
    ASSERT_TRUE(success);
}

//==============================================================================
#endif // !(defined(_MSC_VER) && _MSC_VER >= 1700)
#endif // !TEST_TOOLS_THREAD_SAFE



