
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

        template<class a, class b> struct select_big
        {
            enum { v = sizeof(a) >= sizeof(b) };
            typedef my::conditional<v, a, b> x;
            typedef typename x::type type;
        };


        template<class ret_type, class from_type>
        class help
        {
            typedef typename 
            my::remove_cv<ret_type>::type 
                ret_t;

            typedef typename 
            my::remove_cv<from_type>::type
                from_t;

            typedef tools::type_of_enum_t<ret_t>
                ret;

            typedef tools::type_of_enum_t<from_t>
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
                return static_cast<from>(limit<ret>::max_value) >= v;
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
                return static_cast<big>(limit<ret>::max_value) >= static_cast<big>(v);
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
                    static_cast<big>(limit<ret>::max_value) >= static_cast<big>(v) &&
                    static_cast<big>(limit<ret>::min_value) < static_cast<big>(v);
            }
        };

    } // namespace detail_cast

    template<class ret, class from>
    dCONSTEXPR_CPP11 dNODISCARD 
    bool can_numeric_cast(const from v) dNOEXCEPT
    {
        namespace x = ::tools::detail_cast;
        typedef typename remove_cv<ret>::type 
            ret_ty;
        typedef typename remove_cv<from>::type 
            from_ty;

        typedef tools::type_of_enum_t<ret_ty>
            ret_t;

        typedef tools::type_of_enum_t<from_ty>
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
#endif // !dTOOLS_NUMERIC_CAST_USED_

//================================================================================
//================================================================================
//================================================================================
//================================================================================
//================================================================================
//================================================================================


#if 0
// [2020y-09-25d][20:13:18] Idrisov Denis R.
// [2020y-12-01d][14:06:17] Idrisov Denis R.
// [2021y-02-20d][18:40:18] Idrisov Denis R.
// [2021y-03-10d][05:33:36] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_NUMERIC_CAST_USED_ 
#define dTOOLS_NUMERIC_CAST_USED_ 1

#include <tools/features.hpp>
#include <tools/types/fixed.hpp>
//================================================================================
//================================================================================
//================================================================================
//================================================================================
namespace tools
{
    namespace detail_cast
    {
        template<class ret, class from, bool sigret>
        struct positiv
        {
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT 
            {
                return v >= 0;
            }
        };

        template<class ret, class from>
        struct positiv<ret, from, true>
        {
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT 
            {
                typedef limit<ret> lim;
                return static_cast<ret>(lim::min_value) <= static_cast<ret>(v);
            }
        };

//.................................................................................
        template<class ret, class from, bool capacious>
            struct diff;

        template<class ret, class from, bool capacious>
        struct diff
        {
            // small -> big
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT 
            {
                typedef is_signed<ret> sig;
                //typedef positiv<ret, from, sig::value> p;
                //return p::can(v);
                typedef limit<ret> lim;
                return v >= 0 || (sig::value && static_cast<ret>(lim::min_value) <= static_cast<ret>(v));
            }
        };

        template<class ret, class from> struct diff<ret, from, false>
        {
            static dCONSTEXPR_CPP11 bool can(const from v) dNOEXCEPT 
            { 
                typedef limit<ret> lim;
                return static_cast<from>(lim::max_value) >= v &&
                    static_cast<from>(lim::min_value) <= v;
            }
        };
//.................................................................................
        template<class from> struct diff<float, from, false>
        {
            static dCONSTEXPR_CPP11 
            bool can(const from) dNOEXCEPT { return false; }
        };
        template<class from> struct diff<double, from, false>
        {
            static dCONSTEXPR_CPP11 
            bool can(const from) dNOEXCEPT { return false; }
        };
//.................................................................................
        template<class ret, class from> struct help
        {
            enum { capacious = sizeof(ret) >= sizeof(from) };
            typedef diff<ret, from, capacious> x;

            static dCONSTEXPR_CPP11 
            bool can(const from v) dNOEXCEPT { return x::can(v); }
        };

        template<class t> struct help<t, t>
        {
            static dCONSTEXPR_CPP11 
            bool can(const t) dNOEXCEPT { return true; }
        };

    } // namespace detail_cast

    template<class ret, class from>
    dCONSTEXPR_CPP11 dNODISCARD 
    bool can_numeric_cast(const from v) dNOEXCEPT
    {
        namespace x = ::tools::detail_cast;
        typedef typename remove_cv<ret>::type 
            ret_t;
        typedef typename remove_cv<from>::type 
            from_t;
        typedef x::help<ret_t, from_t> 
            agent;
        return agent::can(v);
    }

} // tools
#endif // !dTOOLS_NUMERIC_CAST_USED_
#endif

//================================================================================
//================================================================================
//================================================================================
//================================================================================
//================================================================================
//================================================================================

#if 0
// [2020y-09-25d][20:13:18] Idrisov Denis R.
// [2020y-12-01d][14:06:17] Idrisov Denis R.
// [2021y-02-20d][18:40:18] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_NUMERIC_CAST_USED_ 
#define dTOOLS_NUMERIC_CAST_USED_ 1

#include <tools/features.hpp>

//#include <type_traits>
//#include <stdexcept>
//#include <typeinfo>
//#include <cassert>
//#include <string>
//#include <limits>

//================================================================================
//================================================================================
#ifndef dTOOLS_ENUM_TYPE_USED_ 
#define dTOOLS_ENUM_TYPE_USED_ 1
namespace tools
{
    namespace detail
    {
        template<class t, bool = ::std::is_enum<t>::value >
        struct type_of_enum
        {
            using type = ::std::underlying_type_t<t>;
        };

        template<class t>
        struct type_of_enum<t, false>
        {
            using type = t;
        };

    } // namespace detail

    template<class t> 
    using type_of_enum_t
        = typename ::tools::detail::type_of_enum<t>::type;

} // tools
#endif // !dTOOLS_ENUM_TYPE_USED_

//================================================================================
//================================================================================
namespace tools
{
    using str_t = ::std::string;

    namespace detail_numeric_cast
    {
        #define dDETAIL \
            ::tools::detail_numeric_cast

        template<class ret, class from> ret throw_error(const from val)
        {
            using from_ = ::tools::type_of_enum_t<from>;
            const from_ v = static_cast<from_>(val);
            const str_t t = typeid(ret).name();
            const str_t s = ::std::to_string(v);
            throw ::std::out_of_range(
                "tools::can_numeric_cast<" + t + ">(" + s + "): failed"
            );
        }

        template<class from, class to, class t>
        dCONSTEXPR_CPP11 from cast(const t value) dNOEXCEPT
        {
            using from_ = ::tools::type_of_enum_t<from>;
            using to_   = ::tools::type_of_enum_t<to>;

            using x = ::std::common_type_t<from_, to_>;
            return static_cast<x>(value);
        }

        #define dMIN_LIMIT(to)                     \
            dDETAIL::cast<from, to>(               \
                (::std::numeric_limits<to>::min)() \
            )

        #define dMAX_LIMIT(to)                     \
            dDETAIL::cast<from, to>(               \
                (::std::numeric_limits<to>::max)() \
            )

        #define dTHE_VALUE(val) \
            dDETAIL::cast<from, ret>(val)

        template<class ret_type, class from_type>
        class help
        {
            using origin_from 
                = std::remove_cv_t<from_type>;

            using origin_ret  
                = std::remove_cv_t<ret_type>;

            using from 
                = ::tools::type_of_enum_t<origin_from>;

            using ret  
                = ::tools::type_of_enum_t<origin_ret>;
        };

    } // namespace detail_numeric_cast

    #undef dTHE_VALUE
    #undef dMIN_LIMIT
    #undef dMAX_LIMIT
    #undef dDETAIL
    #undef dBOOL

} // namespace tools

//================================================================================
//================================================================================

namespace tools
{
    template<class ret, class from>
    dCONSTEXPR_CPP11 ret assert_numeric_cast(const from val) dNOEXCEPT
    {
        assert((tools::can_numeric_cast<ret, from>(val)));
        return static_cast<ret>(val);
    }

    template<class ret, class from>
    dCONSTEXPR_CPP11 ret numeric_cast(const from val) 
    {
        return tools::can_numeric_cast<ret, from>(val) ?
            static_cast<ret>(val):
            detail_numeric_cast::throw_error<ret>(val);
    }

} // namespace tools
//================================================================================

#endif // !dTOOLS_NUMERIC_CAST_USED_
#endif

