// [2021y-02-20d][18:40:18] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_COMMON_USED_ 
#define dTOOLS_COMMON_USED_ 100

#include <tools/features.hpp>
#include <tools/pragma/pragma.hpp>

#ifdef dHAS_CPP11
    #include <tools/types/common/common-msvc2015.hpp>
#elif dHAS_USING_ALIAS
    #include <tools/types/common/common-msvc2013.hpp>
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_COMMON_USED_
