// [2019y-10m-24d][19:22:08] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_CONV_USED_
#define dTOOLS_CONV_USED_ 100

#include <tools/features.hpp>
#include <locale>
#include <string>

//==============================================================================
//==============================================================================

namespace tools 
{
    // work with global locale
    namespace multibyte 
    {
        ::std::string convert(const wchar_t* s, const size_t length);
        ::std::string convert(const wchar_t* s);
        ::std::string convert(const std::wstring& s);

        ::std::wstring convert(const char* s, const size_t length);
        ::std::wstring convert(const char* s);
        ::std::wstring convert(const std::string& s);

        // 'char' or 'wchar_t' only
        // char ------> std::wstring
        // wchar_t ---> std::string
        // template<class s> auto convert(const s& src);


        #ifdef dHAS_CPP11
        // 'char' or 'wchar_t' only
        // ch == deduce_symbol_t<s> ? 
        //     string& -----> string&      (from reference returned reference)
        //     string&& ----> string       (from rvalue returned by value)
        //     stringed ----> stringed&    (from stringed returned string by value)
        // else
        //     convert(src)
        template<class ch, class s> 
        decltype(auto) convert_to(s&& src);
        #endif

    } // namespace multibyte 

    // work with target locale
    namespace stdlocal 
    {
        ::std::string convert(const wchar_t* s, const size_t len, const ::std::locale& loc);
        ::std::string convert(const wchar_t* s, const ::std::locale& loc);

        ::std::string convert(const wchar_t* s, const size_t len);
        ::std::string convert(const wchar_t* s);

        ::std::string convert(const std::wstring& s, const ::std::locale& loc);
        ::std::string convert(const std::wstring& s);

        //----------------

        ::std::wstring convert(const char* s, const size_t len, const ::std::locale& loc);
        ::std::wstring convert(const char* s, const ::std::locale& loc);

        ::std::wstring convert(const char* s, const size_t len);
        ::std::wstring convert(const char* s);

        ::std::wstring convert(const std::string& s, const ::std::locale& loc);
        ::std::wstring convert(const std::string& s);

        //----------------
        #if 0
        // char ------> std::wstring
        // wchar_t ---> std::string
        template<class s> auto convert(const s& src);

        template<class str> auto convert(
            const str& s, 
            const ::std::locale& loc
        );
        #endif

        #ifdef dHAS_CPP11
        // 'char' or 'wchar_t' only
        // ch == deduce_symbol_t<s> ? 
        //     string& -----> string&               (from reference returned reference)
        //     string&& ----> string                (from rvalue returned by value)
        //     stringed ----> basic_string<char>    (from stringed returned string by value)
        // else
        //     convert(src)
        template<class ch, class s> 
        decltype(auto) convert_to(s&& src);

        template<class ch, class s> 
        decltype(auto) convert_to(
            s&& src, 
            const ::std::locale& loc
        );
        #endif

    } // namespace stdlocal 

} // namespace tools

//==============================================================================
//=== implementations ==========================================================

#ifdef dHAS_CPP11

#include <tools/assert.hpp>
#include <type_traits>

//==============================================================================
//=== dfor_lvalue ==============================================================
#ifndef dTOOLS_FOR_LVALUE_USED_ 
#define dTOOLS_FOR_LVALUE_USED_
namespace tools
{
    #define dfor_lvalue(t) ::tools::for_lvalue<t>* = nullptr
    template<class t, class ret = void>
        using for_lvalue
            = ::std::enable_if_t<
                ::std::is_lvalue_reference<t>::value,
                ret
            >;

    #define dfor_not_lvalue(t) ::tools::for_not_lvalue<t>* = nullptr
    template<class t, class ret = void>
        using for_not_lvalue
            = ::std::enable_if_t<
                ! ::std::is_lvalue_reference<t>::value,
                ret
            >;

} // namespace tools
#endif // !dTOOLS_FOR_LVALUE_USED_

//==============================================================================
//==============================================================================
namespace tools
{
    namespace multibyte
    {
        #if 0
        template<class s> auto convert(const s& src)
        {
            const auto* p = &src[0];
            return ::tools::multibyte::convert(p);
        }
        #endif

        namespace detail
        {
            template<bool> struct converter
            {
                template<class s, dfor_lvalue(s&&) > 
                static decltype(auto) convert(s&& src) noexcept
                    { return ::std::forward<s>(src); }

                template<class s,  dfor_not_lvalue(s&&)> 
                static auto convert(s&& src) noexcept
                    { return src; }
            };

            template<> struct converter<false>
            {
                template<class s>
                static auto convert(const s& src)
                    { return ::tools::multibyte::convert(src); }
            };

        } // namespace detail

        template<class ch, class s> 
        decltype(auto) convert_to(s&& src)
        {
            const auto* p = &src[0];
            dASSERT(p);
            (void) p;

            using x = ::std::remove_pointer_t<decltype(p)>;
            using z = ::std::remove_cv_t<x>;
            enum { v = ::std::is_same<z, ch>::value };
            using conv_t = ::tools::multibyte::detail::converter<v>;
            return conv_t::convert(::std::forward<s>(src)); 
        }

    } // namespace multibyte

    namespace stdlocal
    {
        #if 0
        template<class s> auto convert(const s& src)
        {
            const auto* p = &src[0];
            return ::tools::stdlocal::convert(p);
        }
        #endif

        namespace detail
        {
            template<bool> struct converter
            {
                template<class s, dfor_lvalue(s&&) > 
                static decltype(auto) convert(s&& src) noexcept
                    { return ::std::forward<s>(src); }

                template<class s,  dfor_not_lvalue(s&&)> 
                static auto convert(s&& src) noexcept
                    { return src; }
            };

            template<> struct converter<false>
            {
                template<class s>
                static auto convert(const s& src)
                    { return ::tools::stdlocal::convert(src); }
            };

        } // namespace detail

        template<class ch, class s> 
        decltype(auto) convert_to(s&& src)
        {
            const auto* p = &src[0];
            dASSERT(p);
            (void) p;

            using x = ::std::remove_pointer_t<decltype(p)>;
            using z = ::std::remove_cv_t<x>;
            enum { v = ::std::is_same<z, ch>::value };
            using conv_t = ::tools::stdlocal::detail::converter<v>;
            return conv_t::convert(::std::forward<s>(src)); 
        }

    } // namespace stdlocal

} // namespace tools 

#endif // !dHAS_CPP11
//==============================================================================
//==============================================================================

#endif // !dTOOLS_CONV_USED_
