// [2019y-10m-24d][19:22:08] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_RANDOM

#include <tools/features.hpp>
#ifdef dHAS_CHRONO

#include <tools/random.hpp>
#include <string>
#include <list>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) random_##n

namespace me  = ::TEST_CASE_NAME;
//==============================================================================
//=== TDD ======================================================================
namespace 
{
    const size_t count = 1000;

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

    template<class T1, class T2>
    void check_death_random(T1 a, T2 b) dNOEXCEPT
    {
        ASSERT_DEATH_DEBUG(me::random(a, b));
        (void) a;
        (void) b;
    }

} //namespace
//==============================================================================

TEST_COMPONENT(000)
{
    const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    check_random(-1000, 1000 );
    check_random(0u   , 1000u);
    check_random('1'  , '9'  );
    check_random(L'1' , L'9' );
    check_random(false , true);
    check_random(1.5  , 9.5  );
    check_random(arr);
}
TEST_COMPONENT(001)
{
    check_death_random(1000, -1000 );
    check_death_random(1000u   , 0u);
    check_death_random('9'  , '1'  );
    check_death_random(L'9' , L'1' );
    check_death_random(true , false);
    check_death_random(9.5  , 1.5  );
}

//==============================================================================
//==============================================================================
#endif // !dHAS_CHRONO
#endif // !TEST_TOOLS_RANDOM

