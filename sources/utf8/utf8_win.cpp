// [2020y-12m-01d][14:06:17] Idrisov Denis R.
// [2021y-03m-05d][20:25:47] Idrisov Denis R.

#ifdef _WIN32

#include <string>
#include <tools/assert.hpp>
#include <tools/windows.hpp>

#ifndef NDEBUG
    #include <climits>
#endif

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
    // Convert a wide Unicode string to an UTF8 string  (wchar_t ---> char)
    namespace utf8
    {
        ::std::string convert(const wchar_t* text, const size_t len)
        {
            dASSERT(text);
            dASSERT(::detail::str_length(text) >= len);

            if (text[0] == 0)
                return ::std::string();

            dASSERT(len < INT_MAX);
            const int slen = static_cast<int>(len);

            const int size_needed = ::WideCharToMultiByte(
                CP_UTF8, 0, text, slen,
                NULL, 0, NULL, NULL
            );

            dASSERT(size_needed > 0);
            const size_t cnt 
                = static_cast<size_t>(size_needed);
            ::std::string strTo(cnt, 0);

            ::WideCharToMultiByte(
                CP_UTF8, 0, text, slen, &strTo[0], 
                size_needed, NULL, NULL
            );
            return strTo;
        }

        ::std::string convert(const wchar_t* text)
        {
            dASSERT(text);
            if (text[0] == 0)
                return ::std::string();
            const size_t len = ::detail::str_length(text);
            return ::tools::utf8::convert(text, len);
        }
        
        ::std::string convert(const ::std::wstring& text)
        {
            return ::tools::utf8::convert(
                text.c_str(),
                text.length()
            );
        }

    } // namespace utf8

    // Convert an UTF8 string to a wide Unicode String  (char ---> wchar_t)
    namespace utf8
    {
        ::std::wstring convert(const char* text, const size_t len)
        {
            dASSERT(text);
            dASSERT(::detail::str_length(text) >= len);

            if (text[0] == 0)
                return std::wstring();

            int size_needed = ::MultiByteToWideChar(
                CP_UTF8, 0, text,
                static_cast<int>(len),
                NULL, 0
            );

            dASSERT(size_needed > 0);
            const size_t cnt
                = static_cast<size_t>(size_needed);
            ::std::wstring wstrTo(cnt, 0);

            ::MultiByteToWideChar(
                CP_UTF8, 0, text,
                static_cast<int>(len),
                &wstrTo[0],
                size_needed
            );
            return wstrTo;
        }

        ::std::wstring convert(const char* text)
        {
            dASSERT(text);
            if (text[0] == 0)
                return ::std::wstring();
            const size_t len = ::detail::str_length(text);
            return ::tools::utf8::convert(text, len);
        }
        
        ::std::wstring convert(const ::std::string& text)
        {
            return ::tools::utf8::convert(
                text.c_str(),
                text.length()
            );
        }

    } // namespace utf8 

} // namespace tools

//==============================================================================
//==============================================================================

#endif // _WIN32

