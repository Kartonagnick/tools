
// [2020y-09-25d][20:13:18] Idrisov Denis R.
// [2020y-12-01d][14:06:17] Idrisov Denis R.
// [2021y-02-20d][18:40:18] Idrisov Denis R.
// [2021y-03-10d][05:33:36] Idrisov Denis R.
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
//================================================================================
//================================================================================
//================================================================================
namespace tools
{
    namespace detail_cast
    {
        #ifdef dHAS_TYPE_TRAITS
            namespace my = std;
        #else
            namespace my = ::tools;
        #endif

        template<class a, class b, bool> struct select_big_
        {
            enum { v = sizeof(a) >= sizeof(b) };
            typedef my::conditional<v, a, b> x;
            typedef typename x::type type;
        };

        template<class a, class b> struct select_big_<a,b,false>
        {
            enum { v = tools::is_unsigned<a>::value };
            typedef my::conditional<v, a, b> x;
            typedef typename x::type type;
        };

        template<class a, class b> struct select_big
        {
            enum { v = sizeof(a) != sizeof(b) };
            typedef select_big_<a, b, v> x;
            typedef typename x::type type;
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


        template<class ret_type, class from_type>
        class help
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

            enum { same_types = my::is_same<from, ret>::value };
            enum { capacious = sizeof(ret) >= sizeof(from) };

            enum { floating = my::is_floating_point<from>::value };
            enum { ret_signed  = my::is_signed<ret >::value };
            enum { from_signed = my::is_signed<from>::value };

            enum { ret_unsigned  = !ret_signed  };
            enum { from_unsigned = !from_signed };
        
            enum { greater_uint =  capacious && ret_unsigned && from_unsigned };
            enum { less_uint    = !capacious && ret_unsigned && from_unsigned };

            enum { mode = 
                 floating     ?                  0:
                 same_types   ?                  1: 
                 greater_uint ?                  2:
                 less_uint    ?                  3: 
                 ret_signed   && from_unsigned ? 4: 
                 ret_unsigned && from_signed   ? 5: 
                 ret_signed   && from_signed   ? 6:
                                                 7 
            };
        public:
            ~help()
            {
                dSTATIC_ASSERT(
                    (a && b) || (c && d),
                    SUPPORT_ONLY_FLOATING_WITH_FLOATING_OR_INTEGER_WITH_INTEGER
                );
                dSTATIC_ASSERT(mode != 7, ERROR_INTERNAL);
            }

            help(); 

            enum { value = mode };
        };

        template<unsigned> struct agent;

        // --- floating
        template<> struct agent<0>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from) dNOEXCEPT
                { return sizeof(ret) >= sizeof(from); }
        };

        // --- same
        template<> struct agent<1>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from) dNOEXCEPT
                { return true; }
        };

        // --- small ---> big       (unsigned)
        template<> struct agent<2>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from) dNOEXCEPT
                { return true; }
        };

        // --- big ---> small       (unsigned)
        template<> struct agent<3>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT
            {
                return max_value<from,ret>() >= v;
                //return static_cast<from>(limit<ret>::max_value) >= v;
            }
        };

        // --- from(unsigned) to signed
        template<> struct agent<4>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT
            {
                typedef select_big<ret, from> x;
                typedef typename x::type big;
                return max_value<big,ret>() >= static_cast<big>(v);
                //return static_cast<big>(limit<ret>::max_value) >= static_cast<big>(v);
            }
        };

        // --- from(signed) to unsigned
        template<> struct agent<5>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT
            {
                typedef select_big<ret, from> x;
                typedef typename x::type big;

                return v < 0 ? false:
                    //max_value<big,ret>() >= static_cast<big>(v);
                    static_cast<big>(limit<ret>::max_value) >= static_cast<big>(v);
            }
        };

        // from(signed) to signed
        template<> struct agent<6>
        {
            template<class ret, class from>
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT
            {
                typedef select_big<ret, from> x;
                typedef typename x::type big;

                return
                    max_value<big,ret>() >= static_cast<big>(v) &&
                    min_value<big,ret>() <  static_cast<big>(v) ;
                    //static_cast<big>(limit<ret>::max_value) >= static_cast<big>(v) &&
                    //static_cast<big>(limit<ret>::min_value) < static_cast<big>(v);
            }
        };

    } // namespace detail_cast

    template<class ret, class from>
    dCONSTEXPR_CPP11 dNODISCARD 
    bool can_numeric_cast(const from v) dNOEXCEPT
    {
        namespace x = ::tools::detail_cast;

        #ifdef dHAS_ENUM_CLASS
            typedef typename remove_cv<ret>::type 
                ret_ty;
            typedef typename remove_cv<from>::type 
                from_ty;

            typedef typename 
            tools::type_of_enum<ret_ty>::type
                ret_t;

            typedef typename 
            tools::type_of_enum<from_ty>::type
                from_t;
        #else
            typedef typename remove_cv<ret>::type 
                ret_t;
            typedef typename remove_cv<from>::type 
                from_t;
        #endif

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
