
// [2021y-02m-21d] Idrisov Denis R.

#pragma once
#ifndef dTOOLS_COUNTER_USED_ 
#define dTOOLS_COUNTER_USED_ 100

#include <tools/features.hpp>
//================================================================================
//================================================================================

#ifdef dHAS_ATOMIC
#include <atomic>
#include <cstddef>

namespace tools 
{
    class counter
    {
        ::std::atomic<size_t> m_count;
    public:
        dNOCOPYABLE(counter);

        counter(const size_t v = 0) dNOEXCEPT
            : m_count(v) 
        {}

        counter& operator=(const size_t v) dNOEXCEPT
        {
            this->m_count = v;
            return *this;
        }

        // prefix ++it
        counter& operator++() dNOEXCEPT
        {
            ++this->m_count;
            return *this;
        }

        counter& operator--() dNOEXCEPT
        {
            --this->m_count;
            return *this;
        }

        operator size_t() const dNOEXCEPT
        {
            return this->m_count;
        }
    };

} //namespace tools

#else

namespace tools 
{
    class counter
    {
        mutable volatile long m_count;
    public:
        dNOCOPYABLE(counter);

        counter(const size_t = 0) dNOEXCEPT;

        counter& operator=(const size_t v) dNOEXCEPT;

        // prefix ++it
        counter& operator++() dNOEXCEPT;
        counter& operator--() dNOEXCEPT;

        operator size_t() const dNOEXCEPT;
    };

} //namespace tools

#endif // !dHAS_ATOMIC

//================================================================================
//================================================================================
#endif // !dTOOLS_COUNTER_USED_ 



        
