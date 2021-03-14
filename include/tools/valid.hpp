// [2021y-02m-05d][21:27:17] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_VALID_USED_
#define dTOOLS_VALID_USED_ 1
#include <tools/features.hpp>
//==============================================================================
//==============================================================================
namespace tools
{
    #define dATTRIBUTES \
        dNODISCARD dCONSTEXPR_CPP11

    #define dTEMPLATE \
        template<class t> dATTRIBUTES

    namespace detail
    {
        dTEMPLATE bool valid(t*& p)                dNOEXCEPT { return p != 0; }
        dTEMPLATE bool valid(t* const& p)          dNOEXCEPT { return p != 0; }
        dTEMPLATE bool valid(t* volatile& p)       dNOEXCEPT { return p != 0; }
        dTEMPLATE bool valid(t* volatile const& p) dNOEXCEPT { return p != 0; }

        dTEMPLATE bool valid(t&) dNOEXCEPT 
            { return true; }

        #ifdef dHAS_CPP11

        dATTRIBUTES bool valid(nullptr_t&) dNOEXCEPT 
            { return false; }

        dATTRIBUTES bool valid(const nullptr_t&) dNOEXCEPT 
            { return false; }

        #endif // !dHAS_CPP11

    } // namespace detail

    #ifdef dHAS_RVALUE_REFERENCES

        dTEMPLATE bool valid(t&& p) dNOEXCEPT 
        {
            return ::tools::detail::valid(p);
        }

    #else

        dTEMPLATE bool valid(const t& p) dNOEXCEPT 
        { 
            return ::tools::detail::valid(p);
        }

    #endif // !dHAS_RVALUE_REFERENCES

    #undef dATTRIBUTES
    #undef dTEMPLATE

} // namespace tools 
//==============================================================================
//==============================================================================
#endif // !dTOOLS_VALID_USED_

