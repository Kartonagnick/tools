// [2021y-02m-20d][18:40:18] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_FOR_RVALUE

#include <tools/features.hpp>
#ifdef dHAS_CPP11
// #pragma message("build for msvc2015 (or newer) or other compiler")

#define dTEST_COMPONENT tools, types
#define dTEST_METHOD for_rvalue
#define dTEST_TAG tdd

#include <tools/types/common.hpp>
#include <string>

namespace me = ::tools;
//==============================================================================
namespace
{
    template<class t, dfor_rvalue(t&&)>
    constexpr bool is_rvalue_argument(t&&) noexcept { return true; }

    template<class t, dfor_not_rvalue(t&&)>
    constexpr bool is_rvalue_argument(t&&) noexcept { return false; }

    constexpr int val = 1;

    static_assert(
        is_rvalue_argument(1),
        "numeric costant is rvalue"
    );

    static_assert(
        !is_rvalue_argument(val),
        "global variable is not rvalue"
    );

}//namespace

//==============================================================================
//=== typical ==================================================================
TEST_COMPONENT(000)
{
    int v;
    const bool yes = is_rvalue_argument(v);
    ASSERT_TRUE(!yes);
}
TEST_COMPONENT(001)
{
    const bool yes = is_rvalue_argument(10);
    ASSERT_TRUE(yes);
}
TEST_COMPONENT(002)
{
    const bool yes = is_rvalue_argument(std::string("23"));
    ASSERT_TRUE(yes);
}
TEST_COMPONENT(003)
{
    std::string v;
    const bool yes = is_rvalue_argument(v);
    ASSERT_TRUE(!yes);
}

//==============================================================================
//==============================================================================
#endif // !dHAS_CPP11
#endif // !TEST_TOOLS_FOR_RVALUE


