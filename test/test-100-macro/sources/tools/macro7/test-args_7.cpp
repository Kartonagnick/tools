// [2021y-02m-16d][00:59:26] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MACRO_ARGS_7

#define dTEST_COMPONENT tools, macro
#define dTEST_METHOD args_7
#define dTEST_TAG tdd

#include <tools/macro/args-7.hpp>
#include <test-staff.hpp>
//=== example ==================================================================
namespace
{
    template<class arr>
    void compareArrays(const arr& a, const arr& b) 
    {
        dCONSTANT size_t size_a = sizeof(a)/sizeof(a[0]);
        dCONSTANT size_t size_b = sizeof(b)/sizeof(b[0]);
        dCHECK_VALUE(size_a == size_b);

        for(size_t i = 0; i != size_a; ++i)
        {
            ASSERT_EQ(a[i], b[i]);
        }
    }

    #define dargs_count(...) dGET_ARGS_COUNT_MAX_7(__VA_ARGS__)
    #define dif_arg_count_0(...) "zero"
    #define dif_arg_count_N(...) "many"

    #define dzero_or_more_arguments(...) \
        dNULL_OR_MORE_7(dif_arg_count, __VA_ARGS__)(__VA_ARGS__)

} //namespace 
//==============================================================================

// --- dFIRST_ARG
TEST_COMPONENT(000)
{
    dCONSTANT size_t count = dFIRST_ARG(11,22,33,44,55,66,77,88,99,10);
    dCHECK_VALUE(count == 11);
}
TEST_COMPONENT(001)
{
    dCONSTANT size_t count = dFIRST_ARG(55,66,77,88,99,10);
    dCHECK_VALUE(count == 55);
}
TEST_COMPONENT(002)
{
    const str_t result = dzero_or_more_arguments(dFIRST_ARG(,66,77,88,99,10));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(003)
{
    const str_t result = dzero_or_more_arguments(dFIRST_ARG());
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(004)
{
    const str_t result = dzero_or_more_arguments(dFIRST_ARG(55,66,77,88,99,10));
    ASSERT_EQ(result, "many");
}

// --- dLAST_ARG_MAX_7
TEST_COMPONENT(005x1)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11,22,33,44,55,66,77);
    dCHECK_VALUE(count == 77);
}
TEST_COMPONENT(005x2)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11,22,33,44,55,66);
    dCHECK_VALUE(count == 66);
}
TEST_COMPONENT(005)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11,22,33,44,55);
    dCHECK_VALUE(count == 55);
}
TEST_COMPONENT(006)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11,22,33,44);
    dCHECK_VALUE(count == 44);
}
TEST_COMPONENT(007)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11,22,33);
    dCHECK_VALUE(count == 33);
}
TEST_COMPONENT(008)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11,22);
    dCHECK_VALUE(count == 22);
}
TEST_COMPONENT(009)
{
    dCONSTANT size_t count = dLAST_ARG_MAX_7(11);
    dCHECK_VALUE(count == 11);
}
TEST_COMPONENT(010)
{
    const str_t result = dzero_or_more_arguments(dLAST_ARG_MAX_7());
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(011)
{
    const str_t result = dzero_or_more_arguments(dLAST_ARG_MAX_7(1));
    ASSERT_EQ(result, "many");
}

// --- dGET_ARG(num, ...)
TEST_COMPONENT(012)
{
    const str_t result = dzero_or_more_arguments(dGET_ARG(0, 11,22,33,44,55,66,77));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(013)
{
    const str_t result = dzero_or_more_arguments(dGET_ARG(1, 11,22,33,44,55,66,77));
    ASSERT_EQ(result, "many");
}
TEST_COMPONENT(014)
{
    dCONSTANT size_t count = dGET_ARG(1, 11,22,33,44,55,66,77);
    dCHECK_VALUE(count == 11);
}
TEST_COMPONENT(015)
{
    dCONSTANT size_t count = dGET_ARG(1, 11,22,33,44,55,66,77);
    dCHECK_VALUE(count == 11);
}

TEST_COMPONENT(016)
{
    dCONSTANT size_t count = dGET_ARG(1, 11,22,33,44,55,66,77);
    dCHECK_VALUE(count == 11);
}
TEST_COMPONENT(017)
{
    dCONSTANT size_t count = dGET_ARG(2, 11,22,33,44,55,66);
    dCHECK_VALUE(count == 22);
}
TEST_COMPONENT(018)
{
    dCONSTANT size_t count = dGET_ARG(3, 11,22,33,44,55);
    dCHECK_VALUE(count == 33);
}
TEST_COMPONENT(019)
{
    dCONSTANT size_t count = dGET_ARG(4, 11,22,33,44);
    dCHECK_VALUE(count == 44);
}
TEST_COMPONENT(020)
{
    dCONSTANT size_t count = dGET_ARG(4, 11,22,33,44,55);
    dCHECK_VALUE(count == 44);
}
TEST_COMPONENT(021)
{
    dCONSTANT size_t count = dGET_ARG(5, 11,22,33,44,55);
    dCHECK_VALUE(count == 55);
}
TEST_COMPONENT(022)
{
    dCONSTANT size_t count = dGET_ARG(6, 11,22,33,44,55,66);
    dCHECK_VALUE(count == 66);
}
TEST_COMPONENT(023)
{
    dCONSTANT size_t count = dGET_ARG(7, 11,22,33,44,55,66,77);
    dCHECK_VALUE(count == 77);
}
TEST_COMPONENT(024)
{
    dCONSTANT size_t count = dGET_ARG(1, 11);
    dCHECK_VALUE(count == 11);
}
TEST_COMPONENT(025)
{
    const str_t result = dzero_or_more_arguments(dGET_ARG(0, 11));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(026)
{
    const str_t result = dzero_or_more_arguments(dGET_ARG(1, 11));
    ASSERT_EQ(result, "many");
}
TEST_COMPONENT(027)
{
    const str_t result = dzero_or_more_arguments(dGET_ARG(0, ));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(028)
{
    // not worked
    //const str_t result = dzero_or_more_arguments(dGET_ARG(1, ));
    //ASSERT_EQ(result, "zero");
}

// --- dFIRST_ARGS(num, ...)
TEST_COMPONENT(029)
{
    const str_t result = dzero_or_more_arguments(dFIRST_ARGS(0, 1,2,3,4,5,6,7));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(030)
{
    const str_t result = dzero_or_more_arguments(dFIRST_ARGS(1, 1,2,3,4,5,6,7));
    ASSERT_EQ(result, "many");
}
TEST_COMPONENT(031)
{
    dCONSTANT int etalon[1] = { 1 };
    dCONSTANT int arr[1] = { dFIRST_ARGS(1, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(032)
{
    dCONSTANT int etalon[2] = { 1,2 };
    dCONSTANT int arr[2] = { dFIRST_ARGS(2, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(033)
{
    dCONSTANT int etalon[3] = { 1,2,3 };
    dCONSTANT int arr[3] = { dFIRST_ARGS(3, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(034)
{
    dCONSTANT int etalon[4] = { 1,2,3,4 };
    dCONSTANT int arr[4] = { dFIRST_ARGS(4, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(035)
{
    dCONSTANT int etalon[5] = { 1,2,3,4,5 };
    dCONSTANT int arr[5] = { dFIRST_ARGS(5, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(036)
{
    dCONSTANT int etalon[6] = { 1,2,3,4,5,6 };
    dCONSTANT int arr[6] = { dFIRST_ARGS(6, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(037)
{
    dCONSTANT int etalon[7] = { 1,2,3,4,5,6,7 };
    dCONSTANT int arr[7] = { dFIRST_ARGS(7, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}

TEST_COMPONENT(038)
{
    const str_t result = dzero_or_more_arguments(dFIRST_ARGS(0, ));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(039)
{
    // not worked
    //const str_t result = dzero_or_more_arguments(dFIRST_ARGS(1, ));
    //ASSERT_EQ(result, "zero");
}

// --- dREVERT_ARGS_MAX_7(...)
TEST_COMPONENT(040)
{
    const str_t result = dzero_or_more_arguments(dREVERT_ARGS_MAX_7());
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(041)
{
    const str_t result = dzero_or_more_arguments(dREVERT_ARGS_MAX_7(1));
    ASSERT_EQ(result, "many");
}
TEST_COMPONENT(042)
{
    dCONSTANT int value = dREVERT_ARGS_MAX_7(1);
    dCHECK_VALUE(value == 1);
}
TEST_COMPONENT(043)
{
    dCONSTANT int etalon[2] = { 2,1 };
    dCONSTANT int arr[2] = { dREVERT_ARGS_MAX_7(1,2) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(044)
{
    dCONSTANT int etalon[3] = { 3,2,1 };
    dCONSTANT int arr[3] = { dREVERT_ARGS_MAX_7(1,2,3) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(045)
{
    dCONSTANT int etalon[4] = { 4,3,2,1 };
    dCONSTANT int arr[4] = { dREVERT_ARGS_MAX_7(1,2,3,4) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(046)
{
    dCONSTANT int etalon[5] = { 5,4,3,2,1 };
    dCONSTANT int arr[5] = { dREVERT_ARGS_MAX_7(1,2,3,4,5) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(047)
{
    dCONSTANT int etalon[6] = { 6,5,4,3,2,1 };
    dCONSTANT int arr[6] = { dREVERT_ARGS_MAX_7(1,2,3,4,5,6) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(048)
{
    dCONSTANT int etalon[7] = { 7,6,5,4,3,2,1 };
    dCONSTANT int arr[7] = { dREVERT_ARGS_MAX_7(1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}

//--- dLAST_ARGS_MAX_7(num, ...)
TEST_COMPONENT(049)
{
    const str_t result = dzero_or_more_arguments(dLAST_ARGS_MAX_7(0, 1,2,3,4,5,6,7));
    ASSERT_EQ(result, "zero");
}
TEST_COMPONENT(050)
{
    const str_t result = dzero_or_more_arguments(dLAST_ARGS_MAX_7(1, 1,2,3,4,5,6,7));
    ASSERT_EQ(result, "many");
}
TEST_COMPONENT(051)
{
    dCONSTANT int etalon[1] = { 7 };
    dCONSTANT int arr[1] = { dLAST_ARGS_MAX_7(1, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(052)
{
    dCONSTANT int etalon[2] = { 6,7 };
    dCONSTANT int arr[2] = { dLAST_ARGS_MAX_7(2, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(053)
{
    dCONSTANT int etalon[3] = { 5,6,7 };
    dCONSTANT int arr[3] = { dLAST_ARGS_MAX_7(3, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(054)
{
    dCONSTANT int etalon[4] = { 4,5,6,7 };
    dCONSTANT int arr[4] = { dLAST_ARGS_MAX_7(4, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(055)
{
    dCONSTANT int etalon[5] = { 3,4,5,6,7 };
    dCONSTANT int arr[5] = { dLAST_ARGS_MAX_7(5, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(056)
{
    dCONSTANT int etalon[6] = { 2,3,4,5,6,7 };
    dCONSTANT int arr[6] = { dLAST_ARGS_MAX_7(6, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}
TEST_COMPONENT(057)
{
    dCONSTANT int etalon[7] = { 1,2,3,4,5,6,7 };
    dCONSTANT int arr[7] = { dLAST_ARGS_MAX_7(7, 1,2,3,4,5,6,7) };
    compareArrays(arr, etalon);
}

TEST_COMPONENT(058)
{
    const str_t result = dzero_or_more_arguments(dLAST_ARGS_MAX_7(0, ));
    ASSERT_EQ(result, "zero");
}

#endif // !TEST_TOOLS_MACRO_ARGS_7

