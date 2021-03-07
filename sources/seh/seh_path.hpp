// [2019y-01m-24d][19:22:08] Idrisov Denis R
// [2021y-03m-07d][09:29:49] Idrisov Denis R
#pragma once

#include <tools/features.hpp>
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

//==============================================================================
//=== [inline section] =========================================================
namespace tools
{
    typedef ::std::string 
        str_t;

    namespace seh
    {
        namespace
        {
            template<class container, class iter>
            inline void insert(container& collection, const iter& cur, const iter& lst)
            {
                const size_t length
                    = static_cast<size_t>(cur - lst);

                #ifdef dHAS_RVALUE_REFERENCES
                    collection.emplace_back(&(*lst), length);
                #else
                    collection.push_back(str_t(&(*lst), length));
                #endif
            }

            typedef ::std::vector<str_t>
                vec_t;

            inline vec_t tokenizePath(const str_t& path)
            {
                typedef str_t::const_iterator it;

                vec_t result;
                result.reserve(20);

                it lst_pos = path.begin();
                it cur_pos = lst_pos;
                const it end_string   = path.end();
                const char separators[3] = "\\/";

                for(;;)
                {
                    cur_pos = ::std::find_first_of(
                        lst_pos,
                        end_string,
                        separators,
                        separators + 2
                    );

                    if(cur_pos == end_string)
                    {
                        if(cur_pos != lst_pos)
                            insert(result, cur_pos, lst_pos);
                        break;
                    }
                    if(cur_pos != lst_pos)
                        insert(result, cur_pos, lst_pos);
                    lst_pos = cur_pos + 1;
                }
                return result;
            }

            inline str_t shortPath(const str_t& path)
            {
                if(path.size() < 81)
                    return path;

                const vec_t tokens = tokenizePath(path);

                const size_t count = tokens.size();

                if(count < 4)
                    return path;

                const str_t& last  = tokens[count-1];
                const str_t& llast = tokens[count-2];

                return tokens[0] + '/' + tokens[1] + "... " + llast + '/' + last;
            }

        } // namespace
    } // namespace seh
} // namespace tools

//==============================================================================
//==============================================================================

