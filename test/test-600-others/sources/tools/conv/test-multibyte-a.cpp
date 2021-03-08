// [2019y-10m-24d][19:22:08] Idrisov Denis R.
//==============================================================================
//==============================================================================

#include <mygtest/modern.hpp>
//==============================================================================

#ifdef TEST_TOOLS_CONV

#define dTEST_COMPONENT tools, conv, multibyte
#define dTEST_METHOD convert
#define dTEST_TAG char

#include <tools/conv.hpp>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    typedef ::std::string  str_t;
    typedef ::std::wstring str_w;
    str_t g_locale_name;

} // namespace

//==============================================================================
//==============================================================================

// --- prepare
TEST_COMPONENT(000)
{
    dprint(std::cout << "origin locale: '" << g_locale_name << "'\n");
    const char* p = ::setlocale(LC_ALL, "");
    ASSERT_TRUE(p);
}

// --- me::multibyte::convert(nullptr) assert/UB
TEST_COMPONENT(001)
{
    const char* null = 0;
    (void) null;
    ASSERT_DEATH_DEBUG(me::multibyte::convert(null));
}

// --- utf8::convert(from char*)        
TEST_COMPONENT(002)
{
    const str_w w_conv = me::multibyte::convert("12345", 5);
    const str_t a_conv  = me::multibyte::convert(w_conv);
    ASSERT_TRUE(a_conv == "12345");
}

#ifdef dHAS_CPP11

TEST_COMPONENT(003)
{
    const str_w w_conv = me::multibyte::convert(u8"привет мир");
    const str_t a_conv  = me::multibyte::convert(w_conv);
    ASSERT_TRUE(a_conv == u8"привет мир");
}

// --- utf8::convert_to<char>(from char*)
TEST_COMPONENT(004)
{
    ::str_t a_conv = "12345";
    using re = decltype(me::multibyte::convert_to<char>(a_conv));

    static_assert(
        ::std::is_same<::str_t&, re>::value,
        "error: expected 'str_t&'"
    );

    ::str_t& a_result
        = me::multibyte::convert_to<char>(a_conv);

    ASSERT_TRUE(a_result == a_conv);
}
TEST_COMPONENT(005)
{
    using re = decltype(me::multibyte::convert_to<char>(str_t("12345")));
    static_assert(
        ::std::is_same<::str_t, re>::value,
        "error: expected 'str_t'"
    );
    const auto a_result
        = me::multibyte::convert_to<char>(str_t("12345"));

    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(006)
{
    using re = decltype(me::multibyte::convert_to<char>("12345"));
    static_assert(
        ::std::is_same<const char(&)[6], re>::value,
        "error: expected 'const char(&)[6]'"
    );

    const auto& a_result
        = me::multibyte::convert_to<char>("12345");

    const ::str_t etalon = "12345";
    ASSERT_TRUE(a_result == etalon);
}
TEST_COMPONENT(007)
{
    const char* ptr = "12345";
    using re = decltype(me::multibyte::convert_to<char>(ptr));

    static_assert(
        ::std::is_same<const char*&, re>::value,
        "error: expected 'const char*&'"
    );

    const auto a_result
        = me::multibyte::convert_to<char>(ptr);

    const ::str_t etalon = "12345";
    ASSERT_TRUE(a_result == etalon);
}
TEST_COMPONENT(008)
{
    const char* ptr = u8"привет мир";
    using re = decltype(me::multibyte::convert_to<char>(ptr));

    static_assert(
        ::std::is_same<const char*&, re>::value,
        "error: expected 'const char*&'"
    );

    const auto a_result
        = me::multibyte::convert_to<char>(ptr);

    const ::str_t etalon = u8"привет мир";
    ASSERT_TRUE(a_result == etalon);
}

// --- utf8::convert_to<char>(from wchar_t*)
TEST_COMPONENT(009)
{
    ::str_w w_conv = L"12345";
    using re = decltype(me::multibyte::convert_to<char>(w_conv));

    static_assert(
        ::std::is_same<::str_t, re>::value,
        "error: expected 'str_t&'"
    );

    ::str_t a_result
        = me::multibyte::convert_to<char>(w_conv);
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(010)
{
    using re = decltype(me::multibyte::convert_to<char>(str_w(L"12345")));
    static_assert(
        ::std::is_same<::str_t, re>::value,
        "error: expected 'str_t'"
    );
    const auto a_result
        = me::multibyte::convert_to<char>(str_w(L"12345"));
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(011)
{
    using re = decltype(me::multibyte::convert_to<char>(L"12345"));
    static_assert(
        ::std::is_same<str_t, re>::value,
        "error: expected 'str_t'"
    );

    const str_t a_result
        = me::multibyte::convert_to<char>(L"12345");
    ASSERT_TRUE(a_result == "12345");
}
TEST_COMPONENT(012)
{
    const wchar_t* ptr = L"12345";
    using re = decltype(me::multibyte::convert_to<char>(ptr));
    static_assert(
        ::std::is_same<str_t, re>::value,
        "error: expected 'str_t'"
    );

    const str_t a_result
        = me::multibyte::convert_to<char>(ptr);
    ASSERT_TRUE(a_result == "12345");
}

#ifdef INCLUDE_CONV_RUSSIAN
TEST_COMPONENT(013)
{
    str_w text = L"привет мир";
    const size_t len = text.length();
    ASSERT_TRUE(len == 10);

    using re = decltype(
	    me::multibyte::convert_to<char>(text.c_str())
    );
    static_assert(
        ::std::is_same<str_t, re>::value,
        "error: expected 'str_t'"
    );
    const str_t a_result
        = me::multibyte::convert_to<char>(text.c_str());

    const char* ptr = "привет мир";
    const bool equal = a_result == ptr;
    ASSERT_TRUE(equal);
}
#endif

// --- done
TEST_COMPONENT(014)
{
    ASSERT_TRUE(::setlocale(LC_ALL, g_locale_name.c_str()));
}

//==============================================================================
//==============================================================================
#endif // !dHAS_CPP11
#endif //!TEST_TOOLS_CONV



