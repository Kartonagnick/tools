
#if defined(_MSC_VER) && _MSC_VER < 1600
// pragma message("Visual Studio 2008 or older")

#include <tools/counter.hpp>
#include <tools/windows.hpp>
#include <tools/assert.hpp>

//================================================================================
//================================================================================

namespace tools 
{
    counter::counter(const size_t) dNOEXCEPT
    {
        ::InterlockedExchange(&this->m_count, 0);
    }

    counter& counter::operator=(const size_t v) dNOEXCEPT
    {
        const long val = static_cast<long>(v);
        ::InterlockedExchange(&this->m_count, val);
        return *this;
    }

    // prefix ++it
    counter& counter::operator++() dNOEXCEPT
    {
        ::InterlockedIncrement(&this->m_count);
        return *this;
    }
    counter& counter::operator--() dNOEXCEPT
    {
        ::InterlockedDecrement(&this->m_count);
        return *this;
    }

    counter::operator size_t() const dNOEXCEPT
    {
        const long v
            = ::InterlockedExchangeAdd(&this->m_count, 0);
        dASSERT(v >= 0);
        return static_cast<size_t>(v);
    }

} //namespace tools

//================================================================================
//================================================================================
#endif // defined(_MSC_VER) && _MSC_VER < 1600