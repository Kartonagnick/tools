// [2021y-02m-21d][18:40:18] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_COPIES_USED_ 
#define dTOOLS_COPIES_USED_ 100

#include <tools/assert.hpp>
#include <tools/features.hpp>
#include <cstddef>
//================================================================================
//================================================================================

#if dHAS_ATOMIC
    #include <atomic>
#else
    #include <tools/counter.hpp>
#endif

namespace tools 
{
    template<class T> class copies
    {
        #if dHAS_ATOMIC
            typedef ::std::atomic<size_t> count_t;
        #else
            typedef ::tools::counter count_t;
        #endif
    public:
        ~copies()
        {
            dASSERT(copies::instances() > 0 &&
                "error: DESTRUCTOR CALLED WITHOUT CONSTRUCTOR");
            --instances_();
        }

        copies() dNOEXCEPT { ++copies::instances_(); }

        copies(const copies&) dNOEXCEPT 
            { ++copies::instances_(); }

        static size_t instances() dNOEXCEPT 
            { return copies::instances_(); }
    private:
        static count_t& instances_() dNOEXCEPT
        {
            static count_t n; 
            return n;
        }
    };

} //namespace tools

//================================================================================
//================================================================================
#endif // !dTOOLS_COPIES_USED_ 
