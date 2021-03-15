// [2019y-10m-24d][19:22:08] Idrisov Denis R.
// [2021y-03m-08d][03:41:01] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_FIND_FIRST_OF

#define dTEST_COMPONENT tools, algorithm
#define dTEST_METHOD find_first_of
#define dTEST_TAG tdd

#include <tools/algorithm/find_first_of.hpp>
#include "test-staff.hpp"

namespace me = ::tools;
using namespace ::staff;
//==============================================================================
//=== [TDD] ====================================================================
namespace
{
    typedef str_t::const_iterator it;

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const str_t text = "123;456";
    const str_t symb = " ,;";
    const it etalon = text.begin() + 3;
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end()
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(001)
{
    const str_t text = "123456";
    const str_t symb = " ,;";
    const it etalon = text.end();
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end()
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(002)
{
    const str_t text = "123456";
    const str_t symb = "";
    const it etalon = text.end();
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end()
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(003)
{
    const str_t text = "";
    const str_t symb = " ,;";
    const it etalon = text.end();
    const it result = me::find_first_of(
        text.begin(), text.end(), symb.begin(), symb.end()
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
        text.begin(), text.end(), symb, symb + 3
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(005)
{
    const str_t text  = "123456";
    const char symb[] = " ,;";
    const it etalon   = text.end();
    const it result   = me::find_first_of(
        text.begin(), text.end(), symb, symb + 3
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(006)
{
    const str_t text  = "123456";
    const char symb[] = "";
    const it etalon   = text.end();
    const it result   = me::find_first_of(
        text.begin(), text.end(), symb, symb + 1
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(007)
{
    const str_t text  = "";
    const char symb[] = " ,;";
    const it etalon  = text.end();
    const it result  = me::find_first_of(
        text.begin(), text.end(), symb, symb + 3
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
        text, text + 7, symb, symb + 3
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(009)
{
    const char text[]  = "123456";
    const char symb[]  = " ,;";
    const char* etalon = text + 6;
    const char* result = me::find_first_of(
        text, text + 6, symb, symb + 3
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(010)
{
    const char text[]  = "123456";
    const char symb[]  = "";
    const char* etalon = text + 6;
    const char* result = me::find_first_of(
        text, text + 6, symb, symb + 1
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(011)
{
    const char text[]  = "";
    const char symb[]  = " ,;";
    const char* etalon = text;
    const char* result = me::find_first_of(
        text, text + 0, symb, symb + 3
    );
    ASSERT_TRUE(result == etalon);
}
TEST_COMPONENT(012)
{
    const char text[]  = "";
    const char symb[]  = " ,;";
    const char* etalon = text;
    const char* result = me::find_first_of(
        text, text, symb, symb + 3
    );
    ASSERT_TRUE(result == etalon);
}

//==============================================================================
//==============================================================================
#ifndef NDEBUG
TEST_COMPONENT(013)
{
    const char* b  = 0;
    const char* e  = "";
    const char s[] = " ,;";
    const char* r = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, s, s + 3));
    (void)b;
    (void)e;
    (void)s;
    (void)r;
}
TEST_COMPONENT(014)
{
    const char* b  = "";
    const char* e  = 0;
    const char s[] = " ,;";
    const char* r = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, s, s + 3));
    (void)b;
    (void)e;
    (void)s;
    (void)r;
}
TEST_COMPONENT(015)
{
    const char* b  = "";
    const char* e  = "";
    const char* sb = 0;
    const char* se = "";
    const char* r  = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, sb, se));
    (void)b;
    (void)e;
    (void)sb;
    (void)se;
    (void)r;
}
TEST_COMPONENT(016)
{
    const char* b  = "";
    const char* e  = "";
    const char* sb = "";
    const char* se = 0;
    const char* r  = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, sb, se));
    (void)b;
    (void)e;
    (void)sb;
    (void)se;
    (void)r;
}
TEST_COMPONENT(017)
{
    const char* b  = "";
    const char* e  = 0;
    const char* sb = "";
    const char* se = 0;
    const char* r  = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, sb, se));
    (void)b;
    (void)e;
    (void)sb;
    (void)se;
    (void)r;
}
TEST_COMPONENT(018)
{
    const char* b  = "";
    const char* e  = 0;
    const char* sb = 0;
    const char* se = 0;
    const char* r  = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, sb, se));
    (void)b;
    (void)e;
    (void)sb;
    (void)se;
    (void)r;
}
TEST_COMPONENT(019)
{
    const char* b  = 0;
    const char* e  = 0;
    const char* sb = 0;
    const char* se = 0;
    const char* r  = 0;
    ASSERT_DEATH_DEBUG(r = me::find_first_of(b, e, sb, se));
    (void)b;
    (void)e;
    (void)sb;
    (void)se;
    (void)r;
}
#endif

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FIND_FIRST_OF


