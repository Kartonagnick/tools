// [2021y-03m-01d][03:08:18] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_ERRNO

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) errno_##n

#include <tools/errno.hpp>
#include <cmath> 

#ifdef _WIN32
    #include <tools/windows.hpp>
#endif

namespace me = ::TEST_CASE_NAME;
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    double re = ::std::sqrt(-1.0);
    (void)re;
    const ::std::string msg = me::get_errno();
    dprint(::std::cout << "error_message: " << msg << '\n');
    ASSERT_TRUE(!msg.empty());
}

TEST_COMPONENT(001)
{
    #ifdef _WIN32
    ::HANDLE h = NULL;
    const ::BOOL success = ::CloseHandle(h);
    ASSERT_TRUE(success == FALSE);
    const ::std::string msg = me::get_last_error();
    dprint(::std::cout << "error_message: " << msg << '\n');
    ASSERT_TRUE(!msg.empty());
    #endif
}

#endif // !TEST_TOOLS_ERRNO

