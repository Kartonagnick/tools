
#ifndef _WIN32

#include <tools/assert.hpp>
#include <codecvt>
#include <string>
//==============================================================================
//==============================================================================

namespace detail
{
    template<class ch>
    static dNODISCARD dCONSTEXPR_CPP14 
    size_t str_length(const ch* text) dNOEXCEPT
    {
        dASSERT(text);
        const ch* cur = text;
        while (*cur != 0)
            ++cur;
        return static_cast<size_t>(cur - text);
    }

} // namespace detail

//==============================================================================
//==============================================================================
namespace tools
{
    namespace utf8
    {
        ::std::string convert(const wchar_t* s, const size_t len)
        {
            dASSERT(s);
            dASSERT(::detail::str_length(s) >= len);

            using conv = ::std::codecvt_utf8<wchar_t>;
            ::std::wstring_convert<conv, wchar_t>
                converter;
            return converter.to_bytes(s, s + len);
        }

        ::std::string convert(const wchar_t* s)
        {
            dASSERT(s);
            using conv = ::std::codecvt_utf8<wchar_t>;
            ::std::wstring_convert<conv, wchar_t>
                converter;
            return converter.to_bytes(s);
        }

        ::std::string convert(const ::std::wstring& s)
        {
            using conv = ::std::codecvt_utf8<wchar_t>;
            ::std::wstring_convert<conv, wchar_t>
                converter;
            return converter.to_bytes(s);
        }

    } // namespace utf8 

//..............................................................................

    namespace utf8 
    {
        ::std::wstring convert(const char* s, const size_t len)
        {
            dASSERT(s);
            dASSERT(::detail::str_length(s) >= len);

            using conv = ::std::codecvt_utf8<wchar_t>;
            ::std::wstring_convert<conv, wchar_t>
                converter;
            return converter.from_bytes(s, s + len);
        }

        ::std::wstring convert(const char* s)
        {
            dASSERT(s);
            using conv = ::std::codecvt_utf8<wchar_t>;
            ::std::wstring_convert<conv, wchar_t>
                converter;
            return converter.from_bytes(s);
        }

        ::std::wstring convert(const ::std::string& s)
        {
            using conv = ::std::codecvt_utf8<wchar_t>;
            ::std::wstring_convert<conv, wchar_t>
                converter;
            return converter.from_bytes(s);
        }

    } // namespace utf8 

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !!_WIN32
