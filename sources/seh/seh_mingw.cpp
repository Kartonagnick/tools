// [2019y-01m-24d][19:22:08] Idrisov Denis R

#if defined(__MINGW__) || defined(__MINGW32__)

#include <tools/seh.hpp>
#include <tools/windows.hpp>
#include <tools/assert.hpp>
#include <cstdio>

//==============================================================================
//==============================================================================

namespace tools
{
    namespace seh
    {
        namespace
        {
            ::LONG CALLBACK vectoredExceptionHandler(::PEXCEPTION_POINTERS ep)
            {
                ::std::printf(
                    "entering vectorized ex. handler 0x%lx...\n",
                    ep->ExceptionRecord->ExceptionCode
                );
                return EXCEPTION_CONTINUE_SEARCH;
            }

            ::LONG WINAPI unhandledExecptionFilter(::PEXCEPTION_POINTERS ep)
            {
                ::std::printf(
                    "entering unhandled ex. filter 0x%lx...\n",
                    ep->ExceptionRecord->ExceptionCode
                );
                // should terminate process.
                return EXCEPTION_EXECUTE_HANDLER;
            }

        } // namespace

//==============================================================================
//==============================================================================

        guard::guard() noexcept
            : m_agent()
        {
            this->m_agent = ::AddVectoredExceptionHandler(
                1, vectoredExceptionHandler
            );

            dASSERT(this->m_agent);
            ::SetUnhandledExceptionFilter(unhandledExecptionFilter);
        }

        guard::~guard()
        {
            const auto success
                = ::RemoveVectoredExceptionHandler(this->m_agent) != 0;
            dASSERT(success);
            (void) success;
        }

    } // namespace seh

} // namespace tools

//==============================================================================
//==============================================================================

#endif // #if defined(__MINGW__) || defined(__MINGW32__)

