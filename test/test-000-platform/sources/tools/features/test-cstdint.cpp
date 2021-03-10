// [2021y-03m-10d][13:28:40] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_CSTDINT

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_CSTDINT
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifdef dHAS_CSTDINT
    dMESSAGE("[test] tools: enabled -> dHAS_CSTDINT")
    #include <cstdint>
#else
    dMESSAGE("[test] tools: disabled -> dHAS_CSTDINT")
#endif

//==============================================================================
//==============================================================================
namespace
{
    #ifdef dHAS_CSTDINT
        static_assert(
            sizeof(::std::uint8_t) == 1,
            "ERROR_INVALID_SIZE_MUST_BE_8BIT"
        );
        static_assert(
            sizeof(::std::uint16_t) == 2,
            "ERROR_INVALID_SIZE_MUST_BE_16BIT"
        );
        static_assert(
            sizeof(::std::uint32_t) == 4,
            "ERROR_INVALID_SIZE_MUST_BE_32BIT"
        );
        static_assert(
            sizeof(::std::int64_t) == 8,
            "ERROR_INVALID_SIZE_MUST_BE_64BIT"
        );
    #endif

}//namespace

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_CSTDINT



