
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-20d 19:25:38 february                   +
//+ tools/hash/hash.hpp                                        +
//+                                            Tools's library +
//+                         Copyright @ 2021, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_HASH_HASH_USED_
#define dTOOLS_HASH_HASH_USED_ 100

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
    typedef const ::std::size_t seed_t;

    template <typename...> class hash;

    template<typename T> class hash_common
    {
        #define dHASH_SEED 0xDEADBEEF
        using calc = ::std::hash<T>;
        ::std::size_t m_seed;
    public:
        hash_common(seed_t seed = dHASH_SEED) dNOEXCEPT
            : m_seed(seed)
        {}
        ::std::size_t operator()(const T& v) dNOEXCEPT
        {
            seed_t s = this->m_seed;
            seed_t point = 0x9e3779b9 + (s << 6) + (s >> 2);
            return (s ^ calc()(v)) + point;
        }
    };

    template<typename T> class hash<T>
        : public hash_common<T>
    {
        using base = hash_common<T>;
    public:
        hash(seed_t seed = dHASH_SEED) dNOEXCEPT
            : base(seed)
        {}
    };

    template<> class hash<::std::string>
        : public hash_common<::std::string>
    {
        using base = hash_common<::std::string>;
    public:
        hash(seed_t seed = dHASH_SEED) dNOEXCEPT
            : base(seed)
        {}
    };

    #define dHASH_TEXT_ARRAY(from, type)         \
    template<size_t n> class hash<type>          \
        : public hash_common<from>               \
    {                                            \
        using base = hash_common<from>;          \
    public:                                      \
        hash(seed_t seed = dHASH_SEED) dNOEXCEPT \
            : base(seed)                         \
        {}                                       \
    }

    dHASH_TEXT_ARRAY(std::string, char[n]);
    dHASH_TEXT_ARRAY(std::string, const char[n]);

    dHASH_TEXT_ARRAY(std::wstring, wchar_t[n]);
    dHASH_TEXT_ARRAY(std::wstring, const wchar_t[n]);


    #define dHASH_TEXT(from, type)               \
    template<> class hash<type>                  \
        : public hash_common<from>               \
    {                                            \
        using base = hash_common<from>;          \
    public:                                      \
        hash(seed_t seed = dHASH_SEED) dNOEXCEPT \
            : base(seed)                         \
        {}                                       \
    }

    dHASH_TEXT(std::string, char*);
    dHASH_TEXT(std::string, char*const);
    dHASH_TEXT(std::string, char*volatile);
    dHASH_TEXT(std::string, char*volatile const);

    dHASH_TEXT(std::string, const char*);
    dHASH_TEXT(std::string, const char*const);
    dHASH_TEXT(std::string, const char*volatile);
    dHASH_TEXT(std::string, const char*volatile const);

    dHASH_TEXT(std::wstring, wchar_t*);
    dHASH_TEXT(std::wstring, wchar_t*const);
    dHASH_TEXT(std::wstring, wchar_t*volatile);
    dHASH_TEXT(std::wstring, wchar_t*volatile const);

    dHASH_TEXT(std::wstring, const wchar_t*);
    dHASH_TEXT(std::wstring, const wchar_t*const);
    dHASH_TEXT(std::wstring, const wchar_t*volatile);
    dHASH_TEXT(std::wstring, const wchar_t*volatile const);



    template <typename T, typename... Rest>
    class hash<T, Rest...>
    {
        ::std::size_t m_seed;
    public:
        hash(seed_t seed = dHASH_SEED) dNOEXCEPT
            : m_seed(seed)
        {}

        inline ::std::size_t 
        operator()(const T& v, const Rest&... rest) dNOEXCEPT
        {
            seed_t s = this->m_seed;
            seed_t seed = hash<T>(s)(v);
            return hash<Rest...>(seed)(rest...);
        }
    };

    template <typename T, typename... Rest>
    hash<T, Rest...>
        hash_maket(const T& v, const Rest&... rest);

    #define dMAKE_TOOLS_HASHABLE(type, ...)                       \
        namespace tools                                           \
        {                                                         \
            template<> class hash<type>                           \
            {                                                     \
                ::std::size_t m_seed;                             \
            public:                                               \
                hash(seed_t seed = dHASH_SEED) dNOEXCEPT          \
                    : m_seed(seed)                                \
                {}                                                \
                size_t operator()(const type& v) const dNOEXCEPT  \
                {                                                 \
                    using maket_t                                 \
                        = decltype(hash_maket(__VA_ARGS__));      \
                    seed_t s = this->m_seed;                      \
                    return maket_t(s)(__VA_ARGS__);               \
                }                                                 \
            };                                                    \
        } void dummy()

} // namespace tools

//==============================================================================
//==============================================================================
    #if 0
        // usage:
        #include <string>
        int main()
        {
            hash<int, float, double, std::string> hasher;
            const std::size_t h = hasher(1, 0.2f, 2.0, "Hello World!");
        }
    #endif
//==============================================================================
//==============================================================================
#endif // !dTOOLS_HASH_HASH_USED_

