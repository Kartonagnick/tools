// [2020y-09-25d][20:13:18] Idrisov Denis R.
// [2020y-12-01d][14:06:17] Idrisov Denis R.
// [2021y-02-20d][18:40:18] Idrisov Denis R.
// [2021y-03-10d][05:33:36] Idrisov Denis R.
// [2021y-03-11d][22:15:01] Idrisov Denis R.
// [2021y-03-12d][20:27:51] Idrisov Denis R.
// [2021y-03-13d][21:34:16] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_CAST_NUMERIC_USED_ 
#define dTOOLS_CAST_NUMERIC_USED_ 3 PRE

#include <tools/features.hpp>
#include <tools/types/fixed.hpp>
#include <tools/types/traits.hpp>

#ifdef dHAS_TYPE_TRAITS
    #include <type_traits>
#endif

//================================================================================
//=== [can_numeric_cast] =========================================================
namespace tools
{
    namespace numeric
    {
        namespace detail
        {
            #ifdef dHAS_TYPE_TRAITS
                namespace my = std;
            #else
                namespace my = ::tools;
            #endif

            template<class ret_type, class from_type>
            struct adapt
            {
                #ifdef dHAS_ENUM_CLASS
                    typedef typename
                    my::remove_cv<ret_type>::type
                        ret_t;

                    typedef typename
                    my::remove_cv<from_type>::type
                        from_t;

                    typedef typename
                    ::tools::type_of_enum<ret_t>::type
                        ret;

                    typedef typename
                    ::tools::type_of_enum<from_t>::type
                        from;
                #else
                    typedef typename
                    my::remove_cv<ret_type>::type
                        ret;

                    typedef typename
                    my::remove_cv<from_type>::type
                        from;
                #endif
            };

            template<class ret_type, class from_type>
            class help
            {
                typedef adapt<ret_type, from_type>
                    adaptor;
                typedef typename adaptor::ret
                    ret;
                typedef typename adaptor::from
                    from;

                enum { a = my::is_floating_point<from>::value };
                enum { b = my::is_floating_point<ret>::value  };
                enum { c = my::is_integral<from>::value       };
                enum { d = my::is_integral<ret>::value        };

                #ifdef dHAS_STATIC_ASSERT
                    static_assert(
                        (a && b) || (c && d),
                        "support only 'floating VS floating' "
                        "or 'integers VS integers'"
                    );
                #endif

                enum { floating   = my::is_floating_point<from>::value };
                enum { same_types = my::is_same<from, ret>::value };
                enum { capacious  = sizeof(ret) >= sizeof(from) };

                enum { ret_signed  = my::is_signed<ret >::value };
                enum { from_signed = my::is_signed<from>::value };

                enum { unsigned_grt_unsigned =  capacious && !ret_signed && !from_signed };
                enum { unsigned_lss_unsigned = !capacious && !ret_signed && !from_signed };

                enum { signed_grt_signed =  capacious && ret_signed && from_signed };
                enum { signed_lss_signed = !capacious && ret_signed && from_signed };

                enum { signed_grt_unsigned =  capacious && ret_signed && !from_signed };
                enum { signed_lss_unsigned = !capacious && ret_signed && !from_signed };

                enum { unsigned_grt_signed =  capacious && !ret_signed && from_signed };
                enum { unsigned_lss_signed = !capacious && !ret_signed && from_signed };

                enum { mode = 
                     floating              ?         0:
                     same_types            ?         1: 
                     unsigned_grt_unsigned ?         2:
                     unsigned_lss_unsigned ?         3: 
                     signed_grt_signed     ?         4:
                     signed_lss_signed     ?         5: 
                     signed_grt_unsigned   ?         6:
                     signed_lss_unsigned   ?         7: 
                     unsigned_grt_signed   ?         8:
                     unsigned_lss_signed   ?         9: 
                     10
                };

            public:
                ~help()
                {
                    dSTATIC_ASSERT(
                        (a && b) || (c && d),
                        SUPPORT_ONLY_FLOATING_WITH_FLOATING_OR_INTEGER_WITH_INTEGER
                    );
                    dSTATIC_ASSERT(mode >= 0, ERROR_INTERNAL);
                    dSTATIC_ASSERT(mode < 10, ERROR_INTERNAL);
                }

                help(); 

                enum { value = mode };
            };

            template<class r, class t>
            dCONSTEXPR_CPP11 r max_value() dNOEXCEPT
            {
                return static_cast<r>(::tools::limit<t>::max_value);
            }

            template<class r,class t>
            dCONSTEXPR_CPP11 r min_value() dNOEXCEPT
            {
                return static_cast<r>(::tools::limit<t>::min_value);
            }

            template<unsigned> struct agent;

            // --- floating
            template<> struct agent<0>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from) dNOEXCEPT
                    { return sizeof(ret) >= sizeof(from); }
            };

            // --- same
            template<> struct agent<1>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from) dNOEXCEPT
                    { return true; }
            };

            // --- from(small-unsigned) -> big-unsigned
            template<> struct agent<2>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from) dNOEXCEPT
                    { return true; }
            };

            // --- from(big-unsigned) -> small-unsigned
            template<> struct agent<3>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from v) dNOEXCEPT
                {
                    return max_value<from,ret>() >= v;
                }
            };

            // from(small-signed) to big-signed
            template<> struct agent<4>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from) dNOEXCEPT
                    { return true; }
            };

            // from(big-signed) to small-signed
            template<> struct agent<5>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from v) dNOEXCEPT
                {
                    return
                        max_value<from, ret>() >= v &&
                        min_value<from, ret>() <  v ;
                }
            };

            template<bool> struct unsigned_signed
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11 
                bool can(const from) dNOEXCEPT { return  true; }
            };

            template<> struct unsigned_signed<false>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11 
                bool can(const from v) dNOEXCEPT 
                {
                    return max_value<from,ret>() >= v;
                }
            };

            // --- from(small-unsigned) to big-signed
            template<> struct agent<6>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11 
                bool can(const from v) dNOEXCEPT
                {
                    typedef unsigned_signed< (sizeof(ret) > sizeof(from)) >
                        impl;
                    return impl::template can<ret, from>(v);
                    //return  ((void)v,  sizeof(ret) > sizeof(from) || max_value<from,ret>() >= v);
                }
            };

            // --- from(big-unsigned) to small-signed
            template<> struct agent<7>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11 
                bool can(const from v) dNOEXCEPT
                {
                    return max_value<from,ret>() >= v;
                }
            };

            // from(small-signed) to big-unsigned
            template<> struct agent<8>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from v) dNOEXCEPT
                    { return v >= 0; }
            };

            // from(big-signed) to small-unsigned
            template<> struct agent<9>
            {
                template<class ret, class from>
                static dCONSTEXPR_CPP11
                bool can(const from v) dNOEXCEPT
                {
                    return v < 0 ? false:
                        max_value<from,ret>() >= v;
                }
            };

        } // namespace detail

        template<class ret, class from>
        dCONSTEXPR_CPP11 dNODISCARD 
        bool can_cast(const from v) dNOEXCEPT
        {
            namespace x = ::tools::numeric::detail;
            typedef x::adapt<ret, from>
                adaptor;
            typedef typename adaptor::ret
                ret_t;
            typedef typename adaptor::from
                from_t;
            typedef x::help<ret_t, from_t>
                help;
            typedef x::agent<help::value> 
                agent;
            return agent::template can<ret_t, from_t>(
                static_cast<from_t>(v)
            );
        }

    } // namespace numeric

} // namespace tools

//================================================================================
//=== [cast/assert_cast] =========================================================

#include <tools/assert.hpp>
#include <typeinfo>
#include <sstream>
#include <cassert>
#include <string>

namespace tools
{
    typedef ::std::string
        str_t;

    namespace numeric
    {
        namespace detail
        {
            template<class ret, class from>
            ret throw_error(const from val)
            {
                #ifdef dHAS_ENUM_CLASS
                    typedef typename 
                    ::tools::type_of_enum<from>::type 
                        from_;

                    const from_ v = static_cast<from_>(val);
                #else
                    const from& v = val;
                #endif

                const str_t t = typeid(ret).name();
                ::std::stringstream ss;
                ss << v;
                const str_t s = ss.str();
                throw ::std::out_of_range(
                    "tools::can_numeric_cast"
                    "<" + t + ">(" + s + "): failed"
                );
            }

        } // namespace detail_cast

        template<class ret, class from>
        dCONSTEXPR_CPP11 dNODISCARD 
        ret cast(const from val) 
        {
            namespace x = ::tools::numeric::detail;
            return ::tools::numeric::can_cast<ret, from>(val) ?
                static_cast<ret>(val):
                x::throw_error<ret>(val);
        }

        template<class ret, class from>
        dCONSTEXPR_CPP11 dNODISCARD 
        ret assert_cast(const from val) dNOEXCEPT
        {
            dASSERT(
                ::tools::numeric::can_cast<ret, from>(val)
            );
            return static_cast<ret>(val);
        }

        #ifdef dFORBID_SAFE_CAST
            template<class ret, class from>
            dCONSTEXPR_CPP11 dNODISCARD ret safe_cast(const from val) dNOEXCEPT
            {
                #ifdef dHAS_STATIC_ASSERT
                    static_assert(
                        detail::my::is_same<from, const from>::value,
                        "'safe_cast' is forbidden to use"
                    );
                #else
                    dSTATIC_ASSERT(false && ERROR_SAFE_CAST_FORBIDDEN);
                #endif
                return val;
            }

            template<class ret, class from>
            dCONSTEXPR_CPP11 dNODISCARD
            ret assert_safe_cast(const from val) dNOEXCEPT
            {
                #ifdef dHAS_STATIC_ASSERT
                    static_assert(
                        detail::my::is_same<from, const from>::value,
                        "'assert_safe_cast' is forbidden to use"
                    );
                #else
                    dSTATIC_ASSERT(false && ERROR_ASSERT_SAFE_CAST_FORBIDDEN);
                #endif
                return val;
            }

        #else

        template<class ret, class from>
        dCONSTEXPR_CPP11 dNODISCARD
        ret safe_cast(const from val)
        {
            #ifndef dDISABLE_SAFE_CAST
                return ::tools::numeric::cast<ret>(val);
            #else
                return val;
            #endif
        }

        template<class ret, class from>
        dCONSTEXPR_CPP11 dNODISCARD
        ret assert_safe_cast(const from val) dNOEXCEPT
        {
            #ifndef dDISABLE_SAFE_CAST
                return ::tools::numeric::assert_cast<ret>(val);
            #else
                return val;
            #endif
        }

        #endif // !dFORBID_SAFE_CAST

    } // namespace numeric

} // namespace tools 

//================================================================================
//================================================================================
#endif // !dTOOLS_CAST_NUMERIC_USED_
