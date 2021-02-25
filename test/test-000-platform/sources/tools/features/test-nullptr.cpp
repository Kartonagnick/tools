// [2021y-02m-22d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_NULLPTR

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_NULLPTR
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_NULLPTR
    dMESSAGE("[test] tools: disabled -> dHAS_NULLPTR")
#else

#include <tools/features.hpp>
#include <string>

dMESSAGE("[test] tools: enabled -> dHAS_NULLPTR")

//==============================================================================
//==============================================================================
namespace 
{
    void foo(char* p)
    {
        ASSERT_TRUE(!p);
    }

    void bar(std::nullptr_t p)
    {
        void* a = p;
        ASSERT_TRUE(p == 0);
        ASSERT_TRUE(!a);
    }

} // namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    char* p = nullptr;
    foo(p);
}

TEST_COMPONENT(001)
{
    bar(nullptr);
}

//==============================================================================
//==============================================================================
#endif // !dHAS_NULLPTR
#endif // !TEST_TOOLS_FEATURE_NULLPTR

