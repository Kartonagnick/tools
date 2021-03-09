// [2021y-02m-16d][00:59:26] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MACRO_REPEAT_7

#define dTEST_COMPONENT tools, macro
#define dTEST_METHOD repeat_7
#define dTEST_TAG tdd

#include <tools/macro/repeat-7.hpp>
#include <test-staff.hpp>
//=== example ==================================================================
namespace
{
    #define pp_macro(index) ss << index;

    #define pp_delim(index) ss << ",";
    
    #define pp_repeat(num) \
        dREPEAT(pp_macro, pp_delim, num);

} //namespace 
//==============================================================================

TEST_COMPONENT(000)
{
    sstrem_t ss;
    pp_repeat(1);
    const str_t result = ss.str();
    const char* etalon = "1";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}
TEST_COMPONENT(001)
{
    sstrem_t ss;
    pp_repeat(2);
    const str_t result = ss.str();
    const char* etalon = "1,2";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}
TEST_COMPONENT(002)
{
    sstrem_t ss;
    pp_repeat(3);
    const str_t result = ss.str();
    const char* etalon = "1,2,3";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}
TEST_COMPONENT(003)
{
    sstrem_t ss;
    pp_repeat(4);
    const str_t result = ss.str();
    const char* etalon = "1,2,3,4";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}
TEST_COMPONENT(004)
{
    sstrem_t ss;
    pp_repeat(5);
    const str_t result = ss.str();
    const char* etalon = "1,2,3,4,5";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}
TEST_COMPONENT(005)
{
    sstrem_t ss;
    pp_repeat(6);
    const str_t result = ss.str();
    const char* etalon = "1,2,3,4,5,6";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}
TEST_COMPONENT(006)
{
    sstrem_t ss;
    pp_repeat(7);
    const str_t result = ss.str();
    const char* etalon = "1,2,3,4,5,6,7";
    ASSERT_EQ(result, etalon)
        << "etalon: " << etalon << '\n'
        << "result: " << result << '\n'
    ;
}

#endif // !TEST_TOOLS_MACRO_REPEAT_7

