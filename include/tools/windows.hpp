// [2021y-02m-21d][20:30:33] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_WINDOWS_USED_ 
#define dTOOLS_WINDOWS_USED_ 100
//==============================================================================
//==============================================================================

#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0502
#endif

#ifdef _WIN32
    #define NOMINMAX 1
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h> 
#else
     #error: only windows supported
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_WINDOWS_USED_