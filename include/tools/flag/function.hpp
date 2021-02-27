
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-27d 21:41:43 february  Idrisov D. R     +
//+ tools/flag/function.hpp                                    +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_FLAG_FUNCTION_USED_ 
#define dTOOLS_FLAG_FUNCTION_USED_ 100

#include <tools/features.hpp>

//==============================================================================
//=== int ======================================================================
namespace tools
{
    dCONSTEXPR_CPP11 int add_flags(const int flag, const int flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- enable all
        return
              flag == 0 ? flags
            : flag == 1 ? 1
            : flags | flag;
    }

    dCONSTEXPR_CPP11 int del_flags(const int flag, const int flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- disable all
        return
              flag == 0 ? flags
            : flag == 1 ? 0
            : flags & (~flag);
    }

    dCONSTEXPR_CPP11 bool has_any_flags(const int flag, const int flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- all
        return
              flag  == 0 ? flags == 0
            : flag  == 1 ? flags != 0
            : flags == 1 ? flag == 0 ? false : true
            : (flag & flags) != 0;
    }

    dCONSTEXPR_CPP11 bool has_flags(const int flag, const int flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- all
        return
              flag  == 0 ? flags == 0
            : flag  == 1 ? flags == 1
            : flags == 1 ? flag == 0 ? false : true
            : (flag & flags) == flag;
    }

} // namespace tools

//==============================================================================
//=== unsigned =================================================================
namespace tools
{
    dCONSTEXPR_CPP11 unsigned add_flags(const unsigned flag, const unsigned flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- enable all
        return
              flag == 0 ? flags
            : flag == 1 ? 1
            : flags | flag;
    }

    dCONSTEXPR_CPP11 unsigned del_flags(const unsigned flag, const unsigned flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- disable all
        return
              flag == 0 ? flags
            : flag == 1 ? 0
            : flags & (~flag);
    }

    dCONSTEXPR_CPP11 bool has_any_flags(const unsigned flag, const unsigned flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- all
        return
              flag  == 0 ? flags == 0
            : flag  == 1 ? flags != 0
            : flags == 1 ? flag == 0 ? false : true
            : (flag & flags) != 0;
    }

    dCONSTEXPR_CPP11 bool has_flags(const unsigned flag, const unsigned flags) dNOEXCEPT
    {
        // 0 --- none
        // 1 --- all
        return
              flag  == 0 ? flags == 0
            : flag  == 1 ? flags == 1
            : flags == 1 ? flag == 0 ? false : true
            : (flag & flags) == flag;
    }

} // namespace tools

//==============================================================================
//=== usage ====================================================================
#if 0
    enum eFLAGS { 
        eNONE = 0, eALL = 1, eONE = 1<<1, eTWO = 1<<2, eTHREE = 1<<3 
    };

    const size_t v = ::tools::del_flags(eTWO|eTHREE, eONE|eTWO|eTHREE);
    EXPECT_EQ(v, eONE);

    const bool has = ::tools::has_flags(eTWO|eTHREE, eONE|eTWO|eTHREE);
    EXPECT_EQ(has, true);
#endif
//==============================================================================
//==============================================================================
    
#endif // !dTOOLS_FLAG_FUNCTION_USED_
