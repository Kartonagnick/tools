// [2021y-02m-25d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_CPP17

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_CPP17
#define dTEST_TAG tdd

#include <tools/features.hpp>
#include <string>

#ifdef dHAS_CPP17
    dMESSAGE("[test] tools: enabled -> dHAS_CPP17")
#else
    dMESSAGE("[test] tools: disabled -> dHAS_CPP17")
#endif

//==============================================================================
//==============================================================================

namespace 
{
    #ifdef dHAS_CPP17
        [[nodiscard]] int foo() { return 1;  }    
    #endif

    dNODISCARD int bar() { return 1; }

    #ifdef dHAS_CPP17
    struct book
    {
        std::string title;
        unsigned year;
    };

    book getBook()
    {
        return { "123", 1997 };
    }
    #endif

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000) 
{
    ASSERT_TRUE(bar() == 1);

    #ifdef dHAS_CPP17
    ASSERT_TRUE(foo() == 1);

    auto [title, year] = getBook();
    ASSERT_TRUE(title == "123");
    ASSERT_TRUE(year  == 1997 );
    #endif
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_FEATURE_CPP17

