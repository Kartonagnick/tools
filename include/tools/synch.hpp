
// [2021y-02m-21d] Idrisov Denis R.
// [2021y-02m-23d] Idrisov Denis R.

#pragma once
#ifndef dTOOLS_SYNCH_USED_ 
#define dTOOLS_SYNCH_USED_ 102
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
    class synch_dummy
    {
    public:
        void lock()   dNOEXCEPT {}
        void unlock() dNOEXCEPT {}
    };

    template<class Synch> class synch_lock
    {
        Synch& ref;
    public:
        dNOCOPYABLE(synch_lock);

        synch_lock(Synch& s) dNOEXCEPT 
            : ref(s)
        { ref.lock(); }

        ~synch_lock() dNOEXCEPT
        { ref.unlock(); }
    };

    typedef synch_lock<synch> 
        synch_guard;

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_SYNCH_USED_