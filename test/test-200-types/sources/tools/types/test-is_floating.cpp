// [2021y-03m-10d][02:14:35] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_IS_FLOATING

#define dTEST_COMPONENT tools, types, traits
#define dTEST_METHOD is_floating
#define dTEST_TAG tdd

#include <tools/types/traits.hpp>
#include <tools/features.hpp>
namespace me = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace
{
    #ifdef dHAS_STATIC_ASSERT
        #define dCHECK(type, expected)                          \
            static_assert(                                      \
                me::is_floating_point<type>::value == expected, \
                "'tools::is_floating_point<" # type ">::value'" \
                "must be '" #expected "'"                       \
            )
    #else
        #define dCHECK(type, expected)                          \
            dSTATIC_ASSERT(                                     \
                me::is_floating_point<type>::value == expected, \
                ERROR_MUST_BE_##expected                        \
            )
    #endif

}//namespace

//==============================================================================
//==============================================================================
TEST_COMPONENT(000)
{
    dCHECK(wchar_t      , false);
    dCHECK(int          , false);
    dCHECK(short        , false);
    dCHECK(signed char  , false);
    dCHECK(unsigned char, false);
    dCHECK(size_t       , false);
    dCHECK(unsigned     , false);

    dCHECK(float        , true );
    dCHECK(double       , true );
    dCHECK(long double  , true );
}

#endif // !TEST_IS_FLOATING

