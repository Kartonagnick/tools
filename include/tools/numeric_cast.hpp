// [2020y-09-25d][20:13:18] Idrisov Denis R.
// [2020y-12-01d][14:06:17] Idrisov Denis R.
// [2021y-02-20d][18:40:18] Idrisov Denis R.
// [2021y-03-10d][05:33:36] Idrisov Denis R.
// [2021y-03-11d][22:15:01] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_NUMERIC_CAST_USED_ 
#define dTOOLS_NUMERIC_CAST_USED_ 1

#include <tools/features.hpp>
#include <tools/types/fixed.hpp>

#ifdef dHAS_TYPE_TRAITS
    #include <type_traits>
#endif
#include <tools/types/traits.hpp>
//================================================================================
//=== [can_numeric_cast] =========================================================
namespace tools
{
    namespace detail_cast
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
                tools::type_of_enum<ret_t>::type
                    ret;

                typedef typename
                tools::type_of_enum<from_t>::type
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
            return static_cast<r>(tools::limit<t>::max_value);
        }

        template<class r,class t>
        dCONSTEXPR_CPP11 r min_value() dNOEXCEPT
        {
            return static_cast<r>(tools::limit<t>::min_value);
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

        // --- from(small-unsigned) to big-signed
        template<> struct agent<6>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 
            bool can(const from v) dNOEXCEPT
            {
                return  ((void)v,  sizeof(ret) > sizeof(from) || max_value<from,ret>() >= v);
                //return max_value<from,ret>() >= v;
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

    } // namespace detail_cast

    template<class ret, class from>
    dCONSTEXPR_CPP11 dNODISCARD 
    bool can_numeric_cast(const from v) dNOEXCEPT
    {
        namespace x = ::tools::detail_cast;
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

} // namespace tools

//================================================================================
//================================================================================
#endif // !dTOOLS_NUMERIC_CAST_USED_
