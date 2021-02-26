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
    void loop(const bool dir, const size_t limit)
    {
        dprint(std::cout << "started: " << dir << " " << limit << std::endl);
        for (size_t i = 0; i < limit; ++i)
            if (dir)
                ++value;
            else
                --value;
    }
} // namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    // --- check std::atomic with std::async

    const size_t payload
        = testing::stress ? 100000 : 100;

    #ifdef INCLUDE_LONG_LONG_TESTS
        const size_t count = payload * 100;
        const size_t total = 10;
    #elif defined (INCLUDE_LONG_TESTS)
        const size_t count = payload * 10;
        const size_t total = 5;
    #else
        const size_t count = payload;
        const size_t total = 1;
    #endif

    for (size_t i = 0; i != total; ++i)
    {
        value = 0;
        dprint(std::cout << "generation(" << count << "): " << i + 1 << "/" << total << '\n');
        auto f = std::async(
            std::launch::async, 
            std::bind(loop, true, 2 * count)
        );
        loop(false, count);
        f.wait();
        ASSERT_TRUE(value == count);
    }
}

#endif // !dHAS_ATOMIC
#endif // !TEST_TOOLS_FEATURE_ATOMIC

