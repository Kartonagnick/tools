// [2021y-03m-10d][02:14:35] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_CONDITIONAL

#define dTEST_COMPONENT tools, types, traits
#define dTEST_METHOD conditional
#define dTEST_TAG tdd

#include <tools/types/traits.hpp>
#include <tools/features.hpp>
namespace me = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace
{
    #define dVAL(v,a,b) \
        typename me::conditional<v,a,b>::type

    #ifdef dHAS_STATIC_ASSERT
        #define dCHECK(v, a, b, t)                                    \
            static_assert(                                            \
                me::is_same<dVAL(v,a,b), t>::value,                   \
                "'tools::conditional<" #v ", " #a ", " #b ">::type' " \
                "must be '" #t "'"                                    \
            )
    #else
        #define dCHECK(v, a, b, t)                   \
        {                                            \
            typedef me::conditional<v,a,b>::type x;  \
            typedef me::is_same<x,t> y;              \
            dSTATIC_ASSERT(                          \
                y::value, ERROR_MUST_BE_##expected   \
            );                                       \
        } void()

    #endif

}//namespace

//==============================================================================
//==============================================================================
TEST_COMPONENT(000)
{
    dCHECK(true , int , int , int );
    dCHECK(false, int , int , int );
    dCHECK(true , char, bool, char);
    dCHECK(false, char, bool, bool);
}

//==============================================================================
//==============================================================================
#endif // !TEST_CONDITIONAL

