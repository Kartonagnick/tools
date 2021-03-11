// [2021y-03m-11d][10:15:28] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_FIXED_CPP11_USED_
#define dTOOLS_FIXED_CPP11_USED_ 100
//==============================================================================
//==============================================================================

#include <tools/features.hpp>
#include <cstdint>

namespace tools
{
    using ::std::uint8_t ;
    using ::std::uint16_t;
    using ::std::uint32_t;
    using ::std::uint64_t;
        
    using ::std::int8_t  ; 
    using ::std::int16_t ; 
    using ::std::int32_t ; 
    using ::std::int64_t ; 

    template<size_t Size> struct map_signed;
    
    template<> struct map_signed<1>
    {
        typedef ::tools::int8_t type; 
        static constexpr type min_value = INT8_MIN;
        static constexpr type max_value = INT8_MAX;
    };

    template<> struct map_signed<2>
    {
        typedef ::tools::int16_t type; 
        static constexpr type min_value = INT16_MIN;
        static constexpr type max_value = INT16_MAX;
    };

    template<> struct map_signed<4>
    {
        typedef ::tools::int32_t type;
        static constexpr type min_value = INT32_MIN;
        static constexpr type max_value = INT32_MAX;
    };

    template<> struct map_signed<8>
    {
        typedef ::tools::int64_t type; 
        static constexpr type min_value = INT64_MIN;
        static constexpr type max_value = INT64_MAX;
    };

    template<size_t Size> struct map_unsigned;
    
    template<> struct map_unsigned<1>
    {
        typedef ::tools::uint8_t type; 
        static constexpr type min_value = 0;
        static constexpr type max_value = UINT8_MAX;
    };

    template<> struct map_unsigned<2>
    {
        typedef ::tools::uint16_t type;
        static constexpr type min_value = 0;
        static constexpr type max_value = UINT16_MAX;
    };

    template<> struct map_unsigned<4>
    {
        typedef ::tools::uint32_t type; 
        static constexpr type min_value = 0;
        static constexpr type max_value = UINT32_MAX;
    };

    template<> struct map_unsigned<8>
    {
        typedef ::tools::uint64_t type; 
        static constexpr type min_value = 0;
        static constexpr type max_value = UINT64_MAX;
    };

    template<class t> struct limit_unsigned
        : map_unsigned<sizeof(t)>
    {};

    template<class t> struct limit_signed
        : map_signed<sizeof(t)>
    {};

} // namespace tools

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
//=== limit ====================================================================
#ifndef dTOOLS_LIMIT_USED_ 
#define dTOOLS_LIMIT_USED_ 1
namespace tools
{
    template <class t, bool> struct limit_
        : limit_signed<t>
    {};

    template <class t> struct limit_<t, false>
        : limit_unsigned<t>
    {};

    template <class t> struct limit
        : limit_<t, is_signed<t>::value>
    {};

} // namespace tools 
#endif // !dTOOLS_LIMIT_USED_

//==============================================================================
//==============================================================================
#endif // !dTOOLS_FIXED_CPP11_USED_
