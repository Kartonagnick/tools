// [2021y-03m-10d][12:44:35] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_FIXED_USED_
#define dTOOLS_FIXED_USED_ 100
//==============================================================================
//==============================================================================

#include <tools/features.hpp>

#ifdef dHAS_CSTDINT
    #include <cstdint>
#endif

namespace tools
{
    #ifdef dHAS_CSTDINT
        // #pragma message("build for msvc2010 or newer)")
        using ::std::uint8_t ;
        using ::std::uint16_t;
        using ::std::uint32_t;
        using ::std::uint64_t;
        
        using ::std::int8_t  ; 
        using ::std::int16_t ; 
        using ::std::int32_t ; 
        using ::std::int64_t ; 
    #else
        // #pragma message("build for msvc2008 or older)")
        typedef unsigned char    uint8_t ;
        typedef unsigned __int16 uint16_t;
        typedef unsigned __int32 uint32_t;
        typedef unsigned __int64 uint64_t;

        typedef signed char      int8_t  ;
        typedef __int16          int16_t ;
        typedef __int32          int32_t ;
        typedef __int64          int64_t ;

        static inline void static_assert_check_signed_fixed_()
        {
            dSTATIC_ASSERT(
                sizeof(::tools::int8_t) == 1,
                ERROR_INVALID_SIZE_MUST_BE_8BIT
            );
            dSTATIC_ASSERT(
                sizeof(::tools::int16_t) == 2,
                ERROR_INVALID_SIZE_MUST_BE_16BIT
            );
            dSTATIC_ASSERT(
                sizeof(::tools::int32_t) == 4,
                ERROR_INVALID_SIZE_MUST_BE_32BIT
            );
            dSTATIC_ASSERT(
                sizeof(::tools::int64_t) == 8,
                ERROR_INVALID_SIZE_MUST_BE_64BIT
            );
        }

        static inline void static_assert_check_unsigned_fixed_()
        {
            dSTATIC_ASSERT(
                sizeof(::tools::uint8_t) == 1,
                ERROR_INVALID_SIZE_MUST_BE_8BIT
            );
            dSTATIC_ASSERT(
                sizeof(::tools::uint16_t) == 2,
                ERROR_INVALID_SIZE_MUST_BE_16BIT
            );
            dSTATIC_ASSERT(
                sizeof(::tools::uint32_t) == 4,
                ERROR_INVALID_SIZE_MUST_BE_32BIT
            );
            dSTATIC_ASSERT(
                sizeof(::tools::uint64_t) == 8,
                ERROR_INVALID_SIZE_MUST_BE_64BIT
            );
        }

        #define INT8_MIN         (-127 - 1)
        #define INT16_MIN        (-32767 - 1)
        #define INT32_MIN        (-2147483647 - 1)
        #define INT64_MIN        (-9223372036854775807 - 1)

        #define INT8_MAX         127
        #define INT16_MAX        32767
        #define INT32_MAX        2147483647
        #define INT64_MAX        9223372036854775807

        #define UINT8_MAX        0xffu
        #define UINT16_MAX       0xffff
        #define UINT32_MAX       0xffffffff
        #define UINT64_MAX       0xffffffffffffffff

    #endif // !dHAS_CSTDINT

    template<size_t Size> struct map_signed;
    
    template<> struct map_signed<1>
    {
        typedef ::tools::int8_t type; 
        enum { min_value = INT8_MIN };
        enum { max_value = INT8_MAX };
    };

    template<> struct map_signed<2>
    {
        typedef ::tools::int16_t type; 
        enum { min_value = INT16_MIN };
        enum { max_value = INT16_MAX };
    };

    template<> struct map_signed<4>
    {
        typedef ::tools::int32_t type;
        enum { min_value = INT32_MIN };
        enum { max_value = INT32_MAX };
    };

    #ifdef _MSC_VER
        #pragma warning( push )
        // warning C4480: nonstandard extension used: specifying underlying type for enum ''
        #pragma warning(disable : 4480)
    #endif

    template<> struct map_signed<8>
    {
        typedef ::tools::int64_t type; 
        enum:__int64 { min_value = INT64_MIN };
        enum:__int64 { max_value = INT64_MAX };
    };

    template<size_t Size> struct map_unsigned;
    
    template<> struct map_unsigned<1>
    {
        typedef ::tools::uint8_t type; 
        enum { min_value = 0   };
        enum { max_value = UINT8_MAX };
    };

    template<> struct map_unsigned<2>
    {
        typedef ::tools::uint16_t type;
        enum { min_value = 0   };
        enum { max_value = UINT16_MAX };
    };

    template<> struct map_unsigned<4>
    {
        typedef ::tools::uint32_t type; 
        enum { min_value = 0   };
        enum { max_value = UINT32_MAX };
    };

    template<> struct map_unsigned<8>
    {
        typedef ::tools::uint64_t type; 
        enum: unsigned  { min_value = 0 };
        enum: unsigned __int64 { max_value = UINT64_MAX };
    };

    #ifdef _MSC_VER
        #pragma warning(pop)
    #endif


} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_FIXED_USED_
