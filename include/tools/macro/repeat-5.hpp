
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-05m-15d 11:15:19 May                        +
//+ changed: 2020y-04m-19d 19:34:24 April                      +
//+ macro/repeat-5.hpp                                         +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef dTOOLS_MACRO_REPEAT_5_USED_
#define dTOOLS_MACRO_REPEAT_5_USED_ 1
//==============================================================================
//=== dREPEAT ==================================================================

    // support 5 iterations

    #define dREPEAT_1(macro, delim) macro(1)
    #define dREPEAT_2(macro, delim) dREPEAT_1(macro, delim) delim(2) macro(2)
    #define dREPEAT_3(macro, delim) dREPEAT_2(macro, delim) delim(3) macro(3)
    #define dREPEAT_4(macro, delim) dREPEAT_3(macro, delim) delim(4) macro(4)
    #define dREPEAT_5(macro, delim) dREPEAT_4(macro, delim) delim(5) macro(5)

    #define dREPEAT(macro, delim, n) dREPEAT_##n(macro, delim)

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MACRO_REPEAT_5_USED_