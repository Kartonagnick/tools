
// [2021y-02m-21d] Idrisov Denis R.

#pragma once
#ifndef dTOOLS_COPIES_USED_ 
#define dTOOLS_COPIES_USED_ 100

#include <tools/assert.hpp>
#include <tools/features.hpp>
#include <cstddef>
//================================================================================
//================================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1600
// pragma message("Visual Studio 2010 or newer")
#include <atomic>

namespace tools 
{
    template<class T> class copies
    {
        typedef ::std::atomic<size_t>
            count_t;
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
            static count_t n(0); 
            return n;
        }
    };

} //namespace tools

#else

// pragma message("Visual Studio 2010 or older")

#include <tools/counter.hpp>

namespace tools 
{
    template<class T> class copies
    {
        typedef tools::counter
            count_t;
    public:
        ~copies()
        {
            dASSERT(copies::instances() > 0 &&
                "error: DESTRUCTOR CALLED WITHOUT CONSTRUCTOR");
            copies::instances_().decrement();
        }

        copies() dNOEXCEPT
        {
            copies::instances_().increment();
        }

        copies(const copies&) dNOEXCEPT 
        {
            copies::instances_().increment();
        }

        static size_t instances() dNOEXCEPT 
        {
            return copies::instances_().value();
        }
    private:
        static count_t& instances_() dNOEXCEPT
        {
            static count_t n; 
            return n;
        }
    };

} //namespace tools

#endif // old compilers

//================================================================================
//================================================================================
#endif // !dTOOLS_COPIES_USED_ 
