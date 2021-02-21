// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_THREAD_SAFE

// examples:
// check thread-safe consept

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) thred_safe_##n

#include <future>

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    volatile int value = 0;
    int loop(bool inc, int limit)
    {
        dprint(std::cout << "Started " << inc << " " << limit << std::endl);

        for (int i = 0; i < limit; ++i)
        {
            if (inc)
                ++value;
            else
                --value;
        }
        return 0;
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
            std::bind(loop, true, 20'000'000)
        );
        loop(false, 10'000'000);
        f.wait();

        // --- так как нет никакой синхронизации,
        // --- то в результате должен получитьс€ мусор
        dprint(std::cout << value << '\n');

        success = value != 10'000'000;
    }
    ASSERT_TRUE(success);
}

//==============================================================================
#endif // !TEST_TOOLS_THREAD_SAFE



