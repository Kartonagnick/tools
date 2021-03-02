// [2021y-02m-25d][04:21:08] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_CPP11

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_CPP11
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifdef dHAS_CPP11
    dMESSAGE("[test] tools: enabled -> dHAS_CPP11")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_CPP11")
#endif

//==============================================================================
//==============================================================================

namespace 
{
    #ifdef dHAS_CPP11
        constexpr size_t len(const char* p, const size_t i = 0)
            { return p[i] == 0 ? i : len(p, i + 1); }

        constexpr const char* ptr = "1234";

        static_assert(len(ptr) == 4, "expected 4");
    #endif

    #ifdef dHAS_CONSTEXPR_CPP11
        constexpr size_t foo(const char* p, const size_t i = 0)
            { return p[i] == 0 ? i : foo(p, i + 1); }

        constexpr const char* msg = "1234";

        static_assert(foo(msg) == 4, "expected 4");
    #endif

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000) {}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FEATURE_CPP11

