// [2019y-01m-24d][19:22:08] Idrisov Denis R
// [2021y-03m-07d][09:29:49] Idrisov Denis R
#pragma once

#ifdef _WIN32 

#include <tools/seh.hpp>
#include <tools/features.hpp>
#include <tools/windows.hpp>
#include <sstream>
#include <iomanip>
#include <psapi.h>
//==============================================================================
//==============================================================================

namespace tools
{
    typedef ::std::string 
        str_t;

    namespace seh
    {
        namespace
        {

            inline const char* opDescription(const ::ULONG opcode) dNOEXCEPT
            {
                switch (opcode)
                {
                    case  0: return "read";
                    case  1: return "write";
                    case  8: return "user-mode data execution prevention (DEP) violation";
                    default: return "unknown";
                }
            }

            inline const char* seDescription(const ::ULONG code) dNOEXCEPT
            {
                switch (code)
                {
                    case EXCEPTION_ACCESS_VIOLATION:         return "ACCESS_VIOLATION";
                    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "ARRAY_BOUNDS_EXCEEDED";
                    case EXCEPTION_BREAKPOINT:               return "BREAKPOINT";
                    case EXCEPTION_DATATYPE_MISALIGNMENT:    return "DATATYPE_MISALIGNMENT";
                    case EXCEPTION_FLT_DENORMAL_OPERAND:     return "FLT_DENORMAL_OPERAND";
                    case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "FLT_DIVIDE_BY_ZERO";
                    case EXCEPTION_FLT_INEXACT_RESULT:       return "FLT_INEXACT_RESULT";
                    case EXCEPTION_FLT_INVALID_OPERATION:    return "FLT_INVALID_OPERATION";
                    case EXCEPTION_FLT_OVERFLOW:             return "FLT_OVERFLOW";
                    case EXCEPTION_FLT_STACK_CHECK:          return "FLT_STACK_CHECK";
                    case EXCEPTION_FLT_UNDERFLOW:            return "FLT_UNDERFLOW";
                    case EXCEPTION_ILLEGAL_INSTRUCTION:      return "ILLEGAL_INSTRUCTION";
                    case EXCEPTION_IN_PAGE_ERROR:            return "IN_PAGE_ERROR";
                    case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "INT_DIVIDE_BY_ZERO";
                    case EXCEPTION_INT_OVERFLOW:             return "INT_OVERFLOW";
                    case EXCEPTION_INVALID_DISPOSITION:      return "INVALID_DISPOSITION";
                    case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "NONCONTINUABLE_EXCEPTION";
                    case EXCEPTION_PRIV_INSTRUCTION:         return "PRIV_INSTRUCTION";
                    case EXCEPTION_SINGLE_STEP:              return "SINGLE_STEP";
                    case EXCEPTION_STACK_OVERFLOW:           return "STACK_OVERFLOW";
                    default: return "EXCEPTION_UNKNOWN";
                }
            }

            inline str_t information(const ::_EXCEPTION_POINTERS& frame, const ::ULONG code)
            {
                ::PVOID& address
                    = frame.ExceptionRecord->ExceptionAddress;


                ::ULONG_PTR* info
                    = frame.ExceptionRecord->ExceptionInformation;

                ::HMODULE hm;
                ::GetModuleHandleEx(
                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                    static_cast<::LPCTSTR>(address),
                    &hm
                );

                ::MODULEINFO mi;
                ::GetModuleInformation(::GetCurrentProcess(), hm, &mi, sizeof(mi));

                char fn[MAX_PATH];
                ::GetModuleFileNameExA(::GetCurrentProcess(), hm, fn, MAX_PATH);

                ::std::ostringstream oss;

                oss << tools::seh::seDescription(code)
                    << " at address 0x" << ::std::hex << address << ::std::dec
                    << " (" << tools::seh::shortPath(fn)
                    << " loaded at base address 0x"
                    << ::std::hex << mi.lpBaseOfDll
                    << ")";

                if (code == EXCEPTION_ACCESS_VIOLATION || code == EXCEPTION_IN_PAGE_ERROR)
                {
                    const ::ULONG op = static_cast<::ULONG>(info[0]);
                    oss << ". Invalid  "
                        << tools::seh::opDescription(op)
                        << " at address 0x"
                        << ::std::hex << info[1] << ::std::dec;
                }
                if (code == EXCEPTION_IN_PAGE_ERROR)
                {
                    oss << ". Underlying NTSTATUS code that resulted in the exception "
                        << info[2];
                }
                return oss.str();
            }

            inline void rethrow(const unsigned code, struct ::_EXCEPTION_POINTERS* ep)
            {
                str_t info;
                try
                {
                    info = seh::information(*ep, code);
                }
                catch(const ::std::exception& e)
                {
                    info = "seh(critical): ";
                    info += e.what();
                }
                catch(...)
                {
                    info = "seh(critical): unknown";
                }

                #ifdef dHAS_RVALUE_REFERENCES
                    throw tools::seh::exception(::std::move(info));
                #else
                    throw tools::seh::exception(info);
                #endif
            }

        } // namespace 
    } // namespace seh
} // namespace tools

#endif // !_WIN32

//==============================================================================
//==============================================================================

