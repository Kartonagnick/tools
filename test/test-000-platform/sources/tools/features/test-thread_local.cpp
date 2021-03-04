// [2021y-03m-04d][19:34:26] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_THREAD_LOCAL

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_THREAD_LOCAL
#define dTEST_TAG tdd

#include <tools/features.hpp>
#include <string>

#ifdef dHAS_THREAD_LOCAL
    dMESSAGE("[test] tools: enabled -> dHAS_THREAD_LOCAL")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_THREAD_LOCAL")
#endif

//==============================================================================
//==============================================================================
namespace
{

    #ifdef dHAS_THREAD_LOCAL
        thread_local std::string txt = "11";
    #else
        std::string txt = "11";
    #endif

    dTHREAD_LOCAL_EXTENSION int val = 10;

} // namespace

TEST_COMPONENT(000)
{
    ASSERT_TRUE(txt == "11");
    ASSERT_TRUE(val ==  10 );
}

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_THREAD_LOCAL



