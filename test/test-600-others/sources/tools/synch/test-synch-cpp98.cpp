// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_SYNCH
#ifdef _MSC_VER

#define dTEST_COMPONENT tools
#define dTEST_METHOD synch
#define dTEST_TAG cpp98

#include <tools/synch.hpp>
#include <tools/windows.hpp>
#include <process.h>
namespace me = ::tools;

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    struct param { bool dir; size_t limit; };

    size_t begin = 0;
    size_t ready = 0;
    size_t value = 0;
    me::synch sync;

    void threadFunction(void* ptr)
    {
        ASSERT_TRUE(ptr);
        const param& ref = *static_cast<const param*>(ptr);
        dprint(std::cout << "started " << ref.dir << " " << ref.limit << std::endl);

        ++begin;
        while (begin != 2)
            ::Sleep(30);

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

    size_t count_positive = 2000000;
    size_t count_negative = 1000000;

    void prepare()
    {
        count_negative = testing::stress ? 1000000 : 100;
        count_positive = count_negative * 2;
        begin = 0;
        ready = 0;
        value = 0;
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

    prepare();
    ::param positive = { true , count_positive };
    ::param negative = { false, count_negative };

    for (size_t i = 0; i != total; ++i)
    {
        prepare();
        dprint(std::cout << "generation(" << count_negative << "): " << i + 1 << "/" << total << '\n');

        const uintptr_t re 
            = ::_beginthread(::threadFunction, 0, &positive);
	    ASSERT_TRUE(re != -1);

        ::threadFunction(&negative);

        while (ready != 2)
            ::Sleep(30);

        ASSERT_TRUE(value == count_negative)
            << "value = " << value << '\n';
    }
    ::Sleep(30);
}

//==============================================================================
#endif // !_MSC_VER
#endif // !TEST_TOOLS_SYNCH



