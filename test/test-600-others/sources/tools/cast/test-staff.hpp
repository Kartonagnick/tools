
// [2021y-03m-10d][15:20:55] Idrisov Denis R.
#pragma once
#include <tools/assert.hpp>
#include <tools/types/fixed.hpp>
//=================================================================================
//=================================================================================
namespace test_can_numeric_cast
{
    using ::tools::int8_t;
    using ::tools::int16_t;
    using ::tools::int32_t;
    using ::tools::int64_t;

    using ::tools::uint8_t;
    using ::tools::uint16_t;
    using ::tools::uint32_t;
    using ::tools::uint64_t;

    dCONSTANT bool may_be 
        = sizeof(13.13l) == sizeof(13.13);

    dCONSTANT long double long_double = 13.13l;

//---------------------------------------------------------------------------------
    dCONSTANT int8_t  int8max  = INT8_MAX ;
    dCONSTANT int16_t int16max = INT16_MAX;
    dCONSTANT int32_t int32max = INT32_MAX;
    dCONSTANT int64_t int64max = INT64_MAX;
//---------------------------------------------------------------------------------
    dCONSTANT uint8_t  uint8max  = UINT8_MAX ;
    dCONSTANT uint16_t uint16max = UINT16_MAX;
    dCONSTANT uint32_t uint32max = UINT32_MAX;
    dCONSTANT uint64_t uint64max = UINT64_MAX;
//---------------------------------------------------------------------------------
    dCONSTANT int16_t int8maxPlus  = int16_t(int8max ) + 1;
    dCONSTANT int32_t int16maxPlus = int32_t(int16max) + 1;
    dCONSTANT int64_t int32maxPlus = int64_t(int32max) + 1;
//---------------------------------------------------------------------------------
    dCONSTANT uint16_t uint8maxPlus  = uint16_t(uint8max ) + 1;
    dCONSTANT uint32_t uint16maxPlus = uint32_t(uint16max) + 1;
    dCONSTANT uint64_t uint32maxPlus = uint64_t(uint32max) + 1;
//---------------------------------------------------------------------------------
    dCONSTANT int8_t  int8min  = INT8_MIN ;
    dCONSTANT int16_t int16min = INT16_MIN;
    dCONSTANT int32_t int32min = INT32_MIN;
    dCONSTANT int64_t int64min = INT64_MIN;
//---------------------------------------------------------------------------------
    dCONSTANT int16_t int8minMinus  = int16_t(int8min ) - 1;
    dCONSTANT int32_t int16minMinus = int32_t(int16min) - 1;
    dCONSTANT int64_t int32minMinus = int64_t(int32min) - 1;
//---------------------------------------------------------------------------------

} // namespace test_can_numeric_cast

//=================================================================================
//=================================================================================

