// [2019y-10m-24d][23:17:05] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_RANDOM

#include <tools/features.hpp>
#ifdef dHAS_CHRONO

#include <tools/random.hpp>
#include <string>
#include <atomic>
#include <list>

#define dTEST_COMPONENT tools
#define dTEST_METHOD random
#define dTEST_TAG cpp11

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

    std::atomic_size_t start = 0;
    size_t total = g_total;
    size_t count = g_count;

    void prepare()
    {
        total = testing::stress ? g_total : 10;
        count = testing::stress ? g_count : 10;
        start = 0;
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

    void test_functionality()
    {
        ++start;
        while (start != 10)
            ::std::this_thread::sleep_for(
                ::std::chrono::milliseconds(10)
            );

        const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        check_random(-1000, 1000 );
        check_random(0u   , 1000u);
        check_random('1'  , '9'  );
        check_random(L'1' , L'9' );
        check_random(false , true);
        check_random(1.5  , 9.5  );
        check_random(arr);
    }

} //namespace
//==============================================================================

TEST_COMPONENT(000)
{
    prepare();

    for (size_t x = 0; x != total; ++x)
    {
        start = 0;
        std::vector<std::thread> vec;

        for (size_t i = 0; i != 10; ++i)
            vec.emplace_back(test_functionality);

        for (size_t i = 0; i != 10; ++i)
            vec[i].join();
    }
}

//==============================================================================
//==============================================================================
#endif // !dHAS_CHRONO
#endif // !TEST_TOOLS_RANDOM

