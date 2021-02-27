
// [2021y-02m-20d][18:41:19] Idrisov Denis R.
// [2021y-02m-20d][18:41:19] birthday of the project
// [2021y-02m-25d][04:10:xx] Idrisov Denis R.
// [2021y-02m-26d][06:30:xx] Idrisov Denis R.
// [2021y-02m-27d][21:58:36] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_CONFBUILD_USED_
#define dTOOLS_CONFBUILD_USED_ 008
//==============================================================================
//==============================================================================

#if !defined(dX64) && !defined(dX32)
    #ifdef _WIN32
        #ifdef _WIN64
            #define dX64 1
        #else
            #define dX32 1
        #endif
    #else
        #if defined(__LP64__) || defined(_M_IA64)
            #define dX64 1
        #else
            #define dX32 1
        #endif
    #endif
#endif

#if defined(dX64)
    #define dTXT_ADDRESS_MODEL "64-bit"
#elif defined(dX32)
    #define dTXT_ADDRESS_MODEL "32-bit"
#endif

#ifdef NDEBUG
    #define dTXT_CONFIGURATION "release"
#else
    #define dTXT_CONFIGURATION "debug"
#endif

#ifdef STABLE_RELEASE
    #define dTXT_RELEASE_STABLE "stable"
#else
    #define dTXT_RELEASE_STABLE "unstable"
#endif

#define dVERSION_MAJOR      0
#define dVERSION_MINOR      0
#define dVERSION_PATCH      8 

#define dSTRINGIZE(...) #__VA_ARGS__
#define dSSTRINGIZE(x) dSTRINGIZE(x)

#define dFILE_VERSION       dVERSION_MAJOR, dVERSION_MINOR, dVERSION_PATCH
#define dFILE_VERSION_NUM   dVERSION_MAJOR * 100 + dVERSION_MINOR * 10 + dVERSION_PATCH
#define dFILE_VERSION_STR   dSSTRINGIZE(dVERSION_MAJOR.dVERSION_MINOR.dVERSION_PATCH)

#define dABOUT_ME \
    dTXT_CONFIGURATION "-" dTXT_ADDRESS_MODEL ", " dTXT_RELEASE_STABLE 

#define dFULL_VERSION dFILE_VERSION_STR ", " dABOUT_ME

//==============================================================================
//==============================================================================
#endif // !dTOOLS_CONFBUILD_USED_
