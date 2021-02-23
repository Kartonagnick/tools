// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_COUNTER
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

    const size_t count_positive = 2000000;
    const size_t count_negative = 1000000;


} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
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



