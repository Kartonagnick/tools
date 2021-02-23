
// [2021y-02m-21d] Idrisov Denis R.
// [2021y-02m-23d] Idrisov Denis R.

#pragma once
#ifndef dTOOLS_SYNCH_USED_ 
#define dTOOLS_SYNCH_USED_ 101
//==============================================================================
//==============================================================================

#include <tools/features.hpp>

#ifdef dHAS_ATOMIC

#include <mutex>

namespace tools
{
    class synch
    {
        ::std::recursive_mutex m_mutex;
    public:
        dNOCOPYABLE(synch);

        synch() dNOEXCEPT : m_mutex() {}

        void lock() dNOEXCEPT
        {
            this->m_mutex.lock();
        }
        void unlock() dNOEXCEPT
        {
            this->m_mutex.unlock();
        }
    };

} // namespace tools

#else

// --- old compiler
namespace tools
{
    class synch
    {
        typedef char arr_t[40];
        union storage
        {
            void* ptr;
            arr_t arr;
        };
        storage m_storage;
    public:
        dNOCOPYABLE(synch);

        ~synch();
        synch() dNOEXCEPT;

        void lock()   dNOEXCEPT;
        void unlock() dNOEXCEPT;
    };

} // namespace tools

#endif

//==============================================================================
//==============================================================================

namespace tools
{
    class synch_guard
    {
        synch& ref;
    public:
        dNOCOPYABLE(synch_guard);

        synch_guard(synch& s) dNOEXCEPT 
            : ref(s)
        {
            ref.lock();
        }
        ~synch_guard() dNOEXCEPT
        {
            ref.unlock();
        }
    };

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_SYNCH_USED_