// [2021y-02m-22d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_ATOMIC

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_ATOMIC
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_ATOMIC
    dMESSAGE("[test] tools: disabled -> dHAS_ATOMIC")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_ATOMIC")
    #include <thread>
    #include <future>
    #include <atomic>

//==============================================================================
//==============================================================================
namespace 
{
    std::atomic<size_t> value = 0;
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
} // namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    // --- check std::atomic with std::async

    #ifdef INCLUDE_LONG_LONG_TESTS
        const size_t total = 10;
    #elif defined (INCLUDE_LONG_TESTS)
        const size_t total = 5;
    #else
        const size_t total = 1;
    #endif

    for (size_t i = 0; i != total; ++i)
    {
        dprint(std::cout << "generation: " << i << '\n');
        value = 0;

        auto f = std::async(
            std::launch::async, 
            std::bind(loop, true, 20000000)
        );
        loop(false, 10000000);
        f.wait();
        ASSERT_TRUE(value == 10000000);
    }
}

#endif // !dHAS_ATOMIC
#endif // !TEST_TOOLS_FEATURE_ATOMIC

