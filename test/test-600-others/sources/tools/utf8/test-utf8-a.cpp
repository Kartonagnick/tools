// [2020y-12m-01d][14:06:17] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================

#ifdef TEST_TOOLS_UTF8

#define dTEST_COMPONENT tools, utf8
#define dTEST_METHOD convert
#define dTEST_TAG char

#include <tools/utf8.hpp>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    typedef ::std::string  str_t;
    typedef ::std::wstring str_w;

} // namespace

//==============================================================================
//==============================================================================

// --- me::utf8::convert(nullptr) assert/UB
TEST_COMPONENT(000)
{
    const char* null = 0;
    (void) null;
    ASSERT_DEATH_DEBUG(me::utf8::convert(null));
}

// --- utf8::convert(from char*)        
TEST_COMPONENT(001)
{
    const str_w w_conv = me::utf8::convert("12345", 5);
    const str_t a_conv = me::utf8::convert(w_conv);
    ASSERT_TRUE(a_conv == "12345");
}

#ifdef dHAS_CPP11
TEST_COMPONENT(002)
{
    const str_w w_conv = me::utf8::convert(u8"привет мир");
    const str_t a_conv = me::utf8::convert(w_conv);
    ASSERT_TRUE(a_conv == u8"привет мир");
}

// --- utf8::convert_to<char>(from char*)
TEST_COMPONENT(003)
{
    ::str_t a_conv = "12345";
    using re = decltype(me::utf8::convert_to<char>(a_conv));

    static_assert(
        ::std::is_same<::str_t&, re>::value,
        "error: expected 'str_t&'"
    );

    ::str_t& a_result
        = me::utf8::convert_to<char>(a_conv);

    ASSERT_TRUE(a_result == a_conv);
}
TEST_COMPONENT(004)
{
    using re = decltype(me::utf8::convert_to<char>(str_t("12345")));
    static_assert(
        ::std::is_same<::str_t, re>::value,
        "error: expected 'str_t'"
    );
    const auto a_result
        = me::utf8::convert_to<char>(str_t("12345"));

    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(005)
{
    using re = decltype(me::utf8::convert_to<char>("12345"));
    static_assert(
        ::std::is_same<const char(&)[6], re>::value,
        "error: expected 'const char(&)[6]'"
    );

    const auto& a_result
        = me::utf8::convert_to<char>("12345");

    const ::str_t etalon = "12345";
    ASSERT_TRUE(a_result == etalon);
}
TEST_COMPONENT(006)
{
    const char* ptr = "12345";
    using re = decltype(me::utf8::convert_to<char>(ptr));

    static_assert(
        ::std::is_same<const char*&, re>::value,
        "error: expected 'const char*&'"
    );

    const auto a_result
        = me::utf8::convert_to<char>(ptr);

    const ::str_t etalon = "12345";
    ASSERT_TRUE(a_result == etalon);
}
TEST_COMPONENT(007)
{
    const char* ptr = u8"привет мир";
    using re = decltype(me::utf8::convert_to<char>(ptr));

    static_assert(
        ::std::is_same<const char*&, re>::value,
        "error: expected 'const char*&'"
    );

    const auto a_result
        = me::utf8::convert_to<char>(ptr);

    const ::str_t etalon = u8"привет мир";
    ASSERT_TRUE(a_result == etalon);
}

// --- utf8::convert_to<char>(from wchar_t*)
TEST_COMPONENT(008)
{
    ::str_w w_conv = L"12345";
    using re = decltype(me::utf8::convert_to<char>(w_conv));

    static_assert(
        ::std::is_same<::str_t, re>::value,
        "error: expected 'str_t&'"
    );

    ::str_t a_result
        = me::utf8::convert_to<char>(w_conv);
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(009)
{
    using re = decltype(me::utf8::convert_to<char>(str_w(L"12345")));
    static_assert(
        ::std::is_same<::str_t, re>::value,
        "error: expected 'str_t'"
    );
    const auto a_result
        = me::utf8::convert_to<char>(str_w(L"12345"));
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(010)
{
    using re = decltype(me::utf8::convert_to<char>(L"12345"));
    static_assert(
        ::std::is_same<str_t, re>::value,
        "error: expected 'str_t'"
    );

    const str_t a_result
        = me::utf8::convert_to<char>(L"12345");
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(011)
{
    const wchar_t* ptr = L"12345";
    using re = decltype(me::utf8::convert_to<char>(ptr));
    static_assert(
        ::std::is_same<str_t, re>::value,
        "error: expected 'str_t'"
    );

    const str_t a_result
        = me::utf8::convert_to<char>(ptr);
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(012)
{
    using re = decltype(me::utf8::convert_to<char>(L"привет мир"));
    static_assert(
        ::std::is_same<str_t, re>::value,
        "error: expected 'str_t'"
    );
    const str_t a_result
        = me::utf8::convert_to<char>(L"привет мир");
    ASSERT_TRUE(a_result == u8"привет мир");
}
#endif // !dHAS_CPP11
//==============================================================================
//==============================================================================
#endif //!TEST_TOOLS_UTF8



