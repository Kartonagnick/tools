// [2019y-01m-24d][19:22:08] Idrisov Denis R
// [2021y-03m-08d][19:22:08] Idrisov Denis R
//==============================================================================
//==============================================================================

#pragma once

#ifndef dTOOLS_SEH_USED_ 
#define dTOOLS_SEH_USED_ 1

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__MINGW__) || defined(__MINGW32__))
    // nothing...
#else
    #error Only Windows is supported
#endif

#include <tools/features.hpp>
#include <stdexcept>
//==============================================================================
//==============================================================================

#ifdef WIN32   // WINDOWS
    #define dFUNCTION_NAME_   __FUNCTION__  
#else          // *NIX
    #define dFUNCTION_NAME_   __func__ 
#endif

#define dBEGIN_SEH_EXCEPTION                                   \
    {                                                          \
        ::tools::seh::guard guard_thread;                      \
        try

#define dEND_SEH_EXCEPTION                                     \
        catch(const ::tools::seh::exception& e)                \
        {                                                      \
            output_seh_exception_(dFUNCTION_NAME_, e.what());  \
        }                                                      \
        catch(const ::std::exception& e)                       \
        {                                                      \
            output_std_exception_(dFUNCTION_NAME_, e.what());  \
        }                                                      \
        catch(...)                                             \
        {                                                      \
            output_unknown_exception_(dFUNCTION_NAME_);        \
        }                                                      \
    }void()

//==============================================================================
//==============================================================================

#ifdef _MSC_VER
    struct _EXCEPTION_POINTERS;
    typedef void (__cdecl *_se_translator_function)(unsigned int, struct _EXCEPTION_POINTERS*);
#endif

namespace tools
{
    namespace seh
    {
        class exception: public ::std::runtime_error 
        {                                            
            typedef ::std::runtime_error
                base;      
        public:
            #ifdef dHAS_CPP11
                using base::base;
            #else
                template<class t> exception(const t& reason)
                    : base(reason)
                {}
            #endif
        };

        class guard
        {
            #ifdef _MSC_VER
            typedef ::_se_translator_function
                agent_t;
            #else
            typedef void* agent_t;
            #endif
        public:
            dNOCOPYABLE(guard);
            guard() dNOEXCEPT;
           ~guard();
        private:
            agent_t m_agent;
        };

    } // namespace seh 

} // namespace tools 

//==============================================================================
//==============================================================================

#endif // !dTOOLS_SEH_USED_
