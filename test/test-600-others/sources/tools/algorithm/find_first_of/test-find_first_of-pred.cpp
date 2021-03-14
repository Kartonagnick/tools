// [2021y-03m-14d][23:06:58] Idrisov Denis R.
#include <mygtest/modern.hpp>
#ifdef TEST_TOOLS_FIND_FIRST_OF

#define dTEST_COMPONENT tools, algorithm
#define dTEST_METHOD find_first_of
#define dTEST_TAG pred

#include <tools/algorithm/find_first_of.hpp>
#include "test-staff.hpp"

namespace me = ::tools;
using namespace ::staff;
//==============================================================================
//=== [TDD] ====================================================================
namespace
{
    typedef str_t::const_iterator it;

    bool compare(const char a, const char b)
    {
        return a == b;
    }

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const str_t text = "123;456";
    const str_t symb = " ,;";
    const it etalon = text.begin() + 3;
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end(),
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(001)
{
    const str_t text = "123456";
    const str_t symb = " ,;";
    const it etalon = text.end();
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end(),
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(002)
{
    const str_t text = "123456";
    const str_t symb = "";
    const it etalon = text.end();
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end(),
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(003)
{
    const str_t text = "";
    const str_t symb = " ,;";
    const it etalon = text.end();
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end(),
        compare
    );
    ASSERT_TRUE(result == etalon);
}

//==============================================================================
//==============================================================================

TEST_COMPONENT(004)
{
    const str_t text  = "123;456";
    const char symb[] = " ,;";
    const it etalon   = text.begin() + 3;
    const it result   = me::find_first_of(
        text.begin(), text.end(), symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(005)
{
    const str_t text  = "123456";
    const char symb[] = " ,;";
    const it etalon   = text.end();
    const it result   = me::find_first_of(
        text.begin(), text.end(), symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(006)
{
    const str_t text  = "123456";
    const char symb[] = "";
    const it etalon   = text.end();
    const it result   = me::find_first_of(
        text.begin(), text.end(), symb, symb + 1,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(007)
{
    const str_t text  = "";
    const char symb[] = " ,;";
    const it etalon  = text.end();
    const it result  = me::find_first_of(
        text.begin(), text.end(), symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}

//==============================================================================
//==============================================================================

TEST_COMPONENT(008)
{
    const char text[]  = "123;456";
    const char symb[]  = " ,;";
    const char* etalon = text + 3;
    const char* result = me::find_first_of(
        text, text + 7, symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(009)
{
    const char text[]  = "123456";
    const char symb[]  = " ,;";
    const char* etalon = text + 6;
    const char* result = me::find_first_of(
        text, text + 6, symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(010)
{
    const char text[]  = "123456";
    const char symb[]  = "";
    const char* etalon = text + 6;
    const char* result = me::find_first_of(
        text, text + 6, symb, symb + 1,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(011)
{
    const char text[]  = "";
    const char symb[]  = " ,;";
    const char* etalon = text;
    const char* result = me::find_first_of(
        text, text + 0, symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(012)
{
    const char text[]  = "";
    const char symb[]  = " ,;";
    const char* etalon = text;
    const char* result = me::find_first_of(
        text, text, symb, symb + 3,
        compare
    );
    ASSERT_TRUE(result == etalon);
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FIND_FIRST_OF


