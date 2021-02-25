// [2021y-02m-25d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_RVALUE_ARRAY

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_RVALUE_ARRAY
#define dTEST_TAG tdd

#include <tools/features.hpp>

#include <cassert>

#ifdef dHAS_RVALUE_ARRAY
    dMESSAGE("[test] tools: enabled -> dHAS_RVALUE_ARRAY")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_RVALUE_ARRAY")
#endif

//==============================================================================
//==============================================================================

namespace 
{
} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000) 
{
    #ifdef dHAS_RVALUE_ARRAY
    char arr[2];
    auto&& ref = std::move(arr);
    (void)ref;
    #endif
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FEATURE_RVALUE_ARRAY

