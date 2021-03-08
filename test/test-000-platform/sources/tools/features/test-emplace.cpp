// [2021y-02m-26d][06:07:32] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_HAS_EMPLACE

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_EMPLACE
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifdef dHAS_EMPLACE
    dMESSAGE("[test] tools: enabled -> dHAS_EMPLACE")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_EMPLACE")
#endif

#ifdef dHAS_EMPLACE
#include <vector>
#include <map>

TEST_COMPONENT(000) 
{
    std::vector<int> vec;
    vec.emplace_back(1);

    std::map<int, int> map;
    map.emplace(1, 1);
}
#endif

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_HAS_EMPLACE



