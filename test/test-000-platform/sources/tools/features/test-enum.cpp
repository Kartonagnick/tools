
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_ENUM

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_ENUM_CLASS
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_ENUM_CLASS
    dMESSAGE("[test] tools: disabled -> dHAS_ENUM_CLASS")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_ENUM_CLASS")
#endif

//==============================================================================
//==============================================================================
namespace
{
    #if dHAS_ENUM_CLASS
    enum eFLAGS1 : int { eSAMPLE = 0 };
    enum class eFLAGS2 : int { eEXAMPLE = 0 };
    #endif

}//namespace

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_ENUM



