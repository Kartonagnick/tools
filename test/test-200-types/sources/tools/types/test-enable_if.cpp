// [2021y-03m-10d][05:41:42] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_ENABLE_IF

#define dTEST_COMPONENT tools, types, traits
#define dTEST_METHOD enable_if
#define dTEST_TAG tdd

#include <tools/types/traits.hpp>
#include <tools/features.hpp>
namespace me = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace
{
    enum eINT_TYPE  { eINT  = 1 };
    enum eBOOL_TYPE { eBOOL = 0 };

    template<class t>
    typename me::enable_if<me::is_same<t, int>::value, eINT_TYPE>::type 
    foo(t){ return eINT; }

    template<class t>
    typename me::enable_if<me::is_same<t, bool>::value, eBOOL_TYPE>::type
    foo(t){ return eBOOL; }

} // namespace

//==============================================================================
//==============================================================================
TEST_COMPONENT(000)
{
    ASSERT_TRUE(foo(0)    == eINT );
    ASSERT_TRUE(foo(true) == eBOOL);
}

#endif // !TEST_ENABLE_IF

