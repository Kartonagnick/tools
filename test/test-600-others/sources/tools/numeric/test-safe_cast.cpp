#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_NUMERIC

#define dTEST_COMPONENT tools, numeric
#define dTEST_METHOD safe_cast
#define dTEST_TAG cpp11

#ifdef dDISABLE_SAFE_CAST
#if 0
    #if defined(__GNUC__) || defined(__MINGW__) || defined(__MINGW32__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wconversion"
        #pragma GCC diagnostic ignored "-Wsign-conversion"
    #endif
#endif
#endif

#include <tools/numeric.hpp>
#include <cstddef>

namespace me = ::tools::numeric;
//=================================================================================
//=== [usage] =====================================================================
namespace
{
    int foo() dNOEXCEPT { return  1; }
    int bar() dNOEXCEPT { return -1; }

} // namespace

TEST_COMPONENT(000)
{
    size_t v = me::safe_cast<size_t>(foo());
    ASSERT_TRUE(v == 1u);
}

TEST_COMPONENT(001)
{
    #ifdef dDISABLE_SAFE_CAST
        size_t v = me::safe_cast<size_t>(bar());
        ASSERT_TRUE(v == size_t(-1));
    #else
        ASSERT_THROW(me::safe_cast<size_t>(bar()), std::exception);
    #endif
}

TEST_COMPONENT(002)
{
    #ifdef dDISABLE_SAFE_CAST
        size_t v = me::assert_safe_cast<size_t>(bar());
        ASSERT_TRUE(v == size_t(-1));
    #else
        ASSERT_DEATH_DEBUG(me::assert_safe_cast<size_t>(bar()));
    #endif
}

#ifndef dDISABLE_SAFE_CAST
#ifdef dHAS_ENUM_CLASS
TEST_COMPONENT(003)
{
    #ifndef NDEBUG
    enum class u_enum : unsigned char { eONE = 128 };
    enum class s_enum : signed   char { eSIG = 125 };
    ASSERT_DEATH_DEBUG(
        me::assert_safe_cast<s_enum>(u_enum::eONE)
    );
    #endif
}
TEST_COMPONENT(004)
{
    #ifndef NDEBUG
    enum class u_enum : unsigned char { eONE = 128 };
    enum class s_enum : signed   char { eSIG = 125 };
    ASSERT_DEATH_DEBUG(me::assert_safe_cast<s_enum>(128));
    #endif
}
#endif // !dHAS_ENUM_CLASS
#endif // !dDISABLE_SAFE_CAST

#ifdef dDISABLE_SAFE_CAST
#if 0

    #if defined(__GNUC__) || defined(__MINGW__) || defined(__MINGW32__)
        #pragma GCC diagnostic pop
    #endif
#endif
#endif

//=================================================================================
//=================================================================================
#endif // !TEST_TOOLS_NUMERIC_CAST
