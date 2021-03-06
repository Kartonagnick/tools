// [2019y-10m-24d][19:22:08] Idrisov Denis R.
//==============================================================================
//==============================================================================

#include <mygtest/modern.hpp>
//==============================================================================

#ifdef TEST_TOOLS_CONV

#define dTEST_COMPONENT tools, conv, multibyte
#define dTEST_METHOD convert
#define dTEST_TAG wchar_t

#include <tools/conv.hpp>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    typedef ::std::string  str_t;
    typedef ::std::wstring str_w;

    str_t g_locale_name;

#if 0
        writer = 0xCF; // П
      ++writer = 0xF0; // р
      ++writer = 0xE8; // и
      ++writer = 0xE2; // в
      ++writer = 0xE5; // е
      ++writer = 0xF2; // т
      ++writer = 0x2C; // ,
      ++writer = 0x20; //
      ++writer = 0xEC; // м
      ++writer = 0xE8; // и
      ++writer = 0xF0; // р
      ++writer = 0x21; // !
#endif

} // namespace

//==============================================================================
//==============================================================================

// --- prepare
TEST_COMPONENT(000)
{
    g_locale_name = std::locale().name();
    const char* p = ::setlocale(LC_ALL, "");
    ASSERT_TRUE(p);
}

// --- me::multibyte::convert(nullptr) assert/UB
TEST_COMPONENT(001)
{
    const wchar_t* null = 0;
    (void) null;
    ASSERT_DEATH_DEBUG(me::multibyte::convert(null));
}

// --- utf8::convert(from char*)        
TEST_COMPONENT(002)
{
    const str_t a_conv = me::multibyte::convert(L"12345", 5);
    const str_w w_conv = me::multibyte::convert(a_conv);
    ASSERT_TRUE(w_conv == L"12345");
}
TEST_COMPONENT(003)
{
    const str_t a_conv = me::multibyte::convert(L"привет мир");
    const str_w w_conv = me::multibyte::convert(a_conv);
    ASSERT_TRUE(w_conv == L"привет мир");
}

#ifdef dHAS_CPP11

// --- utf8::convert_to<wchar_t>(from wchar_t*)
TEST_COMPONENT(004)
{
    ::str_w w_conv = L"12345";
    using re = decltype(me::multibyte::convert_to<wchar_t>(w_conv));
    static_assert(
        ::std::is_same<::str_w&, re>::value,
        "error: expected 'str_w&'"
    );
    ::str_w& w_result
        = me::multibyte::convert_to<wchar_t>(w_conv);
    ASSERT_TRUE(w_result == w_conv);
}
TEST_COMPONENT(005)
{
    using re = decltype(me::multibyte::convert_to<wchar_t>(str_w(L"12345")));
    static_assert(
        ::std::is_same<::str_w, re>::value,
        "error: expected 'str_w'"
    );
    const auto w_result
        = me::multibyte::convert_to<wchar_t>(str_w(L"12345"));

    ASSERT_TRUE(w_result == L"12345");
}
TEST_COMPONENT(006)
{
    using re = decltype(me::multibyte::convert_to<wchar_t>(L"12345"));
    static_assert(
        ::std::is_same<const wchar_t(&)[6], re>::value,
        "error: expected 'const wchar_t(&)[6]'"
    );
    const auto& w_result
        = me::multibyte::convert_to<wchar_t>(L"12345");
    const ::str_w etalon = L"12345";
    ASSERT_TRUE(w_result == etalon);
}
TEST_COMPONENT(007)
{
    const wchar_t* ptr = L"12345";
    using re = decltype(me::multibyte::convert_to<wchar_t>(ptr));
    static_assert(
        ::std::is_same<const wchar_t*&, re>::value,
        "error: expected 'const wchar_t*&'"
    );
    const auto w_result
        = me::multibyte::convert_to<wchar_t>(ptr);
    const ::str_w etalon = L"12345";
    ASSERT_TRUE(w_result == etalon);
}
TEST_COMPONENT(008)
{
    const wchar_t* ptr = L"привет мир";
    using re = decltype(me::multibyte::convert_to<wchar_t>(ptr));

    static_assert(
        ::std::is_same<const wchar_t*&, re>::value,
        "error: expected 'const wchar_t*&'"
    );

    const auto w_result
        = me::multibyte::convert_to<wchar_t>(ptr);

    const ::str_w etalon = L"привет мир";
    ASSERT_TRUE(w_result == etalon);
}

// --- utf8::convert_to<wchar_t>(from char*)
TEST_COMPONENT(009)
{
    ::str_t a_conv = "12345";
    using re = decltype(me::multibyte::convert_to<wchar_t>(a_conv));

    static_assert(
        ::std::is_same<::str_w, re>::value,
        "error: expected 'str_t&'"
    );

    ::str_w w_result
        = me::multibyte::convert_to<wchar_t>(a_conv);
    ASSERT_TRUE(w_result == L"12345");
}
TEST_COMPONENT(010)
{
    using re = decltype(me::multibyte::convert_to<wchar_t>(str_t("12345")));
    static_assert(
        ::std::is_same<::str_w, re>::value,
        "error: expected 'str_w'"
    );
    const auto w_result
        = me::multibyte::convert_to<wchar_t>(str_t("12345"));
    ASSERT_TRUE(w_result == L"12345");
}
TEST_COMPONENT(011)
{
    using re = decltype(me::multibyte::convert_to<wchar_t>("12345"));
    static_assert(
        ::std::is_same<str_w, re>::value,
        "error: expected 'str_w'"
    );

    const str_w w_result
        = me::multibyte::convert_to<wchar_t>("12345");
    ASSERT_TRUE(w_result == L"12345");
}
TEST_COMPONENT(012)
{
    const char* ptr = "12345";
    using re = decltype(me::multibyte::convert_to<wchar_t>(ptr));
    static_assert(
        ::std::is_same<str_w, re>::value,
        "error: expected 'str_w'"
    );

    const str_w w_result
        = me::multibyte::convert_to<wchar_t>(ptr);
    ASSERT_TRUE(w_result == L"12345");
}
#ifdef INCLUDE_CONV_RUSSIAN
TEST_COMPONENT(013)
{
    using re = decltype(me::multibyte::convert_to<wchar_t>("привет мир"));
    static_assert(
        ::std::is_same<str_w, re>::value,
        "error: expected 'str_w'"
    );
    const str_w w_result
        = me::multibyte::convert_to<wchar_t>("привет мир");
    ASSERT_TRUE(w_result == L"привет мир");
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
#endif // !TEST_TOOLS_CONV



