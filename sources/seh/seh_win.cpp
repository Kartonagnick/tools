// [2019y-01m-24d][19:22:08] Idrisov Denis R
//==============================================================================
//==============================================================================

#ifdef _MSC_VER

#include "seh_path.hpp"
#include "seh_win.hpp"
#include <eh.h>
#pragma comment(lib, "psapi.lib")

//==============================================================================
//==============================================================================

namespace tools
{
    namespace seh
    {
        guard::guard() dNOEXCEPT
            : m_agent(::_set_se_translator(rethrow))
        {}

        guard::~guard() 
        {
            typedef ::_se_translator_function
                func_t;
            func_t ptr 
                = static_cast<func_t>(this->m_agent);
            ::_set_se_translator(ptr); 
        }

    } // namespace seh
} // namespace tools

//==============================================================================
//==============================================================================

#endif // ! _MSC_VER

