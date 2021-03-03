
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2021y-02m-20d 18:40:18 february                   +
//+ changed: 2021y-02m-28d 18:04:23 february                   +
//+ tools/hash/accum.hpp                                       +
//+                                            Tools's library +
//+                         Copyright @ 2021, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_HASH_ACCUM_USED_
#define dTOOLS_HASH_ACCUM_USED_ 100

#include <cstddef>
#include <string>

#include <tools/features.hpp>
#include <tools/assert.hpp>

#if !defined(_MSC_VER) || _MSC_VER >= 1600
   // #pragma message("build for msvc2010 or newer)")
   #include <cstdint>
#endif

//==============================================================================
//=== detail ===================================================================
namespace tools
{
    namespace detail_hash
    {
        #if !defined(_MSC_VER) || _MSC_VER >= 1600
            // #pragma message("build for msvc2010 or newer)")
            typedef ::std::uint32_t u32;
        #else
            // #pragma message("build for msvc2008 or older)")
            typedef __int32 u32;
        #endif

        inline u32 shake(u32 hash) dNOEXCEPT
        {
            hash += (hash << 3 );
            hash ^= (hash >> 11);
            hash += (hash << 15);
            return hash;
        }

        // portion is one byte
        inline void add_byte(u32& hash, const u32 portion) dNOEXCEPT
        {
            hash += portion;
            hash += (hash << 10);
            hash ^= (hash >> 6 );
        }

        // for sequences
        inline void add_dump(u32& hash, const void* pd, const size_t size) dNOEXCEPT
        {
            dASSERT(pd);
            namespace x = ::tools::detail_hash;
            typedef const unsigned char*
                ptr_t;
            const unsigned char* p = static_cast<ptr_t>(pd);
            for (size_t i = 0; i < size; ++i, ++p) 
                x::add_byte(hash, static_cast<u32>(*p));
        }

        inline void add_str(u32& hash, const char* str) dNOEXCEPT
        {
            dASSERT(str);
            namespace x = ::tools::detail_hash;
            for(const char* p = str; *p != 0; ++p)
                x::add_byte(hash, static_cast<u32>(*p));

            // add trailing zero to prevent concatenation
            x::add_byte(hash, 0); 
        }

        inline void add_str(u32& hash, const wchar_t* wcs) dNOEXCEPT
        {
            dASSERT(wcs);
            namespace x = ::tools::detail_hash;
            for(const wchar_t* p = wcs; *p != 0; ++p)
            {
                const u32 tmp = static_cast<u32>(*p);
                x::add_byte(hash, tmp & 0xFF);
                x::add_byte(hash, tmp >> 8  );
            }

            // trailing zero
            x::add_byte(hash, 0); 
        }

    } // namespace detail

} // namespace tools

//==============================================================================
//=== hash_accum ===============================================================
namespace tools
{
    typedef ::std::string  str_t;
    typedef ::std::wstring str_w;

    class hash_accum
    {
        #define dHASH_SEED 0xDEADBEEF
    public:
        typedef detail_hash::u32 u32;

        hash_accum() dNOEXCEPT 
            : m_hash(dHASH_SEED) 
        {}

        u32 get() const dNOEXCEPT
        {
            namespace x = ::tools::detail_hash;
            return x::shake(this->m_hash);
        }

        operator u32() const dNOEXCEPT
        {
            return this->get();
        }

    public:
        void add(const void* pd, const ::std::size_t size) dNOEXCEPT
        {
            namespace x = ::tools::detail_hash;
            x::add_dump(this->m_hash, pd, size);
        }

        // POD only
        template<class t> void add(const t& v) dNOEXCEPT 
        {
            namespace x = ::tools::detail_hash;
            x::add_dump(this->m_hash, &v, sizeof(v));
        }

        void add(const str_t& str) dNOEXCEPT
        {
            namespace x = ::tools::detail_hash;
            x::add_str(this->m_hash, str.c_str());
        }

        void add(const str_w& str) dNOEXCEPT
        {
            namespace x = ::tools::detail_hash;
            x::add_str(this->m_hash, str.c_str());
        }

    public:
        #define dVOID template<class s> void 
        dVOID add(s*& p)                dNOEXCEPT { this->add_pointer(p); }
        dVOID add(s* const& p)          dNOEXCEPT { this->add_pointer(p); }
        dVOID add(s* volatile& p)       dNOEXCEPT { this->add_pointer(p); }
        dVOID add(s* volatile const& p) dNOEXCEPT { this->add_pointer(p); }

        template<class ch, size_t n> 
        void add(const ch(&text)[n]) dNOEXCEPT
            { this->add_pointer(text); }

    private:
        dVOID add_pointer(const s* text) dNOEXCEPT
        {
            dASSERT(text);
            namespace x = ::tools::detail_hash;
            x::add_str(this->m_hash, text);
        }

    private:
        u32 m_hash;
    };
    #undef dVOID

} // namespace tools

#endif // !dTOOLS_HASH_ACCUM_USED_

