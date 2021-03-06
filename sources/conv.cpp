// [2019y-10m-24d][19:22:08] Idrisov Denis R.
//==============================================================================
//==============================================================================

#include <tools/assert.hpp>
#include <cstdlib>
#include <cstring>
#include <locale>

#ifdef _MSC_VER
    #pragma warning(disable: 4996)
#endif

//==============================================================================
//=== [multibyte] ==============================================================
namespace tools
{
    namespace multibyte
    {
        ::std::string convert(const wchar_t* s, const size_t length)
        {
            dASSERT(s);
            dASSERT(length <= ::wcslen(s));
            const size_t len = length + 1;

            ::std::string result(256, '\0');

            #if 0
            //TODO: check posix version
            ::std::mbstate_t state = ::std::mbstate_t();
            ::std::wcsrtombs(&result[0], &s, result.size(), &state);
            #endif

            size_t count = 0;
            const ::errno_t err
                = ::wcstombs_s(&count, &result[0], 256, s, len * sizeof(wchar_t));
            dASSERT(err == 0);
            (void) err;

            result.resize(count);
            if (!result.empty())
                result.erase(result.length() - 1);
            return result;
        }

        ::std::string convert(const wchar_t* s)
        {
            dASSERT(s);
            const size_t len = ::wcslen(s);
            return ::tools::multibyte::convert(s, len);
        }

        ::std::string convert(const std::wstring& s)
        {
            return ::tools::multibyte::convert(
                s.c_str(), s.length()
            );
        }

//..............................................................................

        ::std::wstring convert(const char* s, const size_t length)
        {
            dASSERT(s);
            dASSERT(length <= ::std::strlen(s));
            ::std::mbstate_t state = ::std::mbstate_t();

            wchar_t wc[4] = {};
            ::std::wstring result;
            const char* end = s + length;

            for(;;)
            {
                const size_t cnt = static_cast<size_t>(end - s);
                if(cnt == 0)
                    return result;

                const size_t len = ::std::mbrtowc(wc, s, cnt, &state);
                if(len == 0)
                    return result;

                result += wc;
                s += len;

                for (size_t i = 0; i != 4;++i)
                    wc[i] = L'\0';
            }
        }

        ::std::wstring convert(const char* s)
        {
            dASSERT(s);
            const size_t len = ::strlen(s);
            return ::tools::multibyte::convert(s, len);
        }

        ::std::wstring convert(const std::string& s)
        {
            return ::tools::multibyte::convert(
                s.c_str(), s.length()
            );
        }

    } // namespace multibyte 

}  // namespace tools

//==============================================================================
//=== [stdlocal] ===============================================================

namespace tools
{
    namespace stdlocal
    {
        ::std::string convert(const wchar_t* s, const size_t len, const ::std::locale& loc)
        {
            dASSERT(s);
            dASSERT(len <= ::wcslen(s));

            if (len == 0)
                return "";

            typedef ::std::ctype<wchar_t> 
                ty;

            const ty& facet = ::std::use_facet<ty>(loc);

            const wchar_t* last = s + len;
            ::std::string result(len, '?');

            const wchar_t* re 
                = facet.narrow(s, last, L'?', &result[0]);
            (void)re;
            return result;
        }

        ::std::string convert(const wchar_t* s, const size_t len)
        {
            dASSERT(s);
            dASSERT(len <= ::wcslen(s));
            const ::std::locale loc("");
            return ::tools::stdlocal::convert(s, len, loc);
        }

        ::std::string convert(const wchar_t* s, const ::std::locale& loc)
        {
            dASSERT(s);
            const size_t len = ::wcslen(s);
            return ::tools::stdlocal::convert(s, len, loc);
        }

        ::std::string convert(const wchar_t* s)
        {
            dASSERT(s);
            const ::std::locale loc("");
            return ::tools::stdlocal::convert(s, loc);
        }

        ::std::string convert(const std::wstring& s, const ::std::locale& loc)
        {
            return ::tools::stdlocal::convert(s.c_str(), s.length(), loc);
        }

        ::std::string convert(const std::wstring& s)
        {
            const ::std::locale loc("");
            return ::tools::stdlocal::convert(s, loc);
        }

    } // namespace stdlocal

//..............................................................................

    namespace stdlocal 
    {
        ::std::wstring convert(const char* s, const size_t len, const ::std::locale& loc)
        {
            dASSERT(s);
            dASSERT(len <= ::strlen(s));
            if(len == 0) 
                return L"";

            typedef ::std::ctype<wchar_t> 
                ty;

            const ty& facet = ::std::use_facet<ty>(loc);

            const char* last = s + len;
            ::std::wstring result(len, L'\0');
            facet.widen(s, last, &result[0]);
            return result;
        }

        ::std::wstring convert(const char* s, const size_t len)
        {
            dASSERT(s);
            dASSERT(len <= ::strlen(s));
            const ::std::locale loc("");
            return ::tools::stdlocal::convert(s, len, loc);
        }

        ::std::wstring convert(const char* s, const ::std::locale& loc)
        {
            dASSERT(s);
            const size_t len = ::strlen(s);
            return ::tools::stdlocal::convert(s, len, loc);
        }

        ::std::wstring convert(const char* s)
        {
            dASSERT(s);
            const ::std::locale loc("");
            return ::tools::stdlocal::convert(s, loc);
        }

        ::std::wstring convert(const std::string& s, const ::std::locale& loc)
        {
            return ::tools::stdlocal::convert(s.c_str(), s.length(), loc);
        }

        ::std::wstring convert(const std::string& s)
        {
            const ::std::locale loc("");
            return ::tools::stdlocal::convert(s, loc);
        }

    } // namespace stdlocal

} // namespace tools 

//==============================================================================
//==============================================================================
