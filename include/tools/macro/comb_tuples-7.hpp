
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-16d 13:29:41 May                        +
//+ changed: 2020y-04m-19d 08:23:17 April                      +
//+ macro/comb_tuples-7.hpp                                    +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_COMB_TYPLES_7_USED_
#define dTOOLS_MACRO_COMB_TYPLES_7_USED_ 1
                                
#include <tools/macro/foreach-7.hpp>
//==============================================================================
//==============================================================================

    #define dCOMB_TUPLES_EXPAND(...) __VA_ARGS__

    #define dCOMB_TUPLES_0(macro, delim, collect) \
        error_0_arguments_not_support__each_for_each

    #define dCOMB_TUPLES_1(macro, delim, collect, a1) \
        dFOREACH_MAX_7(macro, delim, a1, dCOMB_TUPLES_EXPAND collect)

    #define dCOMB_TUPLES_2(macro, delim, collect, a1, a2) \
        dCOMB_TUPLES_1(macro, delim, collect, a1) \
        delim(1) dFOREACH_MAX_7(macro, delim, a2, dCOMB_TUPLES_EXPAND collect)

    #define dCOMB_TUPLES_3(macro, delim, collect, a1, a2, a3) \
        dCOMB_TUPLES_2(macro, delim, collect, a1, a2) \
        delim(2) dFOREACH_MAX_7(macro, delim, a3, dCOMB_TUPLES_EXPAND collect)

    #define dCOMB_TUPLES_4(macro, delim, collect, a1, a2, a3, a4) \
        dCOMB_TUPLES_3(macro, delim, collect, a1, a2, a3) \
        delim(3) dFOREACH_MAX_7(macro, delim, a4, dCOMB_TUPLES_EXPAND collect)

    #define dCOMB_TUPLES_5(macro, delim, collect, a1, a2, a3, a4, a5) \
        dCOMB_TUPLES_4(macro, delim, collect, a1, a2, a3, a4) \
        delim(4) dFOREACH_MAX_7(macro, delim, a5, dCOMB_TUPLES_EXPAND collect)

    #define dCOMB_TUPLES_6(macro, delim, collect, a1, a2, a3, a4, a5, a6) \
        dCOMB_TUPLES_5(macro, delim, collect, a1, a2, a3, a4, a5) \
        delim(5) dFOREACH_MAX_7(macro, delim, a6, dCOMB_TUPLES_EXPAND collect)

    #define dCOMB_TUPLES_7(macro, delim, collect, a1, a2, a3, a4, a5, a6, a7) \
        dCOMB_TUPLES_6(macro, delim, collect, a1, a2, a3, a4, a5, a6) \
        delim(6) dFOREACH_MAX_7(macro, delim, a7, dCOMB_TUPLES_EXPAND collect)

    #define dSTART_COMB_TUPLES_MAX_7(macro, delim, collect2, ...) \
        dMACRO_CHOOSER_7(dCOMB_TUPLES, __VA_ARGS__)(macro, delim, collect2, __VA_ARGS__)

    #define dCOMB_TUPLES_MAX_7(macro, delim, collect1, collect2) \
        dSTART_COMB_TUPLES_MAX_7(macro, delim, collect2, dCOMB_TUPLES_EXPAND collect1)

//==============================================================================
//=== usage ====================================================================
#if 0
#include <iostream>

int main()
{
    #define pp_macro(index, a, b) \
        ss << "(" << index << ", " << #a << " vs " << #b << ")";

    #define pp_delim(index) \
        ss << ", ";
    
    dCOMB_TUPLES_MAX_7(pp_macro, pp_delim, (1,2), (3,4));
}
#endif
//==============================================================================
//==============================================================================
#endif // !dTOOLS_MACRO_COMB_TYPLES_7_USED_