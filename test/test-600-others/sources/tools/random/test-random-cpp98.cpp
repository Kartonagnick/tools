// [2019y-10m-24d][23:17:05] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_RANDOM
#ifdef _MSC_VER
#include <tools/features.hpp>
#ifdef dHAS_CHRONO

#include <tools/random.hpp>
#include <string>
#include <list>

#define dTEST_COMPONENT tools
#define dTEST_METHOD random
#define dTEST_TAG cpp98

#include <tools/windows.hpp>
#include <process.h>

namespace me = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace 
{
    #ifdef INCLUDE_LONG_LONG_TESTS
        size_t g_total = 1000;
        size_t g_count = 1000;
    #elif defined (INCLUDE_LONG_TESTS)
        size_t g_total = 500;
        size_t g_count = 500;
    #else
        size_t g_total = 50;
        size_t g_count = 50;
    #endif

    volatile unsigned long ready = 0;
    volatile unsigned long start = 0;
    size_t total = g_total;
    size_t count = g_count;

    void prepare()
    {
        total = testing::stress ? g_total : 10;
        count = testing::stress ? g_count : 10;
        start = 0;
        ready = 0;
    }

    template<class T1, class T2> 
    void check_random(T1 a, T2 b) dNOEXCEPT
    {
        for(size_t n = 0; n < count; ++n)
        {
            const auto re = me::random(a, b);
            ASSERT_TRUE(re >= a && re <= b);
        }
    }
    
    template<class T, size_t N> 
    void check_random(const T (&ar)[N]) dNOEXCEPT
    {
        for(size_t n = 0; n < count; ++n)
        {
            const T& re = me::random(ar);
            ASSERT_TRUE(re >= 0 && re <= 9);
        }
    }

    void test_functionality(void*)
    {
        ::InterlockedIncrement(&start);
        while (start != 10)
            ::Sleep(5);

        const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        check_random(-1000, 1000 );
        check_random(0u   , 1000u);
        check_random('1'  , '9'  );
        check_random(L'1' , L'9' );
        check_random(false , true);
        check_random(1.5  , 9.5  );
        check_random(arr);
        ::InterlockedIncrement(&ready);
    }

} //namespace
//==============================================================================

TEST_COMPONENT(000)
{
    prepare();

    for (size_t x = 0; x != total; ++x)
    {
        dprint(std::cout << "random: " << x + 1 << "/" << total << "\n");
        start = 0;
        ready = 0;
        for (size_t i = 0; i != 10; ++i)
        {
            const ::uintptr_t re
                = ::_beginthread(::test_functionality, 0, NULL);

            ASSERT_TRUE(re != -1);
        }
        while (ready != 10)
            ::Sleep(5);
    }
}

//==============================================================================
//==============================================================================
#endif // !_MSC_VER
#endif // ! dHAS_CHRONO
#endif // !TEST_TOOLS_RANDOM

