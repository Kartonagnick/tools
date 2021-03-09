
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-16d 13:29:41 May                        +
//+ changed: 2020y-04m-19d 17:08:17 April                      +
//+ macro/comb_values-7.hpp                                    +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_COMB_VALUES_7_USED_
#define dTOOLS_MACRO_COMB_VALUES_7_USED_ 1
                                
#include <tools/macro/foreach-7.hpp>
//==============================================================================
//==============================================================================

    #define dCOMB_VALUES_0(macro, delim) \
        error_0_arguments_not_support__combinations

    #define dCOMB_VALUES_1(macro, delim, a1) \
        macro(1, a1, a1)

    #define dCOMB_VALUES_2(macro, delim, a1, a2) \
        dFOREACH_MAX_7(macro, delim, a1, a1, a2) delim(1) \
        dFOREACH_MAX_7(macro, delim, a2, a1, a2) 

    #define dCOMB_VALUES_3(macro, delim, a1, a2, a3) \
        dFOREACH_MAX_7(macro, delim, a1, a1, a2, a3) delim(1) \
        dFOREACH_MAX_7(macro, delim, a2, a1, a2, a3) delim(2) \
        dFOREACH_MAX_7(macro, delim, a3, a1, a2, a3) 

    #define dCOMB_VALUES_4(macro, delim, a1, a2, a3, a4) \
        dFOREACH_MAX_7(macro, delim, a1, a1, a2, a3, a4) delim(1) \
        dFOREACH_MAX_7(macro, delim, a2, a1, a2, a3, a4) delim(2) \
        dFOREACH_MAX_7(macro, delim, a3, a1, a2, a3, a4) delim(3) \
        dFOREACH_MAX_7(macro, delim, a4, a1, a2, a3, a4) 

    #define dCOMB_VALUES_5(macro, delim, a1, a2, a3, a4, a5) \
        dFOREACH_MAX_7(macro, delim, a1, a1, a2, a3, a4, a5) delim(1) \
        dFOREACH_MAX_7(macro, delim, a2, a1, a2, a3, a4, a5) delim(2) \
        dFOREACH_MAX_7(macro, delim, a3, a1, a2, a3, a4, a5) delim(3) \
        dFOREACH_MAX_7(macro, delim, a4, a1, a2, a3, a4, a5) delim(4) \
        dFOREACH_MAX_7(macro, delim, a5, a1, a2, a3, a4, a5) 

    #define dCOMB_VALUES_6(macro, delim, a1, a2, a3, a4, a5, a6) \
        dFOREACH_MAX_7(macro, delim, a1, a1, a2, a3, a4, a5, a6) delim(1) \
        dFOREACH_MAX_7(macro, delim, a2, a1, a2, a3, a4, a5, a6) delim(2) \
        dFOREACH_MAX_7(macro, delim, a3, a1, a2, a3, a4, a5, a6) delim(3) \
        dFOREACH_MAX_7(macro, delim, a4, a1, a2, a3, a4, a5, a6) delim(4) \
        dFOREACH_MAX_7(macro, delim, a5, a1, a2, a3, a4, a5, a6) delim(5) \
        dFOREACH_MAX_7(macro, delim, a6, a1, a2, a3, a4, a5, a6) 

    #define dCOMB_VALUES_7(macro, delim, a1, a2, a3, a4, a5, a6, a7) \
        dFOREACH_MAX_7(macro, delim, a1, a1, a2, a3, a4, a5, a6, a7) delim(1) \
        dFOREACH_MAX_7(macro, delim, a2, a1, a2, a3, a4, a5, a6, a7) delim(2) \
        dFOREACH_MAX_7(macro, delim, a3, a1, a2, a3, a4, a5, a6, a7) delim(3) \
        dFOREACH_MAX_7(macro, delim, a4, a1, a2, a3, a4, a5, a6, a7) delim(4) \
        dFOREACH_MAX_7(macro, delim, a5, a1, a2, a3, a4, a5, a6, a7) delim(5) \
        dFOREACH_MAX_7(macro, delim, a6, a1, a2, a3, a4, a5, a6, a7) delim(6) \
        dFOREACH_MAX_7(macro, delim, a7, a1, a2, a3, a4, a5, a6, a7) 

    #define dCOMB_VALUES_MAX_7(macro, delim, ...) \
        dMACRO_CHOOSER_7(dCOMB_VALUES, __VA_ARGS__)(macro, delim, __VA_ARGS__)

//==============================================================================
//=== usage ====================================================================
#if 0
#include <iostream>

int main()
{
    #define pp_macro(index, a, b) \
        ss << "(" << index << ", " << #a << ":" << #b << ")";
        
    #define pp_delim(index) \
        ss << ", ";
    
    dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3,4);
}
#endif
//==============================================================================
//==============================================================================
#endif // !dTOOLS_MACRO_COMB_VALUES_7_USED_