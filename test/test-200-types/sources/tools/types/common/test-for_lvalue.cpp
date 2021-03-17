// [2021y-02m-20d][18:40:18] Idrisov Denis R.
// [2021y-03m-17d][20:47:09] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_FOR_LVALUE

#include <tools/features.hpp>
#ifdef dHAS_USING_ALIAS
// #pragma message("build for msvc2013 (or newer) or other compiler")

#define dTEST_COMPONENT tools, types
#define dTEST_METHOD for_lvalue
#define dTEST_TAG tdd

#include <tools/types/common.hpp>
#include <string>

namespace me = ::tools;
//==============================================================================
namespace
{
    #ifdef dHAS_CONSTEXPR_CPP11
        template<class t, dfor_lvalue(t&&)>
        constexpr bool is_lvalue_argument(t&&) noexcept { return true; }

        template<class t, dfor_not_lvalue(t&&)>
        constexpr bool is_lvalue_argument(t&&) noexcept { return false; }

        constexpr int val = 1;

        static_assert(
            !is_lvalue_argument(1),
            "numeric costant is not lvalue"
        );

        static_assert(
            is_lvalue_argument(val),
            "global variable is lvalue"
        );
    #else
        template<class t>
        inline me::for_lvalue<t, bool>
        is_lvalue_argument(t&&) dNOEXCEPT { return true; }

        template<class t>
        inline me::for_not_lvalue<t, bool>
        is_lvalue_argument(t&&) dNOEXCEPT { return false; }
    #endif // !dHAS_CONSTEXPR_CPP11

}//namespace
//==============================================================================
//=== typical ==================================================================
TEST_COMPONENT(000)
{
    int v;
    const bool yes = is_lvalue_argument(v);
    ASSERT_TRUE(yes);
}
TEST_COMPONENT(001)
{
    const bool yes = is_lvalue_argument(10);
    ASSERT_TRUE(!yes);
}
TEST_COMPONENT(002)
{
    const bool yes = is_lvalue_argument(std::string("23"));
    ASSERT_TRUE(!yes);
}
TEST_COMPONENT(003)
{
    std::string v;
    const bool yes = is_lvalue_argument(v);
    ASSERT_TRUE(yes);
}
//==============================================================================
//==============================================================================

#endif // !dHAS_USING_ALIAS
#endif // !TEST_TOOLS_FOR_RVALUE


