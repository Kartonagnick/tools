// [2019y-10m-24d][19:22:08] Idrisov Denis R.
// [2021y-03m-08d][03:41:01] Idrisov Denis R.
#include <mygtest/test-list.hpp>

#ifdef TEST_TOOLS_MARKER

#include <tools/marker.hpp>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) marker_##n

namespace me = ::TEST_CASE_NAME;
//==============================================================================
//==============================================================================
namespace
{
    typedef me::marker<int, int> 
        marker;

}//namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    marker control;
    ASSERT_TRUE( control.add(0, 10));
    ASSERT_TRUE( control.add(0, 11));
    ASSERT_TRUE( control.add(1, 11));
    
    ASSERT_TRUE(!control.add(0, 10));
    ASSERT_TRUE(!control.add(0, 11));
    ASSERT_TRUE(!control.add(1, 11));
}

TEST_COMPONENT(001)
{
    marker control;
    ASSERT_TRUE(!control.exists(0, 10));
    ASSERT_TRUE(!control.exists(0, 11));
    ASSERT_TRUE(!control.exists(1, 11));

    ASSERT_TRUE( control.add(0, 10));
    ASSERT_TRUE( control.add(0, 11));
    ASSERT_TRUE( control.add(1, 11));

    ASSERT_TRUE(!control.add(0, 10));
    ASSERT_TRUE(!control.add(0, 11));
    ASSERT_TRUE(!control.add(1, 11));
    
    ASSERT_TRUE( control.exists(0, 10));
    ASSERT_TRUE( control.exists(0, 11));
    ASSERT_TRUE( control.exists(1, 11));

    ASSERT_TRUE( control.del(0, 10));
    ASSERT_TRUE( control.del(0, 11));
    ASSERT_TRUE( control.del(1, 11));

    ASSERT_TRUE(!control.exists(0, 10));
    ASSERT_TRUE(!control.exists(0, 11));
    ASSERT_TRUE(!control.exists(1, 11));

    ASSERT_TRUE(!control.del(0, 10));
    ASSERT_TRUE(!control.del(0, 11));
    ASSERT_TRUE(!control.del(1, 11));
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_MARKER


