
// [2020y-09m-06d][00:00:00] Idrisov Denis R.
// [2021y-02m-20d][18:40:18] Idrisov Denis R.
// [2021y-03m-17d][22:25:08] Idrisov Denis R.
//==============================================================================
//==============================================================================
#pragma once
#ifndef dTOOLS_PRAGMA_USED_ 
#define dTOOLS_PRAGMA_USED_ 100
//==============================================================================
//==============================================================================

#ifdef _MSC_VER
    #define dPRAGMA_POP __pragma(warning(pop))

    // 'operator=' should return a reference to '*this' [-Werror=effc++]
    #define dPRAGMA_PUSH_WARNING_EFFECT \
        __pragma(warning(push))

    // 'operator=' should return a reference to '*this' [-Werror=effc++]
    #define dPRAGMA_PUSH_WARNING_RETURN_REFERENCE_TO_THIS \
        __pragma(warning(push))

    // warning C4180: qualifier applied to function type has no meaning; ignored
    // example: const int() ===> int()
    #define dPRAGMA_PUSH_WARNING_QUALIFIER_RETURN_TYPE \
        __pragma(warning(push)) \
        __pragma(warning(disable: 4180))

#else
    #define dPRAGMA_POP _Pragma("GCC diagnostic pop")

    #define dPRAGMA_PUSH_WARNING_EFFECT \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Weffc++\"")

    #define dPRAGMA_PUSH_WARNING_RETURN_REFERENCE_TO_THIS \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Weffc++\"")

    #define dPRAGMA_PUSH_WARNING_QUALIFIER_RETURN_TYPE \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wignored-qualifiers\"")

    #define dPRAGMA_PUSH_WARNING_ZERO_SIZE_ARRAY \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wpedantic\"")
#endif

//==============================================================================
//==============================================================================

#endif // !dTOOLS_PRAGMA_USED_
