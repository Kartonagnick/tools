
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-16d 13:29:41 May                        +
//+ changed: 2020y-04m-19d 06:45:10 April                      +
//+ macro/args-7.hpp                                           +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_ARGS_7_USED_
#define dTOOLS_MACRO_ARGS_7_USED_ 1

#include <tools/macro/overload-7.hpp>
//==============================================================================
//=== dFIRST_ARG ===============================================================

    #define dFIRST_ARG_(arg, ...) arg
    #define dEXTRACT_FIRST_ARG_(args) dFIRST_ARG_ args
    #define dFIRST_ARG(...) dEXTRACT_FIRST_ARG_((__VA_ARGS__, dimmy))

//==============================================================================
//=== dGET_ARG_7 ===============================================================

    // support max 7 arguments
    // -- arguments from range inclusive : [0 : 7]

    #define dGET_ARG_0()
    #define dGET_ARG_1(a1) a1
    #define dGET_ARG_2(a1, a2) a2
    #define dGET_ARG_3(a1, a2, a3) a3
    #define dGET_ARG_4(a1, a2, a3, a4) a4
    #define dGET_ARG_5(a1, a2, a3, a4, a5) a5
    #define dGET_ARG_6(a1, a2, a3, a4, a5, a6) a6
    #define dGET_ARG_7(a1, a2, a3, a4, a5, a6, a7) a7

    #define dLAST_ARG_MAX_7(...) \
        dMACRO_CHOOSER_7(dGET_ARG, __VA_ARGS__)(__VA_ARGS__)

    #define dGET_ARG_NUM_0(...)
    #define dGET_ARG_NUM_1(a1, ...) a1
    #define dGET_ARG_NUM_2(a1, a2, ...) a2
    #define dGET_ARG_NUM_3(a1, a2, a3, ...) a3
    #define dGET_ARG_NUM_4(a1, a2, a3, a4, ...) a4
    #define dGET_ARG_NUM_5(a1, a2, a3, a4, a5, ...) a5
    #define dGET_ARG_NUM_6(a1, a2, a3, a4, a5, a6, ...) a6
    #define dGET_ARG_NUM_7(a1, a2, a3, a4, a5, a6, a7, ...) a7

    #define dEXTRACT_GET_ARG_(num, args) dGET_ARG_NUM_##num args
    #define dGET_ARG(num, ...) \
        dEXTRACT_GET_ARG_(num, (__VA_ARGS__, dummy))

//==============================================================================
//=== dFIRST_ARGS_7 ============================================================

    // support max 7 arguments
    // -- arguments from range inclusive : [0 : 5]

    #define dFIRST_ARGS_7(a1, a2, a3, a4, a5, a6, a7, ...) a1, a2, a3, a4, a5, a6, a7
    #define dFIRST_ARGS_6(a1, a2, a3, a4, a5, a6, ...) a1, a2, a3, a4, a5, a6
    #define dFIRST_ARGS_5(a1, a2, a3, a4, a5, ...) a1, a2, a3, a4, a5
    #define dFIRST_ARGS_4(a1, a2, a3, a4, ...) a1, a2, a3, a4
    #define dFIRST_ARGS_3(a1, a2, a3, ...) a1, a2, a3
    #define dFIRST_ARGS_2(a1, a2, ...) a1, a2
    #define dFIRST_ARGS_1(a1, ...) a1
    #define dFIRST_ARGS_0(...) 

    #define dEXTRACT_FIRST_ARGS_(num, args) dFIRST_ARGS_##num args
    #define dFIRST_ARGS(num, ...) \
        dEXTRACT_FIRST_ARGS_(num, (__VA_ARGS__, dummy))

//==============================================================================
//=== dREVERT_ARGS_7 ===========================================================

    #define dREVERT_ARGS_7(a1, a2, a3, a4, a5, a6, a7) a7, a6, a5, a4, a3, a2, a1
    #define dREVERT_ARGS_6(a1, a2, a3, a4, a5, a6) a6, a5, a4, a3, a2, a1
    #define dREVERT_ARGS_5(a1, a2, a3, a4, a5) a5, a4, a3, a2, a1
    #define dREVERT_ARGS_4(a1, a2, a3, a4) a4, a3, a2, a1
    #define dREVERT_ARGS_3(a1, a2, a3) a3, a2, a1
    #define dREVERT_ARGS_2(a1, a2) a2, a1
    #define dREVERT_ARGS_1(a1) a1
    #define dREVERT_ARGS_0() 

    #define dREVERT_ARGS_MAX_7(...) \
        dMACRO_CHOOSER_7(dREVERT_ARGS, __VA_ARGS__)(__VA_ARGS__)

//==============================================================================
//=== dLAST_ARGS_MAX_7 =========================================================

    #define dEXTRACT_LAST_ARGS_(...) \
        dREVERT_ARGS_MAX_7( __VA_ARGS__ )

    #define dLAST_ARGS_MAX_7(num, ...)               \
        dEXTRACT_LAST_ARGS_(                         \
            dFIRST_ARGS(                             \
                num, dREVERT_ARGS_MAX_7(__VA_ARGS__) \
            )                                        \
        )

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MACRO_ARGS_7_USED_
