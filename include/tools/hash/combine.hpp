
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-20d 19:25:38 february                   +
//+ tools/hash/combine.hpp                                     +
//+                                            Tools's library +
//+                         Copyright @ 2021, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_HASH_COMBINED_USED_
#define dTOOLS_HASH_COMBINED_USED_ 100

#include <tools/features.hpp>

#ifndef dHAS_HASH
    #error std::hash requires c++0x, msvc2010 (or newer) 
#endif

#ifndef dHAS_VARIADIC_TEMPLATE
    #error requires c++11, msvc2013 (or newer) 
#endif

#include <cstddef>
#include <string>

//==============================================================================
//=== forward-std ==============================================================
namespace std
{
    template <class Key> struct hash;

} // namespace std

//==============================================================================
//=== declarations =============================================================
namespace tools
{
    template <class T, size_t N>
    ::std::size_t hash_combine(
        const ::std::size_t seed,
        const T(&arr)[N]
    ) dNOEXCEPT;

    template <class T>
    ::std::size_t hash_combine(
        const ::std::size_t seed,
        const T& v
    ) dNOEXCEPT;

    template <class T, class... Rest>
    ::std::size_t hash_combine(
        const ::std::size_t seed,
        const T& v,
        const Rest& ...rest
    ) dNOEXCEPT;

    template<class t>
    ::std::size_t hash_combine_text(
        const ::std::size_t seed,
        const t* text
    ) dNOEXCEPT;

} // namespace tools

//==============================================================================
//=== implementation ===========================================================
namespace tools
{
    typedef const ::std::size_t seed_t;

    template <class T, size_t N>
    ::std::size_t 
    hash_combine(seed_t seed, const T (&arr)[N]) dNOEXCEPT
    {
        const ::std::hash<T> h;
        ::std::size_t result = seed;
        for (const auto& el : arr)
        {
            seed_t point = 0x9e3779b9 + (result << 6) + (result >> 2);
            result = result ^ h(el) + point;
        }
        return result;
    }

    template <class T>
    ::std::size_t
    hash_combine(seed_t seed, const T& v) dNOEXCEPT
    {
        const ::std::hash<T> h;
        seed_t point = 0x9e3779b9 + (seed << 6) + (seed >> 2);
        const ::std::size_t result = (seed ^ h(v)) + point;
        return result;
    }

    template <class T, class... Rest>
    ::std::size_t 
    hash_combine(seed_t seed, const T& v, const Rest& ...rest) dNOEXCEPT
    {
        return ::tools::hash_combine(
            ::tools::hash_combine(seed, v),
            rest...
        );
    }

    template<class t>
    ::std::size_t 
    hash_combine_text(seed_t seed, const t* text) dNOEXCEPT
    {
        using str_type= ::std::basic_string<t>;
        return ::tools::hash_combine(
            seed, str_type(text)
        );
    }

    #define dhash_combine_pointer(type)                     \
        size_t hash_combine(seed_t seed, type& p) dNOEXCEPT \
            { return ::tools::hash_combine_text(seed, p); }

    #define dIMPLEMENTATIONS(type)                          \
        dhash_combine_pointer(const type*)                  \
        dhash_combine_pointer(const type* const)            \
        dhash_combine_pointer(const type* volatile)         \
        dhash_combine_pointer(const type* volatile const)   \
        dhash_combine_pointer(type*)                        \
        dhash_combine_pointer(type* const)                  \
        dhash_combine_pointer(type* volatile)               \
        dhash_combine_pointer(type* volatile const)         \

    dIMPLEMENTATIONS(char)
    dIMPLEMENTATIONS(wchar_t)

    #undef dhash_combine_pointer
    #undef dIMPLEMENTATIONS

    template <size_t N>
    ::std::size_t 
    hash_combine(seed_t seed, const char (&arr)[N]) dNOEXCEPT
    {
        return ::tools::hash_combine(
            seed, static_cast<const char*>(arr)
        );
    }

    template <size_t N>
    ::std::size_t 
    hash_combine(seed_t seed, const wchar_t (&arr)[N]) dNOEXCEPT
    {
        return ::tools::hash_combine(seed, static_cast<const wchar_t*>(arr));
    }

    #define dMAKE_HASHABLE(type, ...)                             \
        namespace std                                             \
        {                                                         \
            template<> struct hash<type>                          \
            {                                                     \
                size_t operator()(const type& v) const dNOEXCEPT  \
                {                                                 \
                    return ::tools::hash_combine(0, __VA_ARGS__); \
                }                                                 \
            };                                                    \
        } void dummy()

} // namespace tools

//==============================================================================
//==============================================================================
    #if 0
        // usage:
        struct SomeHashKey 
        {
            std::string key1;
            std::string key2;
            bool key3;
        };
        MAKE_HASHABLE(SomeHashKey, v.key1, v.key2, v.key3)
    #endif
//==============================================================================
//==============================================================================
#endif // !dTOOLS_HASH_COMBINED_USED_
