
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FLAG
#if !defined(_MSC_VER) || _MSC_VER >= 1700
// #pragma message("build for msvc2012 (or newer) or other compiler")

#define dTEST_COMPONENT tools
#define dTEST_METHOD flag
#define dTEST_TAG atomic_enum

#include <tools/flag.hpp>
#include <atomic>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    enum eFLAGS 
    { 
        eNONE  = 0, 
        eALL   = 1, 
        eONE   = 1<<1, 
        eTWO   = 1<<2,
        eTHREE = 1<<3
    };

    typedef std::atomic<eFLAGS> 
        atom_t;

    typedef me::flag<atom_t> 
        flag_t;

} // namespace

//==============================================================================
//==============================================================================

// --- ctors/operator=
TEST_COMPONENT(000)
{
    flag_t f;
    ASSERT_TRUE(f.is_empty());
    ASSERT_TRUE(!f.is_full());

    f.clear();
    ASSERT_TRUE(f.is_empty());
    ASSERT_TRUE(!f.is_full());

    f.full();
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(f.is_full());

    f = eONE;
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(!f.is_full());

    const int val = eALL;

    f = val;
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(f.is_full());
}
TEST_COMPONENT(001)
{
    flag_t f(eONE|eTWO);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(!f.is_full());

    const int val = eNONE;
    f = val;
    ASSERT_TRUE(f.is_empty());
    ASSERT_TRUE(!f.is_full());
}

// --- copy/move
TEST_COMPONENT(002)
{
    const int fd = eONE|eTWO;
    const flag_t f1(eONE|eTWO);
    const flag_t f2 = fd;

    ASSERT_TRUE(f2 == f1);
    ASSERT_TRUE(f2 == fd);
}

#ifdef dHAS_RVALUE_REFERENCES
TEST_COMPONENT(003)
{
    const int fd = eONE|eTWO;
    const flag_t f1(eONE|eTWO);
    const flag_t f2 = std::move(f1);

    ASSERT_TRUE(f2 == f1);
    ASSERT_TRUE(f1 == fd);
    ASSERT_TRUE(f2 == fd);
}
#endif

// --- operator ==
TEST_COMPONENT(004)
{
    const flag_t f1(eONE|eTWO);
    const flag_t f2(eONE|eTHREE);
    const flag_t f3 = eALL;
    const flag_t f4;
    const flag_t f5 = eONE|eTHREE;
    const flag_t f6 = eONE|eTWO;

    ASSERT_TRUE(f1 == f1);
    ASSERT_TRUE(f1 != f2);
    ASSERT_TRUE(f1 != f3);
    ASSERT_TRUE(f1 != f4);
    ASSERT_TRUE(f1 != f5);
    ASSERT_TRUE(f1 == f6);

    ASSERT_TRUE(f2 != f1);
    ASSERT_TRUE(f2 == f2);
    ASSERT_TRUE(f2 != f3);
    ASSERT_TRUE(f2 != f4);
    ASSERT_TRUE(f2 == f5);
    ASSERT_TRUE(f2 != f6);

    ASSERT_TRUE(f3 != f1);
    ASSERT_TRUE(f3 != f2);
    ASSERT_TRUE(f3 == f3);
    ASSERT_TRUE(f3 != f4);
    ASSERT_TRUE(f3 != f5);
    ASSERT_TRUE(f3 != f6);

    ASSERT_TRUE(f4 != f1);
    ASSERT_TRUE(f4 != f2);
    ASSERT_TRUE(f4 != f3);
    ASSERT_TRUE(f4 == f4);
    ASSERT_TRUE(f4 != f5);
    ASSERT_TRUE(f4 != f6);
}
TEST_COMPONENT(005)
{
    const flag_t f1(eONE|eTWO);
    const flag_t f2(eONE|eTHREE);
    const flag_t f3 = eALL;
    const flag_t f4;
    const flag_t f5 = eONE|eTHREE;
    const flag_t f6 = eONE|eTWO;

    ASSERT_TRUE(f1 == (eONE|eTWO)   );
    ASSERT_TRUE(f2 == (eONE|eTHREE) );
    ASSERT_TRUE(f3 == eALL);
    ASSERT_TRUE(f4 == eNONE);
    ASSERT_TRUE(f5 == (eONE|eTHREE) );
    ASSERT_TRUE(f6 == (eONE|eTWO)   );
}

// --- has
TEST_COMPONENT(006)
{
    flag_t f(eONE|eTWO);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(!f.is_full());
    ASSERT_TRUE(f.has(eONE|eTWO));
    ASSERT_TRUE(!f.has(eONE|eTHREE));
    ASSERT_TRUE(f.has(eONE));
    ASSERT_TRUE(!f.has(eALL));
    ASSERT_TRUE(!f.has(eNONE));
}
TEST_COMPONENT(007)
{
    flag_t f;
    ASSERT_TRUE(f.is_empty());
    ASSERT_TRUE(!f.is_full());
    ASSERT_TRUE(!f.has(eONE|eTWO));
    ASSERT_TRUE(!f.has(eONE|eTHREE));
    ASSERT_TRUE(!f.has(eALL));
    ASSERT_TRUE(f.has(eNONE));
}
TEST_COMPONENT(008)
{
    flag_t f(eALL);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(f.is_full());
    ASSERT_TRUE(f.has(eONE|eTWO));
    ASSERT_TRUE(f.has(eONE|eTHREE));
    ASSERT_TRUE(f.has(eALL));
    ASSERT_TRUE(!f.has(eNONE));
}

// --- has_any
TEST_COMPONENT(009)
{
    flag_t f(eONE|eTWO);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(!f.is_full());
    ASSERT_TRUE(f.has_any(eONE|eTWO));
    ASSERT_TRUE(f.has_any(eONE|eTHREE));
    ASSERT_TRUE(f.has_any(eONE));
    ASSERT_TRUE(!f.has_any(eTHREE));
    ASSERT_TRUE(f.has_any(eALL));
    ASSERT_TRUE(!f.has_any(eNONE));
}
TEST_COMPONENT(010)
{
    flag_t f;
    ASSERT_TRUE(f.is_empty());
    ASSERT_TRUE(!f.is_full());
    ASSERT_TRUE(!f.has_any(eONE|eTWO));
    ASSERT_TRUE(!f.has_any(eONE|eTHREE));
    ASSERT_TRUE(!f.has_any(eALL));
    ASSERT_TRUE(f.has_any(eNONE));
}
TEST_COMPONENT(011)
{
    flag_t f(eALL);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(f.is_full());
    ASSERT_TRUE(f.has_any(eONE|eTWO));
    ASSERT_TRUE(f.has_any(eONE|eTHREE));
    ASSERT_TRUE(f.has_any(eALL));
    ASSERT_TRUE(!f.has_any(eNONE));
}

// --- add
TEST_COMPONENT(012)
{
    flag_t f;
    ASSERT_TRUE(f.is_empty());
    ASSERT_TRUE(!f.is_full());

    f.add(eONE);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(!f.is_full());
    ASSERT_TRUE(f.has(eONE));
    ASSERT_TRUE(f.has_any(eONE));
    ASSERT_TRUE(!f.has_any(eTWO));
    ASSERT_TRUE(!f.has(eTWO));
    ASSERT_TRUE(f == eONE);

    f.add(eTWO);
    ASSERT_TRUE(!f.is_empty());
    ASSERT_TRUE(!f.is_full());
    ASSERT_TRUE(f.has(eONE|eTWO));
    ASSERT_TRUE(f.has_any(eONE|eTWO));
    
    ASSERT_TRUE(f.has(eONE));
    ASSERT_TRUE(f.has(eTWO));
    ASSERT_TRUE(!f.has(eTHREE));

    ASSERT_TRUE(f.has_any(eONE));
    ASSERT_TRUE(f.has_any(eTWO));
    ASSERT_TRUE(f.has_any(eTWO|eTHREE));

    ASSERT_TRUE(f == (eONE|eTWO) );

    f.add(eTHREE);
    ASSERT_TRUE(f == (eONE|eTWO|eTHREE) );
}
TEST_COMPONENT(013)
{
    flag_t f = eONE|eTWO;
    ASSERT_TRUE(f == (eONE|eTWO) );
    f.add(eALL);
    ASSERT_TRUE(f == 1);
}
TEST_COMPONENT(014)
{
    flag_t f = eONE|eTWO;
    ASSERT_TRUE(f == (eONE|eTWO) );
    f.add(eNONE);
    ASSERT_TRUE(f == (eONE|eTWO) );
}
TEST_COMPONENT(015)
{
    flag_t f = eNONE|eONE|eTWO;
    ASSERT_TRUE(f == (eONE|eTWO) );
}
TEST_COMPONENT(016)
{
    flag_t f = eALL|eONE|eTWO;
    ASSERT_TRUE(f == eALL);
}

// --- del
TEST_COMPONENT(017)
{
    flag_t f = eONE|eTWO|eTHREE;
    ASSERT_TRUE(f == (eONE|eTWO|eTHREE));
    f.del(eTHREE);
    ASSERT_TRUE(f == (eONE|eTWO));

    f.del(eTWO);
    ASSERT_TRUE(f == eONE);

    f.del(eONE);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(018)
{
    flag_t f = eONE|eTWO|eTHREE;
    ASSERT_TRUE(f == (eONE|eTWO|eTHREE));
    f.del(eALL);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(019)
{
    flag_t f = eONE|eTWO|eTHREE;
    ASSERT_TRUE(f == (eONE|eTWO|eTHREE));
    f.del(eNONE);
    ASSERT_TRUE(f == (eONE|eTWO|eTHREE));
}
TEST_COMPONENT(020)
{
    flag_t f = eALL;
    ASSERT_TRUE(f == eALL);
    f.del(eALL);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(021)
{
    flag_t f = eNONE;
    ASSERT_TRUE(f == eNONE);
    f.del(eNONE);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(022)
{
    flag_t f = eNONE;
    ASSERT_TRUE(f == eNONE);
    f.del(eALL);
    ASSERT_TRUE(f == eNONE);
}

// --- valid_only
TEST_COMPONENT(023)
{
    flag_t f = eTWO|eTHREE;
    f.valid_only(eONE|eTWO);
    ASSERT_TRUE(f == eTWO);
}
TEST_COMPONENT(024)
{
    flag_t f = eNONE;
    f.valid_only(eONE|eTWO);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(025)
{
    flag_t f = eNONE;
    f.valid_only(eNONE);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(026)
{
    flag_t f = eNONE;
    f.valid_only(eALL);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(027)
{
    flag_t f = eALL;
    f.valid_only(eONE|eTWO);
    ASSERT_TRUE(f == (eONE|eTWO));
}
TEST_COMPONENT(028)
{
    flag_t f = eALL;
    f.valid_only(eALL);
    ASSERT_TRUE(f == eALL);
}
TEST_COMPONENT(029)
{
    flag_t f = eALL;
    f.valid_only(eNONE);
    ASSERT_TRUE(f == eNONE);
}

// --- change
TEST_COMPONENT(030)
{
    flag_t f = eONE|eTWO;
    f.change(eONE|eTWO, eTHREE);
    ASSERT_TRUE(f == eTHREE);
}
TEST_COMPONENT(031)
{
    flag_t f = eONE|eTWO;
    f.change(eONE|eTWO, eALL);
    ASSERT_TRUE(f == eALL);
}
TEST_COMPONENT(032)
{
    flag_t f = eONE|eTWO;
    f.change(eONE|eTWO, eNONE);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(033)
{
    flag_t f = eONE|eTWO;
    f.change(eONE, eALL);
    ASSERT_TRUE(f == eALL);
}
TEST_COMPONENT(034)
{
    flag_t f = eONE|eTWO;
    f.change(eONE, eNONE);
    ASSERT_TRUE(f == eNONE);
}
TEST_COMPONENT(035)
{
    flag_t f = eONE|eTWO|eTHREE;
    f.change(eONE, eTHREE);
    ASSERT_TRUE(f == (eTWO|eTHREE));
}

TEST_COMPONENT(036)
{
    flag_t f = eONE|eTWO;
    const int v = f.as<int>();
    ASSERT_TRUE(v == (eONE|eTWO));
}
//==============================================================================
//==============================================================================
#endif // !defined(_MSC_VER) || _MSC_VER >= 1700
#endif // ! TEST_TOOLS_FLAG



