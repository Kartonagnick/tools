
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-28d 00:58:48 february  Idrisov D. R     +
//+ tools/flag/template.hpp                                    +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_FLAG_TEMPLATE_USED_ 
#define dTOOLS_FLAG_TEMPLATE_USED_ 1
//==============================================================================
//==============================================================================

#include <tools/features.hpp>

#ifdef dHAS_CPP11
    #include <tools/flag/template-cpp11.hpp>
#else
    #include <tools/flag/template-cpp98.hpp>
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_FLAG_TEMPLATE_USED_
