// [2020y-09m-22d][14:06:17] Idrisov Denis R.
//================================================================================
//================================================================================

#if defined(__MINGW__) || defined(__MINGW32__)

#include <stdexcept>
#include <string>

typedef ::std::string
    str_t;

namespace tools
{
    str_t encrypt(const str_t& src, const str_t& access)
    {
        (void) src;
        (void) access;
        throw ::std::runtime_error(
            "tools::encrypt(): mingw not support"
        );
    }

    str_t decrypt(const str_t& src, const str_t& access)
    {
        (void) src;
        (void) access;
        throw ::std::runtime_error(
            "tools::encrypt(): mingw not support"
        );
    }

} // namespace tools

#endif // !defined(__MINGW__) || defined(__MINGW32__)
