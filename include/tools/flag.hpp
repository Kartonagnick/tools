
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-10m-24d 19:22:08 october                    +
//+ changed: 2021y-02m-26d 05:39:00 february                   +
//+ flag.hpp                                                   +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_FLAG_USED_ 
#define dTOOLS_FLAG_USED_ 100

//==============================================================================
//=== dNOEXCEPT ================================================================

#if defined(__clang__)
    #if __has_feature(cxx_dNOEXCEPT)
        #define dHAS_NOEXCEPT 1
    #endif
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46
    #define dHAS_NOEXCEPT 1
#endif

#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026
    // #pragma message("build for msvc2015 (or newer)")
    #define dHAS_NOEXCEPT 1
#endif
                
#ifdef dHAS_NOEXCEPT
    #define dNOEXCEPT noexcept
#else
    #define dNOEXCEPT throw()
#endif

//==============================================================================
//==============================================================================

namespace std
{
    template<class T> struct atomic;
}

//==============================================================================
//==============================================================================
namespace tools
{
    template<class enum_type> class flag
    {
    public:
        typedef enum_type enum_t;

        template<class intT>
        flag(const intT&   fl) dNOEXCEPT;
        flag(const enum_t& fl) dNOEXCEPT;
        flag(const flag&   fl) dNOEXCEPT;
        flag() dNOEXCEPT;

        // set new value
        template<class intT>
        flag& operator=(const intT&   fl) dNOEXCEPT;
        flag& operator=(const enum_t& fl) dNOEXCEPT;
        flag& operator=(const flag&   fl) dNOEXCEPT;

        //true, if m_flag == fl
        template<class intT>
        bool operator==(const intT&   fl) const dNOEXCEPT;
        bool operator==(const enum_t& fl) const dNOEXCEPT;
        bool operator==(const flag&   fl) const dNOEXCEPT;

        //bool operator!=(const enum_t fl) const dNOEXCEPT;
        template<class intT>
        bool operator!=(const intT&   fl) const dNOEXCEPT;
        bool operator!=(const enum_t& fl) const dNOEXCEPT;
        bool operator!=(const flag&   fl) const dNOEXCEPT;
    public:
        bool is_empty() const dNOEXCEPT;
        bool is_full()  const dNOEXCEPT;

        // true, if m_flags == 1 or all specified flags are enabled
        template<class intT>
        bool has(const intT&   fl) const dNOEXCEPT;
        bool has(const enum_t& fl) const dNOEXCEPT;
        bool has(const flag&   fl) const dNOEXCEPT;

        //true, if m_flags == 1 or if any of the specified flags is enabled
        template<class intT>
        bool has_any(const intT&   fl) const dNOEXCEPT;
        bool has_any(const enum_t& fl) const dNOEXCEPT;
        bool has_any(const flag&   fl) const dNOEXCEPT;
    public:
        void clear() dNOEXCEPT; 
        void full()  dNOEXCEPT; 

        template<class intT>
        void add(const intT&   fl) dNOEXCEPT; 
        void add(const enum_t& fl) dNOEXCEPT; 
        void add(const flag&   fl) dNOEXCEPT; 

        // remove specified flags
        template<class intT>
        void del(const intT&   fl) dNOEXCEPT; 
        void del(const enum_t& fl) dNOEXCEPT; 
        void del(const flag&   fl) dNOEXCEPT; 

        // turn off unspecified flags
        template<class intT>
        void valid_only(const intT&   fl) dNOEXCEPT; 
        void valid_only(const enum_t& fl) dNOEXCEPT;
        void valid_only(const flag&   fl) dNOEXCEPT; 

        // switch flag
        template<class Old, class New>
        void change(const Old& oldFlag, const New& newFlag) dNOEXCEPT;

        template<class intT>
        intT as() const dNOEXCEPT
        {
            return static_cast<intT>(this->m_flags);
        }

    private:
        template<class intT>
        void set_(const intT& fl) dNOEXCEPT;

        enum_type m_flags;
    };

} // namespace tools

//==============================================================================
//=== implementation ===========================================================
namespace tools
{
    #define dTEMPLATE \
        template<class enum_type>

    #define dCLASS \
       flag<enum_type>

    namespace detail_flag
    {
        template<class t> int from(const t& fl) dNOEXCEPT
        {
            const int he = static_cast<int>(fl);
            if ((he & 1) != 0)
                return 1;
            return he;
        }

        template<class from, class ret>
        void copy_from_to(const from& src, ret& dst) dNOEXCEPT
        {
            dst = static_cast<ret>(src);
        }

        template<class from, class t>
        void copy_from_to(const from& src, ::std::atomic<t>& dst) dNOEXCEPT
        {
            dst = static_cast<t>(src);
        }

    } // namespace detail_flag

    dTEMPLATE template<class intT>
    void dCLASS::set_(const intT& fl) dNOEXCEPT
    {
        namespace x = ::tools::detail_flag;
        x::copy_from_to(x::from(fl), this->m_flags);
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    dCLASS::flag(const intT& fl) dNOEXCEPT
        : m_flags()
    {
        this->set_(fl); 
    }

    dTEMPLATE dCLASS::flag(const enum_t& fl) dNOEXCEPT
        : m_flags()
    { this->set_(fl); }

    dTEMPLATE dCLASS::flag(const flag& fl) dNOEXCEPT
        : m_flags()
    {
        namespace x = ::tools::detail_flag;
        x::copy_from_to(fl.m_flags, this->m_flags);
    }

    dTEMPLATE dCLASS::flag() dNOEXCEPT
        : m_flags()
    {}

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE bool dCLASS::is_empty() const dNOEXCEPT 
    {
        return this->m_flags == enum_type();
    }

    dTEMPLATE bool dCLASS::is_full() const dNOEXCEPT
    {
        const int fl = static_cast<int>(this->m_flags);
        return fl == 1;
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    dCLASS& dCLASS::operator=(const intT& fl) dNOEXCEPT
    { 
        this->set_(fl);
        return *this;
    }

    dTEMPLATE dCLASS& dCLASS::operator=(const enum_t& fl) dNOEXCEPT
    {
        this->set_(fl);
        return *this;
    }

    dTEMPLATE dCLASS& dCLASS::operator=(const flag& fl) dNOEXCEPT
    { 
        namespace x = ::tools::detail_flag;
        x::copy_from_to(fl.m_flags, this->m_flags);
        return *this;
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::operator==(const intT& fl) const dNOEXCEPT
    {
        return this->operator==(flag(fl).m_flags);
    }

    dTEMPLATE bool dCLASS::operator==(const enum_t& fl) const dNOEXCEPT
    {
        return this->m_flags == flag(fl).m_flags;
    }

    dTEMPLATE bool dCLASS::operator==(const flag& fl) const dNOEXCEPT
    {
        return this->m_flags == fl.m_flags;
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::operator!=(const intT& fl) const dNOEXCEPT
        { return !this->operator==(fl); }

    dTEMPLATE bool dCLASS::operator!=(const enum_t& fl) const dNOEXCEPT
        { return !this->operator==(fl); }

    dTEMPLATE bool dCLASS::operator!=(const flag& fl) const dNOEXCEPT
        { return !this->operator==(fl); }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::has(const intT& fl) const dNOEXCEPT 
        { return this->has(flag(fl)); } 

    dTEMPLATE bool dCLASS::has(const enum_t& fl) const dNOEXCEPT
        { return this->has(flag(fl)); }

    dTEMPLATE bool dCLASS::has(const flag& fl) const dNOEXCEPT
    { 
        if (fl.is_empty())
            return this->is_empty();

        if (fl.is_full())
            return this->is_full();

        if (this->is_full())
            return fl.is_empty() ? false: true;

        const int he = static_cast<int>(fl.m_flags);
        const int my = static_cast<int>(this->m_flags);
        return (he & my) == he; 
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::has_any(const intT& fl) const dNOEXCEPT 
        { return this->has_any(flag(fl)); } 

    dTEMPLATE bool dCLASS::has_any(const enum_t& fl) const dNOEXCEPT 
        { return this->has_any(flag(fl)); } 

    dTEMPLATE bool dCLASS::has_any(const flag& fl) const dNOEXCEPT
    {
        if (fl.is_full())
            return !this->is_empty();

        if (fl.is_empty())
            return this->is_empty();

        if (this->is_full())
            return fl.is_empty() ? false: true;
       
        const int he = static_cast<int>(fl.m_flags);
        const int my = static_cast<int>(this->m_flags);
        return (he & my) != 0; 
    }

//==============================================================================
//=== implementation ===========================================================
            
    dTEMPLATE void dCLASS::clear() dNOEXCEPT 
    {
        namespace x = ::tools::detail_flag;
        x::copy_from_to(0, this->m_flags);
    } 

    dTEMPLATE void dCLASS::full() dNOEXCEPT 
    {
        namespace x = ::tools::detail_flag;
        x::copy_from_to(1, this->m_flags);
    } 

//==============================================================================
//=== implementation ===========================================================
    
    dTEMPLATE template<class intT>
    void dCLASS::add(const intT& fl) dNOEXCEPT 
        { this->add(flag(fl)); } 

    dTEMPLATE
    void dCLASS::add(const enum_t& fl) dNOEXCEPT 
        { this->add(flag(fl)); } 

    dTEMPLATE void dCLASS::add(const flag& fl) dNOEXCEPT 
    {
        if (fl.is_empty())
            return;

        if (this->is_full())
            return;

        if (fl.is_full())
            this->full();

        else
        {
            const int my = static_cast<int>(this->m_flags);
            const int he = static_cast<int>(fl.m_flags);
            namespace x = ::tools::detail_flag;
            x::copy_from_to(my | he, this->m_flags);
        }
    } 

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    void dCLASS::del(const intT& fl) dNOEXCEPT
        { this->del(flag(fl)); }

    dTEMPLATE
    void dCLASS::del(const enum_t& fl) dNOEXCEPT
        { this->del(flag(fl)); }

    dTEMPLATE void dCLASS::del(const flag& fl) dNOEXCEPT
    {
        if (this->is_empty())
            return;

        if (fl.is_full())
            this->clear();
        else
        {
            const int he = static_cast<int>(fl.m_flags);
            const int my = static_cast<int>(this->m_flags);
            namespace x = ::tools::detail_flag;
            x::copy_from_to(my & (~he), this->m_flags);
        }
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    void dCLASS::valid_only(const intT& fl) dNOEXCEPT 
        { this->valid_only(flag(fl)); } 

    dTEMPLATE
    void dCLASS::valid_only(const enum_t& fl) dNOEXCEPT 
        { this->valid_only(flag(fl)); } 

    dTEMPLATE void dCLASS::valid_only(const flag& fl) dNOEXCEPT
    {
        if(this->is_empty())
            return;

        if(fl.is_full())
            return;

        namespace x = ::tools::detail_flag;
        if(this->is_full())
            x::copy_from_to(fl.m_flags, this->m_flags);
        else
        {
            const int he = static_cast<int>(fl.m_flags);
            const int my = static_cast<int>(this->m_flags);
            x::copy_from_to(my & he, this->m_flags);
        }
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class Old, class New>
    void dCLASS::change(const Old& oldFlag, const New& newFlag) dNOEXCEPT
    {
        namespace x = ::tools::detail_flag;
        if(static_cast<int>(newFlag) == 0)
            this->clear();
        else
        {
            if (newFlag == 1)
                x::copy_from_to(1, this->m_flags);
            else if (newFlag == 0)
                x::copy_from_to(0, this->m_flags);
            else if (oldFlag == 1)
                this->set_(newFlag);
            else
            {
                const int cur_ = static_cast<int>(this->m_flags);
                const int old_ = static_cast<int>(oldFlag);
                const int new_ = static_cast<int>(newFlag);
                const int del_ = cur_ & (~old_);
                x::copy_from_to(del_ | new_, this->m_flags);
            }
        }
    }

    #undef dTEMPLATE
    #undef dCLASS

}//namespace tools

//==============================================================================
//=== usage ====================================================================
#if 0
    enum eFLAGS { eNONE = 0, eONE = 1<<1, eTWO = 1<<2, eTHREE = 1<<3 };
    using flag_t = tools::flag<eFLAGS> ;
    
    flag_t f(eONE|eTWO);
    EXPECT_EQ(eONE|eTWO,    f.getByEnumeration()    );
    EXPECT_EQ(false,        f.empty()               );
    EXPECT_EQ(true,        (f)? true: false         );
    EXPECT_EQ(true,         f.has(eONE)             );
    EXPECT_EQ(true,         f.has(eONE|eTWO)        );
    EXPECT_EQ(false,        f.has(eONE|eTWO|eTHREE) );
    EXPECT_EQ(true,         f.hasAny(eONE|eTWO)     );
    EXPECT_EQ(true,         f.hasAny(eTWO|eTHREE)   );
    EXPECT_EQ(false,        f.hasonly(eONE)         );
    EXPECT_EQ(true,         f.hasonly(eONE|eTWO)    );
    
    f.validOnly(eONE);
               
    EXPECT_EQ(eONE,   f.getByEnumeration()  );
    EXPECT_EQ(false,  f.empty()             );
    EXPECT_EQ(true,  (f)? true: false       );
    EXPECT_EQ(true,   f.has(eONE)           );
    EXPECT_EQ(false,  f.has(eONE|eTWO)      );
    EXPECT_EQ(true,   f.hasAny(eONE|eTWO)   );
    EXPECT_EQ(false,  f.hasAny(eTWO|eTHREE) );
    EXPECT_EQ(true,   f.hasonly(eONE)       );
    EXPECT_EQ(false,  f.hasonly(eONE|eTWO)  );
#endif
//==============================================================================
//==============================================================================
    
#endif // !dTOOLS_FLAG_USED_
