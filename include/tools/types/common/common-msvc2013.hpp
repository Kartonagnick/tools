// [2021y-02-20d][18:40:18] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_COMMON_NEW_USED_ 
#define dTOOLS_COMMON_NEW_USED_ 100
// dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
// dHAS_USING_ALIAS
#include <type_traits>

//==============================================================================
//=== degradate ================================================================
#ifndef dTOOLS_DEGRADATE_USED_ 
#define dTOOLS_DEGRADATE_USED_ 100
namespace tools 
{
    template<class t> 
    using degradate = ::std::remove_cv_t<
        ::std::remove_reference_t<t> 
    >;

} // namespace tools 
#endif // !dTOOLS_DEGRADATE_USED_


//==============================================================================
//=== dfor_lvalue ==============================================================
#ifndef dTOOLS_FOR_LVALUE_USED_ 
#define dTOOLS_FOR_LVALUE_USED_ 100
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
#endif // !dTOOLS_COMMON_NEW_USED_
