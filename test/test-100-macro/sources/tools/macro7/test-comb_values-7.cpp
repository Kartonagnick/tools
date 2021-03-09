// [2021y-02m-16d][00:59:26] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MACRO_COMB_VALUES_7

#define dTEST_COMPONENT tools, macro
#define dTEST_METHOD comb_values_7
#define dTEST_TAG tdd

#include <tools/macro/comb_values-7.hpp>
#include <test-staff.hpp>
//==============================================================================
//=== example ==================================================================
namespace
{
    #define pp_macro(index, a, b) \
        ss << "(" << index << ", " << #a << ":" << #b << ")";
        
    #define pp_delim(index) \
        ss << ", ";

} // namespace
//==============================================================================
//==============================================================================

// --- (1)
TEST_COMPONENT(000)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1);
    const str_t result = ss.str();
    const char* etalon = "(1, 1:1)";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(001)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), "
        "(1, 2:1), (2, 2:2)";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(003)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), (3, 1:3), "
        "(1, 2:1), (2, 2:2), (3, 2:3), "
        "(1, 3:1), (2, 3:2), (3, 3:3)" ;
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(004)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3,4);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), (3, 1:3), (4, 1:4), "
        "(1, 2:1), (2, 2:2), (3, 2:3), (4, 2:4), "
        "(1, 3:1), (2, 3:2), (3, 3:3), (4, 3:4), "
        "(1, 4:1), (2, 4:2), (3, 4:3), (4, 4:4)" ;
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(006)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3,4,5);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), (3, 1:3), (4, 1:4), (5, 1:5), "
        "(1, 2:1), (2, 2:2), (3, 2:3), (4, 2:4), (5, 2:5), "
        "(1, 3:1), (2, 3:2), (3, 3:3), (4, 3:4), (5, 3:5), "
        "(1, 4:1), (2, 4:2), (3, 4:3), (4, 4:4), (5, 4:5), "
        "(1, 5:1), (2, 5:2), (3, 5:3), (4, 5:4), (5, 5:5)" ;
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(007)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3,4,5,6);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), (3, 1:3), (4, 1:4), (5, 1:5), (6, 1:6), "
        "(1, 2:1), (2, 2:2), (3, 2:3), (4, 2:4), (5, 2:5), (6, 2:6), "
        "(1, 3:1), (2, 3:2), (3, 3:3), (4, 3:4), (5, 3:5), (6, 3:6), "
        "(1, 4:1), (2, 4:2), (3, 4:3), (4, 4:4), (5, 4:5), (6, 4:6), "
        "(1, 5:1), (2, 5:2), (3, 5:3), (4, 5:4), (5, 5:5), (6, 5:6), "
        "(1, 6:1), (2, 6:2), (3, 6:3), (4, 6:4), (5, 6:5), (6, 6:6)" ;
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(008)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3,4,5,6,7);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), (3, 1:3), (4, 1:4), (5, 1:5), (6, 1:6), (7, 1:7), "
        "(1, 2:1), (2, 2:2), (3, 2:3), (4, 2:4), (5, 2:5), (6, 2:6), (7, 2:7), "
        "(1, 3:1), (2, 3:2), (3, 3:3), (4, 3:4), (5, 3:5), (6, 3:6), (7, 3:7), "
        "(1, 4:1), (2, 4:2), (3, 4:3), (4, 4:4), (5, 4:5), (6, 4:6), (7, 4:7), "
        "(1, 5:1), (2, 5:2), (3, 5:3), (4, 5:4), (5, 5:5), (6, 5:6), (7, 5:7), "
        "(1, 6:1), (2, 6:2), (3, 6:3), (4, 6:4), (5, 6:5), (6, 6:6), (7, 6:7), "
        "(1, 7:1), (2, 7:2), (3, 7:3), (4, 7:4), (5, 7:5), (6, 7:6), (7, 7:7)" ;
    ASSERT_EQ(result, etalon);
}


//==============================================================================
//==============================================================================

#endif // !TEST_TOOLS_MACRO_COMB_VALUES_7

