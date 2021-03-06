// [2021y-03m-14d][22:10:18] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_REMOVE_REFERENCE

#define dTEST_COMPONENT tools, types, traits
#define dTEST_METHOD remove_reference
#define dTEST_TAG tdd

#include <tools/types/traits.hpp>
#include <tools/features.hpp>
namespace me = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace
{
    #define dVAL(a) \
        typename me::remove_reference<a>::type

    #ifdef dHAS_STATIC_ASSERT
        #define dCHECK(a, b)                               \
            static_assert(                                 \
                me::is_same<dVAL(a), b>::value,            \
                "'tools::remove_reference<" #a ">::type' " \
                "must be '" #b "'"                         \
            )
    #else
        #define dCHECK(a, b)                         \
        {                                            \
            typedef me::remove_reference<a>::type x; \
            typedef me::is_same<x, b> y;             \
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
    dCHECK(int                , int);
    dCHECK(const int          , const int);
    dCHECK(volatile int       , volatile int);
    dCHECK(volatile const int , volatile const int);

    dCHECK(int*                , int*);
    dCHECK(const int*          , const int*);
    dCHECK(volatile int*       , volatile int*);
    dCHECK(volatile const int* , volatile const int*);

    dCHECK(int&                , int);
    dCHECK(const int&          , const int);
    dCHECK(volatile int&       , volatile int);
    dCHECK(volatile const int& , volatile const int);

    dCHECK(int*&                , int*);
    dCHECK(const int*&          , const int*);
    dCHECK(volatile int*&       , volatile int*);
    dCHECK(volatile const int*& , volatile const int*);
}

#ifdef dHAS_RVALUE_REFERENCES
TEST_COMPONENT(001)
{
    dCHECK(int&&                , int);
    dCHECK(const int&&          , const int);
    dCHECK(volatile int&&       , volatile int);
    dCHECK(volatile const int&& , volatile const int);

    dCHECK(int*&&                , int*);
    dCHECK(const int*&&          , const int*);
    dCHECK(volatile int*&&       , volatile int*);
    dCHECK(volatile const int*&& , volatile const int*);
}
#endif

//==============================================================================
//==============================================================================
#endif // !TEST_REMOVE_REFERENCE

