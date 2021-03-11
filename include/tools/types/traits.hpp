// [2021y-03-11d][01:46:56] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_TRAITS_USED_ 
#define dTOOLS_TRAITS_USED_ 1

//==============================================================================
//=== is_same ==================================================================
#ifndef dTOOLS_IS_SAME_USED_ 
#define dTOOLS_IS_SAME_USED_ 1
namespace tools
{
    template<class a, class b> struct is_same
        { enum { value = 0 }; };

    template<class t> struct is_same<t, t>
        { enum { value = 1 }; };

} // namespace tools 
#endif // !dTOOLS_IS_SAME_USED_

//==============================================================================
//=== remove_cv ================================================================
#ifndef dTOOLS_REMOVE_CV_USED_ 
#define dTOOLS_REMOVE_CV_USED_ 1
namespace tools
{
    template<class t> struct remove_cv                     
        { typedef t type; };

    template<class t> struct remove_cv <const t>           
        { typedef t type; };

    template<class t> struct remove_cv <volatile t>        
        { typedef t type; };

    template<class t> struct remove_cv <volatile  const t> 
        { typedef t type; };

} // namespace tools 
#endif // !dTOOLS_REMOVE_CV_USED_

//==============================================================================
//=== is_signed ================================================================
#ifndef dTOOLS_IS_SIGNED_USED_ 
#define dTOOLS_IS_SIGNED_USED_ 1
namespace tools
{
    template <class t> struct is_signed
    {
        typedef typename remove_cv<t>::type x;
        enum { value = static_cast<x>(-1) < static_cast<x>(0) };
    };

    template <class t> struct is_unsigned
    {
        enum { value = !is_signed<t>::value };
    };

} // namespace tools 
#endif // !dTOOLS_IS_SIGNED_USED_

//==============================================================================
//=== is_floating ==============================================================
#ifndef dTOOLS_IS_FLOATING_USED_ 
#define dTOOLS_IS_FLOATING_USED_ 1
namespace tools
{
    template <class t> struct is_floating_
        { enum { value = 0 }; };

    template <> struct is_floating_<float>
        { enum { value = 1 }; };

    template <> struct is_floating_<double>
        { enum { value = 1 }; };

    template <> struct is_floating_<long double>
        { enum { value = 1 }; };

    template <class t> struct is_floating_point
        : is_floating_<typename remove_cv<t>::type>
    {};

} // namespace tools 
#endif // !dTOOLS_IS_FLOATING_USED_

//==============================================================================
//=== is_integral ==============================================================
#ifndef dTOOLS_IS_INTEGRAL_USED_ 
#define dTOOLS_IS_INTEGRAL_USED_ 1
namespace tools
{
    template <class t> struct is_integral_
        { enum { value = 0 }; };

#if !defined(_MSC_VER) || _MSC_VER >= 1900
    template <> struct is_integral_<char16_t>
        { enum { value = 1 }; };

    template <> struct is_integral_<char32_t>
        { enum { value = 1 }; };
#endif

    template <> struct is_integral_<short>
        { enum { value = 1 }; };

    template <> struct is_integral_<unsigned short>
        { enum { value = 1 }; };

    template <> struct is_integral_<int>
        { enum { value = 1 }; };

    template <> struct is_integral_<unsigned int>
        { enum { value = 1 }; };

    template <> struct is_integral_<long>
        { enum { value = 1 }; };

    template <> struct is_integral_<unsigned long>
        { enum { value = 1 }; };

    template <> struct is_integral_<long long>
        { enum { value = 1 }; };

    template <> struct is_integral_<unsigned long long>
        { enum { value = 1 }; };

    template <class t> struct is_integral
        : is_integral_<typename remove_cv<t>::type>
    {};

} // namespace tools 
#endif // !dTOOLS_IS_INTEGRAL_USED_

//==============================================================================
//=== conditional ==============================================================
#ifndef dTOOLS_CONDITIONAL_USED_ 
#define dTOOLS_CONDITIONAL_USED_ 1
namespace tools
{
    template <bool, class a, class b>
    struct conditional
        { typedef a type; };

    template <class a, class b> 
    struct conditional<false, a, b>
        { typedef b type; };

} // namespace tools 
#endif // !dTOOLS_SELECT_USED_

//==============================================================================
//=== enable_if ================================================================
#ifndef dTOOLS_ENABLE_IF_USED_ 
#define dTOOLS_ENABLE_IF_USED_ 1
namespace tools
{
    template <bool, class t = void> 
        struct enable_if;

    template <class t> struct enable_if<true, t>
        { typedef t type; };

} // namespace tools 
#endif // !dTOOLS_SELECT_USED_

//================================================================================
//================================================================================
#ifndef dTOOLS_ENUM_TYPE_USED_ 
#define dTOOLS_ENUM_TYPE_USED_ 1
namespace tools
{
    namespace detail
    {
        template<class t, bool = ::std::is_enum<t>::value >
        struct type_of_enum
            { using type = ::std::underlying_type_t<t>; };

        template<class t>
        struct type_of_enum<t, false>
            { using type = t; };

    } // namespace detail

    template<class t> 
    using type_of_enum_t
        = typename ::tools::detail::type_of_enum<t>::type;

} // tools
#endif // !dTOOLS_ENUM_TYPE_USED_

//==============================================================================
//==============================================================================
#endif // !dTOOLS_TRAITS_USED_
