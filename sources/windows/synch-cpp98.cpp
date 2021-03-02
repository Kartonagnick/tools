// [2021y-02m-23d][20:36:58] Idrisov Denis R.

#if defined(_MSC_VER) && _MSC_VER <= 1600
// pragma message("Visual Studio 2010 or older")

#include <tools/windows.hpp>
#include <tools/assert.hpp>
#include <tools/synch.hpp>
#include <new>
//==============================================================================
//==============================================================================

namespace
{
    ::CRITICAL_SECTION* cast(char* storage) dNOEXCEPT
    {
        dASSERT(storage);
        return reinterpret_cast<::CRITICAL_SECTION*>(storage);
    }

    void dummy() dNOEXCEPT
    {
        dSTATIC_ASSERT(
            sizeof(::CRITICAL_SECTION) <= 40,
            INVALID_SIZE_OF_STORAGE
        );
    }

} // namespace

//==============================================================================
//==============================================================================

namespace tools
{
    synch::synch() dNOEXCEPT
    {
        new (this->m_storage.arr) ::CRITICAL_SECTION;
        ::CRITICAL_SECTION* ptr = cast(this->m_storage.arr);
        dASSERT(ptr);

        ZeroMemory(ptr, sizeof(::CRITICAL_SECTION)); 
        ::InitializeCriticalSection(ptr);
    }

    synch::~synch() 
    {
        ::CRITICAL_SECTION* ptr = cast(this->m_storage.arr);
        dASSERT(ptr);
        ::DeleteCriticalSection(ptr);
    }

    void synch::lock() dNOEXCEPT
    {
        ::CRITICAL_SECTION* ptr = cast(this->m_storage.arr);
        dASSERT(ptr);
        ::EnterCriticalSection(ptr);
    }

    void synch::unlock() dNOEXCEPT 
    {
        ::CRITICAL_SECTION* ptr = cast(this->m_storage.arr);
        dASSERT(ptr);
        ::LeaveCriticalSection(ptr);
    }

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !(defined(_MSC_VER) && _MSC_VER <= 1600)