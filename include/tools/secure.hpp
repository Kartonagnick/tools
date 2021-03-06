// [2020y-09m-22d][14:06:17] Idrisov Denis R.
//==============================================================================
//==============================================================================

#pragma once
#ifndef dTOOLS_SECURE_USED_ 
#define dTOOLS_SECURE_USED_ 100

#include <string>

namespace tools
{
    typedef std::string
        str_t;

    // --- hide
    str_t encrypt(const str_t& src, const str_t& access);

    // --- show
    str_t decrypt(const str_t& src, const str_t& access);
    
} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_SECURE_USED_