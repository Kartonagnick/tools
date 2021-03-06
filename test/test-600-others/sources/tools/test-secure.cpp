// [2021y-02m-20d][00:01:43] Idrisov Denis R.

#ifdef _MSC_VER
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================
#ifdef TEST_TOOLS_SECURE

#include <tools/secure.hpp>
#include <string>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) secure_##n

namespace me = ::tools;
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const char* key = "cryptKey";
    const char* password = "123-test";

    const me::str_t secret = me::encrypt(password, key);
    dprint(std::cout << "secret: " << secret << '\n');

    const me::str_t pass = me::decrypt(secret, key);
    ASSERT_TRUE(password == pass);
}

//==============================================================================
#endif // !TEST_TOOLS_SECURITY
#endif // !_MSC_VER



