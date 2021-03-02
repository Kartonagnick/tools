// [2021y-02m-25d][04:21:08] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_CPP11

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_CPP14
#define dTEST_TAG tdd

#include <tools/features.hpp>

#include <cassert>

#ifdef dHAS_CPP11
    dMESSAGE("[test] tools: enabled -> dHAS_CPP11")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_CPP11")
#endif

//==============================================================================
//==============================================================================

namespace 
{
    #ifdef dHAS_CPP14

        #ifndef dHAS_CONSTEXPR_CPP14
            #error must be defined
        #endif

        template<class s>
        dCONSTEXPR_CPP14 size_t len(s&& text) noexcept
        {
            assert(text);
            const auto* p = text;
            while (*p != 0)
                ++p;
            return static_cast<size_t>(p - text);
        }
        constexpr const char* text = "1234";
        static_assert(len(text) == 4, "expected 4");
    #endif

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000) {}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FEATURE_CPP11

