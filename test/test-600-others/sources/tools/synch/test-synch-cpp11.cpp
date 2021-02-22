// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_SYNCH
#ifdef dHAS_ATOMIC

#define dTEST_COMPONENT tools
#define dTEST_METHOD synch
#define dTEST_TAG cpp11

#include <future>
#include <tools/platform/windows/synch.hpp>
namespace me = ::tools;

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    size_t value = 0;
    me::synch sync;

    void loop(const bool dir, const size_t limit)
    {
        dprint(std::cout << "started: " << dir << " " << limit << std::endl);
        for (size_t i = 0; i < limit; ++i)
        {
            if (dir)
            {
                me::synch_guard lock(sync);
                ++value;
            }
            else
            {
                me::synch_guard lock(sync);
                --value;
            }
        }
    }

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
            std::bind(loop, true, 20000000)
        );
        loop(false, 10000000);
        f.wait();

        ASSERT_TRUE(value == 10000000);
    }
}

//==============================================================================
#endif // !dHAS_ATOMIC
#endif // !TEST_TOOLS_SYNCH



