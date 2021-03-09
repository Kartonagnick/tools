
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-16d 11:15:19 May                        +
//+ changed: 2020y-04m-19d 08:07:24 April                      +
//+ macro/overload-7.hpp                                       +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_OVERLOAD_7_USED_
#define dTOOLS_MACRO_OVERLOAD_7_USED_ 1

//==============================================================================

    // support max 7 arguments
    // -- arguments from range inclusive : [0 : 7]

    #define dCHOOSER_7(f1, f2, f3, f4, f5, f6, f7, N, ... ) N

    #define dRECOMPOSER_7(argsWithParentheses) \
        dCHOOSER_7 argsWithParentheses

    #define dNO_ARG_EXPANDER_7(target_) \
        ,,,,,,,target_##_0

//==============================================================================

    #define dCHOOSE_FROM_ARGS_COUNT_7(macro, ...) \
        dRECOMPOSER_7((__VA_ARGS__,  \
            macro##_7, macro##_6, macro##_5, macro##_4, \
            macro##_3, macro##_2, macro##_1, macro##_0  \
        ))

    #define dMACRO_CHOOSER_7(target_, ...)           \
        dCHOOSE_FROM_ARGS_COUNT_7(target_,           \
            dNO_ARG_EXPANDER_7 __VA_ARGS__ (target_) \
        )

//==============================================================================
//==============================================================================

    #define dNO_ARG_EXPANDER_COUNT_7(n) ,,,,,,,0

    #define dCHOOSE_FOR_ARGS_COUNT_7(...) \
        dRECOMPOSER_7((__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0))

    #define dGET_ARGS_COUNT_MAX_7(...) \
        dCHOOSE_FOR_ARGS_COUNT_7(dNO_ARG_EXPANDER_COUNT_7 __VA_ARGS__ (0) )

//==============================================================================
//==============================================================================

    #define dCHOOSE_NULL_OR_MORE_7(macro, ...)          \
        dRECOMPOSER_7((__VA_ARGS__,                     \
            macro##_N, macro##_N, macro##_N, macro##_N, \
            macro##_N, macro##_N, macro##_N, macro##_0  \
        ))

    #define dNULL_OR_MORE_7(macro, ...) \
        dCHOOSE_NULL_OR_MORE_7(macro, dNO_ARG_EXPANDER_7 __VA_ARGS__ (macro) )

//==============================================================================
//=== usage ====================================================================

#if 0
    // usage: 
    #define dPRINT_0() \
        std::cout <<"empty\n"
    
    #define dPRINT_1(a1) \
        std::cout << a1 << '\n'
    
    #define dPRINT_2(a1, a2) \
        std::cout << a1 << ", " << a2 << '\n'
    
    #define dPRINT_3(a1, a2, a3) \
        std::cout << a1 << ", " << a2 << ", " << a3 << '\n'
    
    #define dPRINT_4(a1, a2, a3, a4) \
        std::cout << a1 << ", " << a2 << ", " << a3 << ", " << a4 << '\n'
    
    #define dPRINT_7(a1, a2, a3, a4, a5) \
        std::cout << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5 << '\n'
    
    #define dPRINT(...) \
        dMACRO_CHOOSER_7(dPRINT, __VA_ARGS__)(__VA_ARGS__)

    #define dIF_ARG_COUNT_0(element, delim, ...) \
        dPRINT(element, delim)

    #define dIF_ARG_COUNT_N(element, delim, ...) \
        dPRINT(element, delim, __VA_ARGS__)

    #define dCALL_ONE_OR_MORE(element, delim, ...) \
        dNULL_OR_MORE_7(dIF_ARG_COUNT, __VA_ARGS__)(element, delim, __VA_ARGS__)
    
    #include <iostream>
    
    int main()
    {
        dPRINT();
        dPRINT(1);
        dPRINT(1,2);
        dPRINT(1,2,3);
        dPRINT(1,2,3,4);
        dPRINT(1,2,3,4,5);
        std::cout << dGET_ARGS_COUNT_MAX_7(1, 2, 3, 4, 5) << '\n';

        dCALL_ONE_OR_MORE(1,2);
        dCALL_ONE_OR_MORE(1,2,3);
    }
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MACRO_OVERLOAD_7_USED_
