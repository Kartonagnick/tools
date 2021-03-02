// [2021y-02m-20d][18:40:18] Idrisov Denis R.
#include <stdexcept>
#include <cstring>
#include <string>

#ifdef _WIN32
    #include <tools/windows.hpp>
#endif

#include <tools/features.hpp>
#include <tools/assert.hpp>

#if defined(__MINGW__) || defined(__MINGW32__) || defined(__GNUC__)
    #ifndef _ERRCODE_DEFINED
    #define _ERRCODE_DEFINED
        typedef int errno_t;
    #endif
#endif

typedef ::std::string 
    str_t;

namespace
{
    #if defined(_MSC_VER) && _MSC_VER <= 1600

    template<bool> 
    unsigned long adopt_(char*& next, const unsigned uval) dNOEXCEPT;

    template<> 
    unsigned long adopt_<true>(char*& next, unsigned uval) dNOEXCEPT
    {
        // For 64-bit numbers, 
        // work in chunks to avoid 64-bit divisions.
        while (uval > 0xFFFFFFFFU)
        {
            unsigned long uval_chunk
                = static_cast<unsigned long>(uval % 1000000000);

            uval /= 1000000000;

            for (unsigned i = 0; i != 9; ++i)
            {
                *--next = static_cast<char>('0' + uval_chunk % 10);
                uval_chunk /= 10;
            }
        }
        return static_cast<unsigned long>(uval);
    }

    template<> 
    unsigned long adopt_<false>(char*& next, const unsigned uval) dNOEXCEPT
    {
        (void)next;
        return static_cast<unsigned long>(uval);
    }

    char* uint_to_buff_(char* next, unsigned uval) dNOEXCEPT
    {
        unsigned long uval_trunc 
            = adopt_< (sizeof(unsigned) > 4) >(next, uval);
        do
        {
            const unsigned ch = '0' + uval_trunc % 10;
            *--next = static_cast<char>(ch);
            uval_trunc /= 10;

        } while (uval_trunc != 0);

        return next;
    }

    str_t int_string_(const int val)
    {
        // can hold -2^63 and 2^64 - 1, plus NUL

        const unsigned uval 
            = static_cast<unsigned>(val);

        char buff[21]; 
        char* const end_ = buff + 21;
        char* next       = end_;

        if (val < 0)
        {
            next = uint_to_buff_(next, 0 - uval);
            *--next = '-';
        }
        else
            next = uint_to_buff_(next, uval);

        return str_t(next, end_);
    }
    #endif // defined(_MSC_VER) && _MSC_VER <= 1600

    template<class t>
    str_t int_to_string_(const t value) 
    {
        #if defined(_MSC_VER) && _MSC_VER <= 1600
            // #pragma message("build for msvc2010 (or older)")
            return int_string_(value);
        #else
            return ::std::to_string(value);
        #endif
    }

} // namespace

namespace tools
{
    str_t get_errno(const int error_id)
    {
        #ifdef __GNUC__
            char* p = ::strerror(error_id);
            dASSERT(p);
            return p;
        #else
            char buf[100];
            enum { len = sizeof(buf)/sizeof(buf[0]) };
            const ::errno_t re = ::strerror_s(buf, len, error_id);
            dASSERT(re == 0);
            if (re == 0)
                return buf;

            const str_t sid = int_to_string_(error_id);
            throw ::std::runtime_error(
                "get_errno(" + sid + "): failed"
            );
        #endif
    }

    #ifdef _WIN32
        str_t get_last_error(const ::DWORD error_id)
        {
            if (error_id == 0) 
                return ""; 

            dSTATIC_ASSERT(
                sizeof(int) == sizeof(::DWORD),
                DATA_CORRUPTION_POSSIBLE
            );

            #define dNULL_PTR 0
            char* buf = dNULL_PTR;
            const unsigned size = ::FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                dNULL_PTR,
                error_id,
                MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
                reinterpret_cast<char*>(&buf),
                0,
                dNULL_PTR
            );

            const str_t message(buf, size);
            ::LocalFree(buf);

            const str_t sid = int_to_string_(error_id);
            return  "(" + sid + "): " + message;
        }

        str_t get_last_error(const int errorId)
        {
            if (errorId == 0) 
                return ""; 

            dSTATIC_ASSERT(
                sizeof(int) == sizeof(::DWORD),
                DATA_CORRUPTION_POSSIBLE
            );

            dASSERT(errorId > 0);

            const ::DWORD err_code 
                = static_cast<::DWORD>(errorId);

            return ::tools::get_last_error(err_code);
        }

        str_t get_last_error()
        {
            const ::DWORD code = ::GetLastError();
            return ::tools::get_last_error(code);
        }

    #else
        str_t get_last_error()
            { return "OS 'Windows' not found"; }

        str_t get_last_error(const int)
            { return "OS 'Windows' not found"; }

    #endif
}

//==============================================================================
//==============================================================================

namespace tools
{
    str_t get_last_error(const char* from)
    {
        dASSERT(from);
        return from + ::tools::get_last_error();
    }

    str_t get_last_error(const str_t& from)
    {
        return from + ::tools::get_last_error();
    }

    void throw_error(const char* from)
    {
        dASSERT(from);
        throw ::std::runtime_error(
            ::tools::get_last_error(from)
        );
    }

    void throw_error(const str_t& from)
    {
        throw ::std::runtime_error(
            ::tools::get_last_error(from)
        );
    }

} // namespace tools

//==============================================================================
//==============================================================================
