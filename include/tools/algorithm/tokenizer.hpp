// [2019y-10m-24d][19:22:08] Idrisov Denis R.
// [2021y-02m-20d][18:40:18] Idrisov Denis R.
// [2021y-03m-15d][18:40:18] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_TOKENIZER_USED_
#define dTOOLS_TOKENIZER_USED_ 1

#include <tools/algorithm/find_first_of.hpp>

#ifndef NDEBUG
    #include <tools/assert.hpp>
    #include <tools/valid.hpp>
#endif // NDEBUG

#include <cstddef>

//================================================================================
//================================================================================

namespace tools
{
    template<class it1, class it2, class it3, class it4, 
        class callWord, class callPunct>
    void tokenize(
        const it1& beg_string    , 
        const it2& end_string    , 
        const it3& beg_separators, 
        const it4& end_separators, 
        callWord&  callbackWord  , 
        callPunct& callbackPunct ,
        const bool trim_empty = true)
    {
        namespace u = ::tools;
        dASSERT(u::valid(beg_string));
        dASSERT(u::valid(end_string));
        dASSERT(u::valid(beg_separators));
        dASSERT(u::valid(end_separators));

        #define dADOPT_(it) \
            typename ::tools::alg_detail::adopt<it>::type 

        dADOPT_(it1) lst_pos = beg_string;
        dADOPT_(it2) cur_pos = beg_string;

        for(;;)
        {
            cur_pos = u::find_first_of(
                lst_pos, end_string, 
                beg_separators, 
                end_separators
            );

            if(cur_pos == end_string)
            {
                if(cur_pos != lst_pos)
                    callbackWord(
                        &(*lst_pos), 
                        static_cast<size_t>(cur_pos - lst_pos)
                    );
                break;
            }
            else if(cur_pos != lst_pos || !trim_empty)
                callbackWord(
                    &(*lst_pos), 
                    static_cast<size_t>(cur_pos - lst_pos)
                ),
                callbackPunct(*cur_pos);
            else
                callbackPunct(*cur_pos);

            lst_pos = cur_pos + 1;
        }
        #undef dADOPT_
    }

} // namespace tools

//==============================================================================
//==============================================================================

#endif // !dTOOLS_TOKENIZER_USED_
