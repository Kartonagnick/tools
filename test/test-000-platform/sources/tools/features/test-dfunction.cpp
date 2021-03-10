// [2021y-02m-25d][02:24:11] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_DFUNCTION

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_FUNCTION
#define dTEST_TAG tdd

#include <tools/dfunction.hpp>
#include <tools/features.hpp>
#include <string>

#ifdef dHAS_CPP11
    dMESSAGE("[test] tools: enabled -> dFUNCTION")
#endif

//==============================================================================
//==============================================================================

static dCONSTEXPR_CPP11 const char* dfunction() dNOEXCEPT
{
    return dFUNCTION;
}

#if defined(_MSC_VER) && defined(dHAS_CPP11)
    constexpr bool static_check(const char* p, const size_t i = 0)
    {
        return p[i] == 0 ? false :
            p[i] == 'd' && p[i + 1] == 'f' ||
            static_check(p, i + 1);
    }
    static_assert(
        static_check(dfunction()), 
        "invalid dfunction"
    );
#endif

//==============================================================================
//==============================================================================

TEST_COMPONENT(000) 
{
    dprint(std::cout << dfunction() << '\n');
    const std::string name = dfunction();
    const size_t pos = name.find("dfunction");
    ASSERT_TRUE(pos != std::string::npos);
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FEATURE_DFUNCTION

