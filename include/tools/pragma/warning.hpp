
// [2019y-04m-12d][00:00:00] Idrisov Denis R.
// [2020y-09m-05d][18:40:18] Idrisov Denis R.
//==============================================================================
//==============================================================================

#pragma once
#ifndef dTOOLS_PRAGMA_WARNING_USED_ 
#define dTOOLS_PRAGMA_WARNING_USED_

#if 0

    // gcc
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    #pragma GCC diagnostic pop


    #ifdef _MSC_VER
        #pragma warning( push )
        // warning C4521: 'Arg' : multiple copy constructors specified
        #pragma warning(disable : 4521)
    #endif

        // code...

    #ifdef _MSC_VER
        #pragma warning(pop)
    #endif

#endif

//==============================================================================
//==============================================================================

#if defined(__GNUC__) || defined(__MINGW__) || defined(__MINGW32__)
    #define dWRN_UNUSED_LOCAL_TYPEDEFS   "-Wunused-local-typedefs"
    #define dWRN_UNUSED_VARIABLE         "-Wunused-variable"
    #define dWRN_UNUSED_FUNCTION         "-Wunused-function"
    #define dWRN_DELETE_NON_VIRTUAL_DTOR "-Wdelete-non-virtual-dtor"
    #define dWRN_NON_VIRTUAL_DTOR        "-Wnon-virtual-dtor"
    #define dWRN_CTOR_DTOR_PRIVACY       "-Wctor-dtor-privacy"
    #define dWRN_CONVERSION_NULL         "-Wconversion-null"
    #define dWRN_OLD_STYLE_CAST          "-Wold-style-cast"
    #define dWRN_CONVERSION              "-Wconversion"
    #define dWRN_PEDANTIC                "-Wpedantic"
    #define dWRN_EFFC_CPP                "-Weffc++"
#elif defined(_MSC_VER)
    #define dWRN_UNUSED_VARIABLE         4100
    #define dWRN_UNREFERENCED_VARIABLE   4101
    #define dWRN_NON_VIRTUAL_DTOR        4265
    #define dWRN_NON_VIRTUAL_DTOR        4265
    #define dWRN_UNREACHABLE_CODE        4702
    #define dWRN_FORCE_VALUE_TO_BOOL     4800
#endif

//==============================================================================
//==============================================================================

#if defined(__GNUC__) || defined(__MINGW__) || defined(__MINGW32__)

    #define dPRAGMA_GCC_(x) _Pragma (#x)

    #define dPRAGMA_DISABLE(id_warning) \
        dPRAGMA_GCC_(GCC diagnostic ignored id_warning)

    #define dPRAGMA_PUSH _Pragma("GCC diagnostic push")
    #define dPRAGMA_POP  _Pragma("GCC diagnostic pop")

#elif defined(_MSC_VER)

    #define dPRAGMA_DISABLE(id_warning) \
        __pragma(warning(disable: id_warning))

    #define dPRAGMA_PUSH  __pragma(warning(push))
    #define dPRAGMA_POP   __pragma(warning(pop))

#else
    error: compiler not support
#endif

//==============================================================================
//==============================================================================

#if 0
    // usage:

    int main()
    {
        dPRAGMA_PUSH;
        dPRAGMA_DISABLE_WARNING(dWRN_UNUSED_VARIABLE);
        {
            int val;
        }
        dPRAGMA_POP;    
    }

#endif

//==============================================================================
//==============================================================================

#endif // !dTOOLS_PRAGMA_WARNING_USED_