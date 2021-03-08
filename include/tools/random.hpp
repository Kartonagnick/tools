
// [2019y-10m-24d][19:22:08] Idrisov Denis R.
// [2021y-03m-04d][01:06:10] Idrisov Denis R.
// [2021y-03m-08d][22:55:41] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_RANDOM_USED_ 
#define dTOOLS_RANDOM_USED_ 101

#ifndef dHAS_CHRONO
    #error expected msvc2012 or newest
#endif

#include <tools/features.hpp>
#include <type_traits>
#include <exception>
#include <cassert>
#include <random>
#include <chrono>

#ifndef dHAS_THREAD_LOCAL
    #include <tools/synch.hpp>
#endif

//==============================================================================
//==============================================================================
namespace tools
{
    template<class T>
    T random(const T& a, const T& b) dNOEXCEPT;

}// namespace tools

//==============================================================================
//=== implementation ===========================================================
namespace tools
{
    namespace detail_random
    {
        #ifdef dHAS_THREAD_LOCAL
            #define dTHREAD_SAFE_ thread_local
        #else
            #define dTHREAD_SAFE_ 
        #endif

        inline ::std::default_random_engine& rnd_() dNOEXCEPT
        {
            typedef ::std::chrono::steady_clock
                clock_type;

            dTHREAD_SAFE_ static 
            ::std::default_random_engine engine(
                static_cast<unsigned>(
                    clock_type::now().time_since_epoch().count()
                )
            );
            return engine;
        }

        #define dFOR_INTEGER_                   \
            typename ::std::enable_if<          \
                ::std::is_integral<T>::value, T \
            >::type

        #define dFOR_FLOATING_                        \
            typename ::std::enable_if<                \
                ::std::is_floating_point<T>::value, T \
            >::type

        template<class T>
        inline dFOR_INTEGER_ random_(const T& a, const T& b) dNOEXCEPT
        {
            try
            {
                assert(a <= b);
                ::std::uniform_int_distribution<T> 
                    calculation(a, b);

                #ifndef dHAS_THREAD_LOCAL
                static ::tools::synch mut;
                ::tools::synch_lock<::tools::synch> 
                    lock(mut);
                #endif

                namespace detail = ::tools::detail_random;
                return calculation(detail::rnd_());
            }
            catch (const ::std::exception&)
            {
                dASSERT(false && "[0] tools::random_(std::exception)");
            }
            catch (...)
            {
                dASSERT(false && "[0] tools::random_(...)");
            }
            return (a + b) / 2;
        }

        template<class T>
        inline dFOR_FLOATING_ random_(const T& a, const T& b) dNOEXCEPT
        {
            try
            {
                assert(a <= b);
                ::std::uniform_real_distribution<T> 
                    calculation(a, b);

                #ifndef dHAS_THREAD_LOCAL
                static ::tools::synch mut;
                ::tools::synch_lock<::tools::synch> 
                    lock(mut);
                #endif

                namespace detail = ::tools::detail_random;
                return calculation(detail::rnd_());
            }
            catch (const ::std::exception&)
            {
                dASSERT(false && "[1] tools::random_(std::exception)");
            }
            catch (...)
            {
                dASSERT(false && "[1] tools::random_(...)");
            }
            return (a + b) / 2.0;
        }

        #undef dFOR_FLOATING_
        #undef dFOR_INTEGER_
        #undef dTHREAD_SAFE_

    } // namespace detail_random

    inline bool random(const bool a, const bool b) dNOEXCEPT
    {
        namespace detail = ::tools::detail_random;
        const int aa = static_cast<int>(a);
        const int bb = static_cast<int>(b);
        const int cc = detail::random_(aa, bb);
        return cc == 0? false: true;
    }

    inline char random(const char a, const char b) dNOEXCEPT
    {
        namespace detail = ::tools::detail_random;
        const int aa = static_cast<int>(a);
        const int bb = static_cast<int>(b);
        return static_cast<char>(detail::random_(aa, bb));
    }

    inline wchar_t random(const wchar_t a, const wchar_t b) dNOEXCEPT
    {
        namespace detail = ::tools::detail_random;
        const int aa = static_cast<int>(a);
        const int bb = static_cast<int>(b);
        const int cc = detail::random_(aa, bb);
        return static_cast<wchar_t>(cc);
    }

    template<class T> 
    T random(const T& a, const T& b) dNOEXCEPT
    {
        namespace detail = ::tools::detail_random;
        return detail::random_(a, b);
    }

    template<class T, size_t N> 
    const T& random(const T (&arr)[N]) dNOEXCEPT
    {
        const size_t nil = 0u;
        const size_t index = ::tools::random(nil, N - 1);
        return arr[index];
    }

} // namespace tools

//==============================================================================
//==============================================================================

#endif // !dTOOLS_RANDOM_USED_
