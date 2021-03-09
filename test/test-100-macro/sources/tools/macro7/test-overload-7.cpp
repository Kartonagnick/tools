// [2021y-02m-16d][00:59:26] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MACRO_OVERLOAD_7

#define dTEST_COMPONENT tools, macro
#define dTEST_METHOD overload_7
#define dTEST_TAG tdd

#include <tools/macro/overload-7.hpp>
#include <test-staff.hpp>
//==============================================================================
//=== example ==================================================================
namespace
{
    #define dPRINT_0() \
        ss << "empty"

    #define dPRINT_1(a1) \
        ss << a1

    #define dPRINT_2(a1, a2) \
        ss << a1 << ", " << a2

    #define dPRINT_3(a1, a2, a3) \
        ss << a1 << ", " << a2 << ", " << a3

    #define dPRINT_4(a1, a2, a3, a4) \
        ss << a1 << ", " << a2 << ", " << a3 << ", " << a4

    #define dPRINT_5(a1, a2, a3, a4, a5) \
        ss << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5

    #define dPRINT_6(a1, a2, a3, a4, a5, a6) \
        ss << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5 << ", " << a6 

    #define dPRINT_7(a1, a2, a3, a4, a5, a6, a7) \
        ss << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 
    
    #define dPRINT(...) \
        dMACRO_CHOOSER_7(dPRINT, __VA_ARGS__)(__VA_ARGS__)

//..............................................................................

    #define dargs_count(...) \
        dGET_ARGS_COUNT_MAX_7(__VA_ARGS__)

//..............................................................................

    #define dif_arg_count_0() \
        dPRINT()

    #define dif_arg_count_N(...) \
        ss << "more: "; dPRINT(__VA_ARGS__)

    #define dlaunch_zero_or_more_arguments(...) \
        dNULL_OR_MORE_7(dif_arg_count, __VA_ARGS__)(__VA_ARGS__)

} //namespace 
//==============================================================================

//--- dPRINT
TEST_COMPONENT(000)
{
    sstrem_t ss;
    dPRINT();
    const str_t result = ss.str();
    const char* etalon = "empty";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(001)
{
    sstrem_t ss;
    dPRINT(1);
    const str_t result = ss.str();
    const char* etalon = "1";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(002)
{
    sstrem_t ss;
    dPRINT(1,2);
    const str_t result = ss.str();
    const char* etalon = "1, 2";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(003)
{
    sstrem_t ss;
    dPRINT(1,2,3);
    const str_t result = ss.str();
    const char* etalon = "1, 2, 3";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(004)
{
    sstrem_t ss;
    dPRINT(1,2,3,4);
    const str_t result = ss.str();
    const char* etalon = "1, 2, 3, 4";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(005)
{
    sstrem_t ss;
    dPRINT(1,2,3,4,5);
    const str_t result = ss.str();
    const char* etalon = "1, 2, 3, 4, 5";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(006)
{
    sstrem_t ss;
    dPRINT(1,2,3,4,5,6);
    const str_t result = ss.str();
    const char* etalon = "1, 2, 3, 4, 5, 6";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(007)
{
    sstrem_t ss;
    dPRINT(1,2,3,4,5,6,7);
    const str_t result = ss.str();
    const char* etalon = "1, 2, 3, 4, 5, 6, 7";
    ASSERT_EQ(result, etalon);
}


//--- dargs_count
TEST_COMPONENT(008)
{
    const size_t cnt = dargs_count();
    ASSERT_TRUE(cnt == 0);
}
TEST_COMPONENT(009)
{
    const size_t cnt = dargs_count(1);
    ASSERT_TRUE(cnt == 1);
}
TEST_COMPONENT(010)
{
    const size_t cnt = dargs_count(1,2);
    ASSERT_TRUE(cnt == 2);
}
TEST_COMPONENT(011)
{
    const size_t cnt = dargs_count(1,2,3);
    ASSERT_TRUE(cnt == 3);
}
TEST_COMPONENT(012)
{
    const size_t cnt = dargs_count(1,2,3,4);
    ASSERT_TRUE(cnt == 4);
}
TEST_COMPONENT(013)
{
    const size_t cnt = dargs_count(1,2,3,4,5);
    ASSERT_TRUE(cnt == 5);
}

// --- dlaunch_zero_or_more_arguments
TEST_COMPONENT(014)
{
    sstrem_t ss;
    dlaunch_zero_or_more_arguments();
    const str_t result = ss.str();
    const char* etalon = "empty";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(015)
{
    sstrem_t ss;
    dlaunch_zero_or_more_arguments(1);
    const str_t result = ss.str();
    const char* etalon = "more: 1";
    ASSERT_EQ(result, etalon);
}

TEST_COMPONENT(016)
{
    sstrem_t ss;
    dlaunch_zero_or_more_arguments(1, 2);
    const str_t result = ss.str();
    const char* etalon = "more: 1, 2";
    ASSERT_EQ(result, etalon);
}

#endif // !TEST_TOOLS_MACRO_OVERLOAD_7

