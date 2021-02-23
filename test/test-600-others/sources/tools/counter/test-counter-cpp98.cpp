// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_COUNTER
#ifdef _MSC_VER

#define dTEST_COMPONENT tools
#define dTEST_METHOD counter
#define dTEST_TAG cpp98

#include <tools/windows.hpp>
#include <tools/counter.hpp>
#include <process.h>
namespace me = ::tools;

//==============================================================================
//=== TDD ======================================================================
namespace 
{
    struct param { bool dir; size_t limit; };

    me::counter ready = 0;
    me::counter value = 0;

    void threadFunction(void* ptr)
    {
        ASSERT_TRUE(ptr);
        const param& ref = *static_cast<const param*>(ptr);
        dprint(std::cout << "started " << ref.dir << " " << ref.limit << std::endl);
        for (size_t i = 0; i < ref.limit; ++i)
        {
            if (ref.dir)
                ++value;
            else
                --value;
        }
        ++ready;
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

    ::param positive = { true , count_positive };
    ::param negative = { false, count_negative };

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
        ASSERT_TRUE(value == count_negative)
            << "[0] value = " << value << '\n';
    }
}

//==============================================================================
#endif // !_MSC_VER
#endif // !TEST_TOOLS_COUNTER



