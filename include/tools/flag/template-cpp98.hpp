
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-28d 00:58:48 february  Idrisov D. R     +
//+ tools/flag/template.hpp                                    +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_FLAG_TEMPLATE_CPP98_USED_ 
#define dTOOLS_FLAG_TEMPLATE_CPP98_USED_ 1

#include <tools/features.hpp>
#ifdef dHAS_CPP11
    #error expected pre c++11
#endif

//==============================================================================
//==============================================================================

namespace tools
{
    template<unsigned flag, unsigned flags> struct add_flag
    {
        // 0 --- none
        // 1 --- enable all
        enum { value =
               flag == 0 ? flags
            :  flag == 1 ? 1
            :  flags | flag
        };
    };

    template<unsigned flag, unsigned flags> struct del_flag
    {
        // 0 --- none
        // 1 --- disable all
        enum { value =
               flag == 0 ? flags
            :  flag == 1 ? 0
            :  flags & (~flag)
        };
    };

    template<unsigned flag, unsigned flags> struct has_any_flag
    {
        // 0 --- none
        // 1 --- all
        enum { value =
               flag  == 0 ? flags == 0
            :  flag  == 1 ? flags != 0
            :  flags == 1 ? flag == 0 ? false : true
            : (flag & flags) != 0
        };
    };

    template<unsigned flag, unsigned flags> struct has_flag
    {
        // 0 --- none
        // 1 --- all
        enum { value =
              flag  == 0 ? flags == 0
            : flag  == 1 ? flags == 1
            : flags == 1 ? flag == 0 ? false : true
            : (flag & flags) == flag
        };
    };

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_FLAG_TEMPLATE_CPP98_USED_
