// [2021y-02m-05d][20:06:30] Idrisov Denis R.
// [2021y-03m-15d][23:28:19] Idrisov Denis R.
#pragma once
//==============================================================================
//==============================================================================

#include <tools/features.hpp>
#include <tools/assert.hpp>
#include <sstream>
#include <cstddef>
#include <string>

#ifdef dHAS_CPP11
    #define dCHECK_VALUE(...) \
        static_assert(__VA_ARGS__, "error");

    #define dCONSTANT constexpr
#else
    #define dCHECK_VALUE(...) \
        ASSERT_TRUE(__VA_ARGS__);

    #define dCONSTANT const
#endif

typedef ::std::stringstream sstrem_t;
typedef ::std::string  str_t;
typedef ::std::wstring str_w;
typedef ::std::basic_string<int> str_i;

//==============================================================================
//==============================================================================
