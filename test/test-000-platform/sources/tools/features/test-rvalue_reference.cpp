// [2021y-02m-22d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_RVALUE_REFERENCE

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_RVALUE_REFERENCES
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_RVALUE_REFERENCES
    dMESSAGE("[test] tools: disabled -> dHAS_RVALUE_REFERENCES")
#else

#include <tools/features.hpp>
#include <string>

dMESSAGE("[test] tools: enabled -> dHAS_RVALUE_REFERENCES")

//==============================================================================
//==============================================================================
namespace 
{
    void foo(std::string&& rval, const std::string& etalon)
    {
        std::string dst = std::move(rval);
        ASSERT_TRUE(dst == etalon);
    }

} // namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    foo("111", "111");
}

#endif // !dHAS_RVALUE_REFERENCES
#endif // !TEST_TOOLS_FEATURE_RVALUE_REFERENCE

