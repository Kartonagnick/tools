// [2021y-03m-15d][18:27:18] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_AGGREGATE_INITIALIZE

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_AGGREGATE_INITIALIZE
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifdef dHAS_AGGREGATE_INITIALIZE
    dMESSAGE("[test] tools: enabled -> dHAS_AGGREGATE_INITIALIZE")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_AGGREGATE_INITIALIZE")
#endif
//..............................................................................
#ifdef dHAS_AGGREGATE_INITIALIZE
#include <string>
#include <vector>
#include <list>
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const std::list<std::string> 
        example = { "aaabbb", "cccddd", "fffggg", "hhhjjj", "yyyuuu", "oooppp" };
    ASSERT_TRUE(example.size() == 6);
}

TEST_COMPONENT(001)
{
    const std::vector<std::string> 
        example = { "aaabbb", "cccddd", "fffggg", "hhhjjj", "yyyuuu", "oooppp" };
    ASSERT_TRUE(example.size() == 6);
}

//==============================================================================
//==============================================================================
#endif // ! dHAS_AGGREGATE_INITIALIZE
#endif // ! TEST_TOOLS_FEATURE_AGGREGATE_INITIALIZE



