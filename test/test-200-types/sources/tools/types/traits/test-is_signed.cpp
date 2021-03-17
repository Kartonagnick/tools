// [2021y-03m-10d][02:14:35] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_IS_INTEGRAL

#define dTEST_COMPONENT tools, types, traits
#define dTEST_METHOD is_signed
#define dTEST_TAG tdd

#include <tools/types/traits.hpp>
#include <tools/features.hpp>
namespace me = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace
{
    #ifdef dHAS_STATIC_ASSERT
        #define dCHECK(type, expected)                     \
            static_assert(                                 \
                me::is_signed<type>::value == expected,    \
                "'tools::is_signed<" # type ">::value' "   \
                "must be '" #expected "'"                  \
            )
    #else
        #define dCHECK(type, expected)                     \
            dSTATIC_ASSERT(                                \
                me::is_signed<type>::value == expected,    \
                ERROR_MUST_BE_##expected                   \
            )
    #endif

}//namespace

//==============================================================================
//==============================================================================
TEST_COMPONENT(000)
{
    dCHECK(wchar_t  , false);

#if !defined(_MSC_VER) || _MSC_VER >= 1600
    dCHECK(char16_t          , false );
    dCHECK(char32_t          , false );
#endif
    dCHECK(short             , true  );
    dCHECK(unsigned short    , false );
    dCHECK(int               , true  );
    dCHECK(unsigned          , false );
    dCHECK(long              , true  );
    dCHECK(unsigned long     , false );
    dCHECK(unsigned long long, false );
    dCHECK(size_t            , false );
    dCHECK(unsigned          , false );

    dCHECK(signed char       , true  );
    dCHECK(unsigned char     , false );
    dCHECK(float             , true  );
    dCHECK(double            , true  );
    dCHECK(long double       , true  );
}

//==============================================================================
//==============================================================================
#endif // !TEST_IS_INTEGRAL

