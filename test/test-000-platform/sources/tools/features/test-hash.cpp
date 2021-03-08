// [2021y-03m-03d][19:14:11] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_HASH

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_HASH
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifdef dHAS_HASH
    dMESSAGE("[test] tools: enabled -> dHAS_HASH")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_HASH")
    #include <functional>
#endif

//==============================================================================
//==============================================================================
namespace {} // namespace

#ifdef dHAS_HASH
TEST_COMPONENT(000)
{
    const std::hash<int> h;
    dprint(std::cout << "hash = " << h(100) << '\n');
    (void)h;
}
#endif

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_HASH



