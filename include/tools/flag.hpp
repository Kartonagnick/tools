
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-27d 02:20:05 february  Idrisov D. R     +
//+ flag.hpp                                                   +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_FLAG_USED_ 
#define dTOOLS_FLAG_USED_ 101

#include <tools/features.hpp>
#include <tools/synch.hpp>

//==============================================================================
//==============================================================================

namespace std
{
    template<class T> struct atomic;
}

//==============================================================================
//==============================================================================
namespace tools
{
    template<class Enum, class Mutex = synch> 
        class flag;

    namespace detail_flag
    {
        template<class t> int from(const t& fl) dNOEXCEPT
        {
            const int he = static_cast<int>(fl);
            if ((he & 1) != 0)
                return 1;
            return he;
        }

        template<class from, class ret>
        void copy_from_to(const from& src, ret& dst) dNOEXCEPT
        {
            dst = static_cast<ret>(src);
        }

        template<class from, class t>
        void copy_from_to(const from& src, ::std::atomic<t>& dst) dNOEXCEPT
        {
            dst = static_cast<t>(src);
        }

    } // namespace detail_flag

} // namespace tools

#include <tools/flag/flag_synch.hpp>
#include <tools/flag/flag_void.hpp>

//==============================================================================
//=== usage ====================================================================
#if 0
    enum eFLAGS { eNONE = 0, eONE = 1<<1, eTWO = 1<<2, eTHREE = 1<<3 };
    using flag_t = tools::flag<eFLAGS> ;
    
    flag_t f(eONE|eTWO);
    EXPECT_EQ(eONE|eTWO,    f.getByEnumeration()    );
    EXPECT_EQ(false,        f.empty()               );
    EXPECT_EQ(true,        (f)? true: false         );
    EXPECT_EQ(true,         f.has(eONE)             );
    EXPECT_EQ(true,         f.has(eONE|eTWO)        );
    EXPECT_EQ(false,        f.has(eONE|eTWO|eTHREE) );
    EXPECT_EQ(true,         f.hasAny(eONE|eTWO)     );
    EXPECT_EQ(true,         f.hasAny(eTWO|eTHREE)   );
    EXPECT_EQ(false,        f.hasonly(eONE)         );
    EXPECT_EQ(true,         f.hasonly(eONE|eTWO)    );
    
    f.validOnly(eONE);
               
    EXPECT_EQ(eONE,   f.getByEnumeration()  );
    EXPECT_EQ(false,  f.empty()             );
    EXPECT_EQ(true,  (f)? true: false       );
    EXPECT_EQ(true,   f.has(eONE)           );
    EXPECT_EQ(false,  f.has(eONE|eTWO)      );
    EXPECT_EQ(true,   f.hasAny(eONE|eTWO)   );
    EXPECT_EQ(false,  f.hasAny(eTWO|eTHREE) );
    EXPECT_EQ(true,   f.hasonly(eONE)       );
    EXPECT_EQ(false,  f.hasonly(eONE|eTWO)  );
#endif
//==============================================================================
//==============================================================================
    
#endif // !dTOOLS_FLAG_USED_
