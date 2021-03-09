// [2021y-02m-16d][00:59:26] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MACRO_COMB_VALUES_5

#define dTEST_COMPONENT tools, macro
#define dTEST_METHOD comb_values_5
#define dTEST_TAG tdd

#include <tools/macro/comb_values-5.hpp>
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
    dCOMB_VALUES_MAX_5(pp_macro, pp_delim, 1);
    const str_t result = ss.str();
    const char* etalon = "(1, 1:1)";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(001)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_5(pp_macro, pp_delim, 1,2);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), "
        "(1, 2:1), (2, 2:2)";
    ASSERT_EQ(result, etalon);
}
TEST_COMPONENT(003)
{
    sstrem_t ss;
    dCOMB_VALUES_MAX_5(pp_macro, pp_delim, 1,2,3);
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
    dCOMB_VALUES_MAX_5(pp_macro, pp_delim, 1,2,3,4);
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
    dCOMB_VALUES_MAX_5(pp_macro, pp_delim, 1,2,3,4,5);
    const str_t result = ss.str();
    const char* etalon = 
        "(1, 1:1), (2, 1:2), (3, 1:3), (4, 1:4), (5, 1:5), "
        "(1, 2:1), (2, 2:2), (3, 2:3), (4, 2:4), (5, 2:5), "
        "(1, 3:1), (2, 3:2), (3, 3:3), (4, 3:4), (5, 3:5), "
        "(1, 4:1), (2, 4:2), (3, 4:3), (4, 4:4), (5, 4:5), "
        "(1, 5:1), (2, 5:2), (3, 5:3), (4, 5:4), (5, 5:5)" ;
    ASSERT_EQ(result, etalon);
}

//==============================================================================
//==============================================================================

#endif // !TEST_TOOLS_MACRO_COMB_VALUES_5

