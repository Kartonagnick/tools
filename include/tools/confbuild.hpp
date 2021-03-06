// [2021y-02m-20d][18:41:19] Idrisov Denis R.
// [2021y-02m-20d][18:41:19] birthday of the project
// [2021y-02m-25d][04:10:xx] Idrisov Denis R.
// [2021y-02m-26d][06:30:xx] Idrisov Denis R.
// [2021y-02m-27d][21:58:36] Idrisov Denis R.
// [2021y-02m-28d][07:09:00] Idrisov Denis R.
// [2021y-03m-01d][03:06:12] Idrisov Denis R.
// [2021y-03m-03d][23:47:55] Idrisov Denis R. 009
// [2021y-03m-04d][20:27:52] Idrisov Denis R. 010
// [2021y-03m-05d][23:19:34] Idrisov Denis R. 011
// [2021y-03m-06d][04:06:55] Idrisov Denis R. 012
// [2021y-03m-06d][05:19:34] Idrisov Denis R. 013 PRE
#pragma once
#ifndef dTOOLS_CONFBUILD_USED_
#define dTOOLS_CONFBUILD_USED_ 013 PRE
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
#define dVERSION_MINOR      1
#define dVERSION_PATCH      3

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
