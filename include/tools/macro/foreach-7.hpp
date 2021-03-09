
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-16d 13:29:41 May                        +
//+ changed: 2020y-04m-19d 08:07:24 April                      +
//+ macro/foreach-7.hpp                                        +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_FOREACH_7_USED_
#define dTOOLS_MACRO_FOREACH_7_USED_ 1

#include <tools/macro/overload-7.hpp>
//==============================================================================
//==============================================================================

    #define dFOREACH_0(macro, delim, arg) \
        error_0_arguments_not_support__foreach

    #define dFOREACH_1(macro, delim, arg, a1) \
        macro(1, arg, a1)

    #define dFOREACH_2(macro, delim, arg, a1, a2) \
        dFOREACH_1(macro, delim, arg, a1) delim(1) macro(2, arg, a2)

    #define dFOREACH_3(macro, delim, arg, a1, a2, a3) \
        dFOREACH_2(macro, delim, arg, a1, a2) delim(2) macro(3, arg, a3)

    #define dFOREACH_4(macro, delim, arg, a1, a2, a3, a4) \
        dFOREACH_3(macro, delim, arg, a1, a2, a3) delim(3) macro(4, arg, a4)

    #define dFOREACH_5(macro, delim, arg, a1, a2, a3, a4, a5) \
        dFOREACH_4(macro, delim, arg, a1, a2, a3, a4) \
        delim(4) macro(5, arg, a5)

    #define dFOREACH_6(macro, delim, arg, a1, a2, a3, a4, a5, a6) \
        dFOREACH_5(macro, delim, arg, a1, a2, a3, a4, a5) \
        delim(5) macro(6, arg, a6)

    #define dFOREACH_7(macro, delim, arg, a1, a2, a3, a4, a5, a6, a7) \
        dFOREACH_6(macro, delim, arg, a1, a2, a3, a4, a5, a6) \
        delim(6) macro(7, arg, a7)

    #define dFOREACH_EXECUTE_7(element, delim, arg, ...) \
        dMACRO_CHOOSER_7(dFOREACH, __VA_ARGS__)(element, delim, arg, __VA_ARGS__)

    #define dFOREACH_MAX_7_ARGS_0(element, delim, arg, ...) \
        error_0_arguments_not_support__foreach

    #define dFOREACH_MAX_7_ARGS_N(element, delim, arg, ...) \
        dFOREACH_EXECUTE_7(element, delim, arg, __VA_ARGS__)

    #define dFOREACH_MAX_7(element, delim, arg, ...) \
        dNULL_OR_MORE_7(dFOREACH_MAX_7_ARGS, __VA_ARGS__)(element, delim, arg, __VA_ARGS__)

//==============================================================================
//=== usage ====================================================================

#if 0
    // usage: 

    #define pp_beg(count) \
        std::cout << "begin(" << count << ")\n";

    #define pp_element(index, name) \
        std::cout << "[" << index << "]" << name;

    #define pp_delim(index) \
        std::cout << "[" << index << "]\n";

    #define pp_end(count) \
        std::cout << "\n" << "end(" << count << ")\n";

    #define pp_enum(...)                                  \
        pp_beg(dGET_ARGS_COUNT_MAX_7(__VA_ARGS__))        \
        dFOREACH_MAX_7(pp_element, pp_delim, __VA_ARGS__) \
        pp_end(dGET_ARGS_COUNT_MAX_7(__VA_ARGS__))

    #include <iostream>
    
    int main()
    {
        //pp_enum();    std::cout << "==========\n";
        pp_enum(1);     std::cout << "==========\n";
        pp_enum(1,2);   std::cout << "==========\n";
        pp_enum(1,2,3); std::cout << "==========\n";
    }
#endif

//==============================================================================
//==============================================================================    
#endif // !dTOOLS_MACRO_FOREACH_7_USED_
