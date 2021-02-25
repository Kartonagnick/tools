
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_ASSERT

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) assert_##n

#include <tools/assert.hpp>
//==============================================================================
//=== TDD ======================================================================
namespace
{
    void foo()
    {
        const bool success = false;
        dprint(std::cout << "call...\n");
        dASSERT(success);
        (void) success;
    }

    #ifndef NDEBUG
    void bar()
    {
        const bool success = false;
        dprint(std::cout << "call...\n");
        assert(success);
    }
    #endif 

}//namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const bool success = true;
    dASSERT(success);
    (void)success;

    #ifndef NDEBUG
    // --- debug
    assert(success);
    #endif 
}

TEST_COMPONENT(001)
{
    ASSERT_DEATH_DEBUG(bar());
}

TEST_COMPONENT(002)
{
    ASSERT_DEATH_DEBUG(foo());
}

TEST_COMPONENT(003)
{
    void(*ptr)() = foo;
    ASSERT_TRUE(ptr);
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_ASSERT

