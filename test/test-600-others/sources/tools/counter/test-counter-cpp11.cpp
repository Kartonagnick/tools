// [2021y-02m-21d][23:59:04] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_COUNTER

#include <tools/features.hpp>

#ifdef dHAS_ATOMIC

#define dTEST_COMPONENT tools
#define dTEST_METHOD counter
#define dTEST_TAG cpp11

#include <future>
#include <tools/counter.hpp>
namespace me = ::tools;

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    me::counter value = 0;
    int loop(bool dir, size_t limit)
    {
        dprint(std::cout << "started: " << dir << " " << limit << std::endl);
        for (size_t i = 0; i < limit; ++i)
        {
            if (dir)
                ++value;
            else
                --value;
        }
        return 0;
    }

    size_t count_positive = 2000000;
    size_t count_negative = 1000000;

    void prepare()
    {
        count_negative = testing::stress ? 1000000 : 100;
        count_positive = count_negative * 2;
        value = 0;
    }

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    prepare();

    #ifdef INCLUDE_LONG_LONG_TESTS
        const size_t total = 10;
    #elif defined (INCLUDE_LONG_TESTS)
        const size_t total = 5;
    #else
        const size_t total = 1;
    #endif

    for (size_t i = 0; i != total; ++i)
    {
        dprint(std::cout << "generation(" << count_negative << "): " << i + 1 << "/" << total << '\n');
        value = 0;

        auto f = std::async(
            std::launch::async, 
            std::bind(loop, true, count_positive)
        );
        loop(false, count_negative);
        f.wait();

        ASSERT_TRUE(value == count_negative)
            << "[0] value = " << value << '\n';
    }
}

//==============================================================================
#endif // !dHAS_ATOMIC
#endif // !TEST_TOOLS_COUNTER



