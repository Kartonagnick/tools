
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-16d 13:29:41 May                        +
//+ changed: 2020y-04m-19d 06:45:10 April                      +
//+ macro/args-5.hpp                                           +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_ARGS_5_USED_
#define dTOOLS_MACRO_ARGS_5_USED_ 1

#include <tools/macro/overload-5.hpp>
//==============================================================================
//=== dFIRST_ARG ===============================================================

    #define dFIRST_ARG_(arg, ...) arg
    #define dEXTRACT_FIRST_ARG_(args) dFIRST_ARG_ args
    #define dFIRST_ARG(...) dEXTRACT_FIRST_ARG_((__VA_ARGS__, dimmy))

//==============================================================================
//=== dGET_ARG_5 ===============================================================

    // support max 5 arguments
    // -- arguments from range inclusive : [0 : 5]

    #define dGET_ARG_0()
    #define dGET_ARG_1(a1) a1
    #define dGET_ARG_2(a1, a2) a2
    #define dGET_ARG_3(a1, a2, a3) a3
    #define dGET_ARG_4(a1, a2, a3, a4) a4
    #define dGET_ARG_5(a1, a2, a3, a4, a5) a5

    #define dLAST_ARG_MAX_5(...) \
        dMACRO_CHOOSER_5(dGET_ARG, __VA_ARGS__)(__VA_ARGS__)

    #define dGET_ARG_NUM_0(...)
    #define dGET_ARG_NUM_1(a1, ...) a1
    #define dGET_ARG_NUM_2(a1, a2, ...) a2
    #define dGET_ARG_NUM_3(a1, a2, a3, ...) a3
    #define dGET_ARG_NUM_4(a1, a2, a3, a4, ...) a4
    #define dGET_ARG_NUM_5(a1, a2, a3, a4, a5, ...) a5

    #define dEXTRACT_GET_ARG_(num, args) dGET_ARG_NUM_##num args

    #define dGET_ARG(num, ...) \
        dEXTRACT_GET_ARG_(num, (__VA_ARGS__, dummy))

//==============================================================================
//=== dFIRST_ARGS_5 ============================================================

    // support max 5 arguments
    // -- arguments from range inclusive : [0 : 5]

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
//=== dREVERT_ARGS_5 ===========================================================

    #define dREVERT_ARGS_5(a1, a2, a3, a4, a5) a5, a4, a3, a2, a1
    #define dREVERT_ARGS_4(a1, a2, a3, a4) a4, a3, a2, a1
    #define dREVERT_ARGS_3(a1, a2, a3) a3, a2, a1
    #define dREVERT_ARGS_2(a1, a2) a2, a1
    #define dREVERT_ARGS_1(a1) a1
    #define dREVERT_ARGS_0()

    #define dREVERT_ARGS_MAX_5(...) \
        dMACRO_CHOOSER_5(dREVERT_ARGS, __VA_ARGS__)(__VA_ARGS__)

//==============================================================================
//=== dLAST_ARGS_MAX_5 =========================================================

    #define dEXTRACT_LAST_ARGS_(...) \
        dREVERT_ARGS_MAX_5( __VA_ARGS__ )

    #define dLAST_ARGS_MAX_5(num, ...)               \
        dEXTRACT_LAST_ARGS_(                         \
            dFIRST_ARGS(                             \
                num, dREVERT_ARGS_MAX_5(__VA_ARGS__) \
            )                                        \
        )

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MACRO_ARGS_5_USED_
