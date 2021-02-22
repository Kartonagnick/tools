
// [2021y-02m-21d] Idrisov Denis R.

#pragma once
#ifndef dTOOLS_SYNCH_USED_ 
#define dTOOLS_SYNCH_USED_ 100
//==============================================================================
//==============================================================================

#include <tools/windows.hpp>
#include <tools/features.hpp>

//==============================================================================
//==============================================================================

namespace tools
{
    class synch
    {
        ::CRITICAL_SECTION m_section;
    public:
        synch() dNOEXCEPT
            : m_section()
        {
            ZeroMemory(&this->m_section, sizeof(this->m_section)); 
            ::InitializeCriticalSection(&this->m_section);
        }

        ~synch() 
        {
            ::DeleteCriticalSection(&this->m_section);
        }

        inline void lock() dNOEXCEPT
        {
            ::EnterCriticalSection(&this->m_section);
        }

        inline void unlock() dNOEXCEPT 
        {
            ::LeaveCriticalSection(&this->m_section);
        }
    };

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