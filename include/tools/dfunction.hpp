
// [2019y-04m-29d][18:40:18] Idrisov Denis R.
// [2021y-02m-26d][02:22:26] Idrisov Denis R.
//==============================================================================
//==============================================================================

//--- cross-platform macro display function name

#ifndef dTOOLS_DFUNCTION_USED_ 
#define dTOOLS_DFUNCTION_USED_ 100

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW__)
    #define dFUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define dFUNCTION __FUNCSIG__
#else
    #define dFUNCTION __FUNCTION__
#endif

//==============================================================================
//==============================================================================
#endif //! dTOOLS_DFUNCTION_USED_

