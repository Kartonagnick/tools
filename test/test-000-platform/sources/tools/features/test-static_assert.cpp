
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_STASTIC_ASSERT

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_STATIC_ASSERT
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_STATIC_ASSERT
    dMESSAGE("[test] tools: disabled -> dHAS_STATIC_ASSERT")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_STATIC_ASSERT")
#endif

//==============================================================================
//==============================================================================
namespace
{
    #if dHAS_STATIC_ASSERT
        constexpr const char* ptr = "123";
        static_assert(
            ptr[1] == '2',
            "'static_assert' not worked"
        );
    #endif

}//namespace

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_STASTIC_ASSERT



