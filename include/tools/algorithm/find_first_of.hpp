// [2021y-02m-20d][18:40:18] Idrisov Denis R.
// [2021y-03m-14d][21:06:56] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_FIND_FIRST_OF_USED_
#define dTOOLS_FIND_FIRST_OF_USED_ 1

#include <tools/features.hpp>
#include <tools/assert.hpp>
#ifndef NDEBUG
    #include <tools/valid.hpp>
#endif // !NDEBUG

//==============================================================================
//==============================================================================
#ifdef dHAS_NOEXCEPT
    #define dNOEXCEPT_COMPARE_  noexcept ( noexcept(*b1 == *b2) )
    #define dNOEXCEPT_PREDICAT_ noexcept ( noexcept(pred(*b1, *b2)) )
#else
    #define dNOEXCEPT_COMPARE_
    #define dNOEXCEPT_PREDICAT_
#endif

namespace tools
{
    namespace alg_detail
    {
        template<class t> struct adopt
            { typedef t type; };

        template<class t, size_t n> struct adopt<t[n]>
            { typedef const t* type; };

        template<class t, size_t n> struct adopt<t(&)[n]>
            { typedef const t* type; };

    } // namespace alg_detail

    #define dADOPT_(it) \
        typename ::tools::alg_detail::adopt<it>::type 

    template <class it1, class it2, class it3, class it4>
    dNODISCARD dADOPT_(it2) find_first_of(
        const it1& b1, const it2& e1, 
        const it3& b2, const it4& e2) dNOEXCEPT_COMPARE_
    {
        namespace u = ::tools;
        dASSERT(u::valid(b1));
        dASSERT(u::valid(e1));
        dASSERT(u::valid(b2));
        dASSERT(u::valid(e2));

        typedef dADOPT_(it1) it_1;
        typedef dADOPT_(it3) it_3;

        for (it_1 i = b1; i != e1; ++i) 
        {
            for (it_3 x = b2; x != e2; ++x)
                if(*i == *x) 
                    return i;
        }
        return e1;
    }

    template <class it1, class it2, class it3, class it4, class predicat>
    dNODISCARD dADOPT_(it2) find_first_of(
        const it1& b1, const it2& e1, 
        const it3& b2, const it4& e2,
        const predicat& pred) dNOEXCEPT_PREDICAT_
    {
        namespace u = ::tools;
        dASSERT(u::valid(b1));
        dASSERT(u::valid(e1));
        dASSERT(u::valid(b2));
        dASSERT(u::valid(e2));

        typedef dADOPT_(it1) it_1;
        typedef dADOPT_(it3) it_3;

        for (it_1 i = b1; i != e1; ++i) 
        {
            for (it_3 x = b2; x != e2; ++x)
                if(pred(*i, *x)) 
                    return i;
        }
        return e1;
    }

    #undef dNOEXCEPT_PREDICAT_
    #undef dNOEXCEPT_COMPARE_

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_FIND_FIRST_OF_USED_