// [2020y-12m-01d][14:06:17] Idrisov Denis R.
// [2021y-03m-05d][20:25:47] Idrisov Denis R.
//==============================================================================
//==============================================================================

#pragma once
#ifndef dTOOLS_UTF8_USED_ 
#define dTOOLS_UTF8_USED_ 100

#include <tools/features.hpp>
#include <string>

//==============================================================================
//==============================================================================
namespace tools
{
    namespace utf8 
    {
        // Convert a wide Unicode string to an UTF8 string
        ::std::string convert(const ::std::wstring& text);
        ::std::string convert(const wchar_t* text, const size_t len);
        ::std::string convert(const wchar_t* text);

        // Convert an UTF8 string to a wide Unicode String
        std::wstring convert(const ::std::string& text);
        std::wstring convert(const char* text, const size_t len);
        std::wstring convert(const char* text);

        #ifdef dHAS_CPP11
        // char ------------> std::string
        // wchar_t ---------> std::wstring
        template<class s> auto convert(const s& src);

        // return std::basic_string<ch>
        // if 'ch' == 's' -> return reference
        template<class ch, class s>
            decltype(auto) convert_to(s&& src);

        #endif // dHAS_CPP11

    } // namespace utf8 

} // namespace tools

//==============================================================================
//==============================================================================




//==============================================================================
//==============================================================================
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
    namespace utf8 
    {
        template<class s> auto convert(const s& src)
        {
            const auto* p = &src[0];
            return ::tools::utf8::convert(p);
        }

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
                    { return ::tools::utf8::convert(src); }
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
            using conv_t = ::tools::utf8::detail::converter<v>;
            return conv_t::convert(::std::forward<s>(src)); 
        } 

    } // namespace utf8 

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dHAS_CPP11
#endif // !dTOOLS_UTF8_USED_

