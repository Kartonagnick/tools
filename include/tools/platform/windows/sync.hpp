
// [2021y-02m-21d] Idrisov Denis R.

#pragma once
#ifndef dTOOLS_SYNC_USED_ 
#define dTOOLS_SYNC_USED_ 100
//==============================================================================
//==============================================================================

#include <tools/windows.hpp>
#include <tools/features.hpp>

//==============================================================================
//==============================================================================

namespace tools
{
    class sync
    {
        ::CRITICAL_SECTION m_section;
    public:
        sync() dNOEXCEPT
            : m_section()
        {
            ZeroMemory(&this->m_section, sizeof(this->m_section)); 
            ::InitializeCriticalSection(&this->m_section);
        }

        ~sync() 
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

    class sync_guard
    {
        sync& ref;
    public:
        dNOCOPYABLE(sync_guard);

        sync_guard(sync& s) dNOEXCEPT 
            : ref(s)
        {
            ref.lock();
        }
        ~sync_guard() dNOEXCEPT
        {
            ref.unlock();
        }
    };

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_SYNC_USED_