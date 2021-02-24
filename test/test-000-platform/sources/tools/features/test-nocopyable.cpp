// [2021y-02m-25d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_COPYABLE

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_dNOCOPYABLE
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_DELETING_FUNCTIONS
    dMESSAGE("[test] tools: disabled -> dHAS_DELETING_FUNCTIONS")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_DELETING_FUNCTIONS")
#endif

#ifndef dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
    dMESSAGE("[test] tools: disabled -> dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM")
#endif

#ifndef dHAS_USING_ALIAS
    dMESSAGE("[test] tools: disabled -> dHAS_USING_ALIAS")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_USING_ALIAS")
#endif

//==============================================================================
//==============================================================================
namespace 
{
    struct alone
    {
        dNOCOPYABLE(alone);
        alone(){}
    };

    #ifdef dHAS_DELETING_FUNCTIONS
    struct Class
    {
        Class(){}
        Class(const Class&)            = delete;
        Class(Class&&)                 = delete;
        Class& operator=(const Class&) = delete;
        Class& operator=(Class&&)      = delete;
    };
    #endif

    #ifdef dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
    template<class T, size_t n = T::count>
    void foo(T) {}
    #endif

    #ifdef dHAS_USING_ALIAS
    template <class t> using sample = t;
    #endif

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000){}

#endif // !TEST_TOOLS_FEATURE_COPYABLE

