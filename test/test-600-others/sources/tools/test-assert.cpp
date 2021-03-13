// [2021y-02m-25d][04:30:47] Idrisov Denis R.
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


    template<class a, class b>
    struct some
    {
        bool compare(const a v1, const b v2) const
        {
            return v1 == v2;
        }
    };

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

TEST_COMPONENT(004)
{
    dASSERT(some<int, int>().compare(1, 1));
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_ASSERT

