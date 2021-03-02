// [2019-04-29][18:40:18] Idrisov Denis R.
//==============================================================================
//==============================================================================

#pragma once

#ifndef dTOOLS_ERRORNO_USED_ 
#define dTOOLS_ERRORNO_USED_ 100

#include <cerrno>
#include <string>

namespace tools
{
    typedef ::std::string 
        str_t;

    str_t get_errno(const int error_id = errno);

    str_t get_last_error();
    str_t get_last_error(const int code);

    str_t get_last_error(const char*  from_description);
    str_t get_last_error(const str_t& from_description);

    void throw_error(const char*  from_description);
    void throw_error(const str_t& from_description);
}

#endif //! dTOOLS_ERRORNO_USED_