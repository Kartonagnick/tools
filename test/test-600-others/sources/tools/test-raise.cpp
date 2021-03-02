// [2021y-02m-20d][00:01:43] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_RAISE

#include <tools/raise.hpp>
#include <string>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) raise_##n

//==============================================================================
//=== TDD ======================================================================
namespace
{
    void execute_raise()
    {
        dRAISE("trololo");
    }

    void test_raise_macros()  
    { 
        #ifdef NDEBUG
            // release version
            EXPECT_THROW(execute_raise(), std::runtime_error);
        #else
            // debug version
            ASSERT_DEATH(execute_raise(), ".*");
        #endif
    }

}//namespace
//==============================================================================
//==============================================================================

// --- dRAISE
TEST_COMPONENT(000)
{
    test_raise_macros();
}

TEST_COMPONENT(001)
{
    #ifdef NDEBUG
    // release version
    bool was_exception = false;

    try
    {
        dRAISE("trololo");
    }
    catch(const ::std::exception& e)
    {
        const ::std::string reason = e.what();
        ASSERT_TRUE(reason == "trololo");
        was_exception = true;
    }
    ASSERT_TRUE(was_exception);
    #endif
}

// --- dVERIFY
TEST_COMPONENT(002)
{
    int* p = 0; (void) p;
    #ifdef NDEBUG
        // release version
        ASSERT_THROW(dVERIFY(p), ::std::exception);
    #else
        ASSERT_DEATH(dVERIFY(p), ".*");
    #endif
}

//==============================================================================
#endif // !TEST_TOOLS_RAISE



