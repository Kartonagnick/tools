// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_SYNCH
#ifdef _MSC_VER

#define dTEST_COMPONENT tools
#define dTEST_METHOD synch
#define dTEST_TAG cpp98

#include <tools/platform/windows/synch.hpp>
#include <process.h>
namespace me = ::tools;

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    struct param { bool dir; size_t limit; };

    size_t ready = 0;
    size_t value = 0;
    me::synch sync;

    void threadFunction(void* ptr)
    {
        ASSERT_TRUE(ptr);
        const param& ref = *static_cast<const param*>(ptr);
        dprint(std::cout << "Started " << ref.dir << " " << ref.limit << std::endl);
        for (size_t i = 0; i < ref.limit; ++i)
        {
            if (ref.dir)
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
        me::synch_guard lock(sync);
        ++ready;
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

    ::param positive = { true , 20000000 };
    ::param negative = { false, 10000000 };

    for (size_t i = 0; i != total; ++i)
    {
        dprint(std::cout << "generation: " << i << '\n');
        ready = 0;
        value = 0;

        const uintptr_t re 
            = ::_beginthread(::threadFunction, 0, &positive);
	    ASSERT_TRUE(re != -1);

        ::threadFunction(&negative);

        while (ready != 2)
            ::Sleep(100);

        ::Sleep(50);
        ASSERT_TRUE(value == 10000000)
            << "real = " << value << '\n';
    }
}

//==============================================================================
#endif // !_MSC_VER
#endif // !TEST_TOOLS_SYNCH



