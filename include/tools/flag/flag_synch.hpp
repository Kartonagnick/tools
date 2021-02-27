
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-10m-24d 19:22:08 october   Idrisov D. R     +
//+ changed: 2021y-02m-26d 05:39:00 february  Idrisov D. R     +
//+ changed: 2021y-02m-27d 02:20:05 february  Idrisov D. R     +
//+ tools/flag/flag_synch.hpp                                  +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once

#ifndef dTOOLS_FLAG_SYNCH_USED_ 
#define dTOOLS_FLAG_SYNCH_USED_ 101

#include <tools/flag.hpp>

//==============================================================================
//==============================================================================
namespace tools
{
    template<class Enum> class flag <Enum, synch>
    {
    public:
        typedef Enum enum_t;

        template<class intT>
        flag(const intT& fl) dNOEXCEPT;
        flag(const Enum& fl) dNOEXCEPT;
        flag(const flag& fl) dNOEXCEPT;
        flag() dNOEXCEPT;

        // set new value
        template<class intT>
        flag& operator=(const intT& fl) dNOEXCEPT;
        flag& operator=(const Enum& fl) dNOEXCEPT;
        flag& operator=(const flag& fl) dNOEXCEPT;

        //true, if m_flag == fl
        template<class intT>
        bool operator==(const intT& fl) const dNOEXCEPT;
        bool operator==(const Enum& fl) const dNOEXCEPT;
        bool operator==(const flag& fl) const dNOEXCEPT;

        //true, if m_flag != fl
        template<class intT>
        bool operator!=(const intT& fl) const dNOEXCEPT;
        bool operator!=(const Enum& fl) const dNOEXCEPT;
        bool operator!=(const flag& fl) const dNOEXCEPT;
    public:
        bool is_empty() const dNOEXCEPT;
        bool is_full()  const dNOEXCEPT;

        // true, if m_flags == 1 or all specified flags are enabled
        template<class intT>
        bool has(const intT& fl) const dNOEXCEPT;
        bool has(const Enum& fl) const dNOEXCEPT;
        bool has(const flag& fl) const dNOEXCEPT;

        //true, if m_flags == 1 or if any of the specified flags is enabled
        template<class intT>
        bool has_any(const intT& fl) const dNOEXCEPT;
        bool has_any(const Enum& fl) const dNOEXCEPT;
        bool has_any(const flag& fl) const dNOEXCEPT;
    public:
        void clear() dNOEXCEPT; 
        void full()  dNOEXCEPT; 

        template<class intT>
        void add(const intT& fl) dNOEXCEPT; 
        void add(const Enum& fl) dNOEXCEPT; 
        void add(const flag& fl) dNOEXCEPT; 

        // remove specified flags
        template<class intT>
        void del(const intT& fl) dNOEXCEPT; 
        void del(const Enum& fl) dNOEXCEPT; 
        void del(const flag& fl) dNOEXCEPT; 

        // turn off unspecified flags
        template<class intT>
        void valid_only(const intT& fl) dNOEXCEPT; 
        void valid_only(const Enum& fl) dNOEXCEPT;
        void valid_only(const flag& fl) dNOEXCEPT; 

        // switch flag
        template<class Old, class New>
        void change(const Old& oldFlag, const New& newFlag) dNOEXCEPT;

        template<class intT>
        intT as() const dNOEXCEPT
        {
            const synch_guard lock(this->m_synch);
            return static_cast<intT>(this->m_flags);
        }

    private:
        template<class intT>
        void set_(const intT& fl) dNOEXCEPT;

        bool is_empty_() const dNOEXCEPT;
        bool is_full_()  const dNOEXCEPT;
        void clear_() dNOEXCEPT; 
        void full_()  dNOEXCEPT; 

        mutable synch m_synch;
        Enum  m_flags;
    };

} // namespace tools

//==============================================================================
//=== implementation ===========================================================
namespace tools
{
    #define dTEMPLATE template<class Enum>
    #define dCLASS    flag<Enum, synch>

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
        : m_synch()
        , m_flags()
    {
        const synch_guard lock(this->m_synch);
        this->set_(fl); 
    }

    dTEMPLATE dCLASS::flag(const Enum& fl) dNOEXCEPT
        : m_synch()
        , m_flags()
    { 
        const synch_guard lock(this->m_synch);
        this->set_(fl);
    }

    dTEMPLATE dCLASS::flag(const flag& fl) dNOEXCEPT
        : m_synch()
        , m_flags()
    {
        const synch_guard lock1(this->m_synch);
        const synch_guard lock2(fl.m_synch);

        namespace x = ::tools::detail_flag;
        x::copy_from_to(fl.m_flags, this->m_flags);
    }

    dTEMPLATE dCLASS::flag() dNOEXCEPT
        : m_synch()
        , m_flags()
    {
        const synch_guard lock(this->m_synch);
        this->set_(0); 
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE bool dCLASS::is_empty_() const dNOEXCEPT 
    {
        const int fl = static_cast<int>(this->m_flags);
        return fl == 0;
    }

    dTEMPLATE bool dCLASS::is_full_() const dNOEXCEPT
    {
        const int fl = static_cast<int>(this->m_flags);
        return fl == 1;
    }

    dTEMPLATE bool dCLASS::is_empty() const dNOEXCEPT 
    {
        const synch_guard lock(this->m_synch);
        return this->is_empty_();
    }

    dTEMPLATE bool dCLASS::is_full() const dNOEXCEPT
    {
        const synch_guard lock(this->m_synch);
        return this->is_full_();
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    dCLASS& dCLASS::operator=(const intT& fl) dNOEXCEPT
    { 
        const synch_guard lock(this->m_synch);
        this->set_(fl);
        return *this;
    }

    dTEMPLATE dCLASS& dCLASS::operator=(const Enum& fl) dNOEXCEPT
    {
        const synch_guard lock(this->m_synch);
        this->set_(fl);
        return *this;
    }

    dTEMPLATE dCLASS& dCLASS::operator=(const flag& fl) dNOEXCEPT
    { 
        if(this == &fl)
            return *this;

        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);

        namespace x = ::tools::detail_flag;
        x::copy_from_to(fl.m_flags, this->m_flags);
        return *this;
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::operator==(const intT& fl) const dNOEXCEPT
    {
        return this->operator==(flag(fl));
    }

    dTEMPLATE bool dCLASS::operator==(const Enum& fl) const dNOEXCEPT
    {
        return this->operator==(flag(fl));
    }

    dTEMPLATE bool dCLASS::operator==(const flag& fl) const dNOEXCEPT
    {
        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);
        return this->m_flags == fl.m_flags;
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::operator!=(const intT& fl) const dNOEXCEPT
        { return !this->operator==(fl); }

    dTEMPLATE bool dCLASS::operator!=(const Enum& fl) const dNOEXCEPT
        { return !this->operator==(fl); }

    dTEMPLATE bool dCLASS::operator!=(const flag& fl) const dNOEXCEPT
        { return !this->operator==(fl); }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::has(const intT& fl) const dNOEXCEPT 
        { return this->has(flag(fl)); } 

    dTEMPLATE bool dCLASS::has(const Enum& fl) const dNOEXCEPT
        { return this->has(flag(fl)); }

    dTEMPLATE bool dCLASS::has(const flag& fl) const dNOEXCEPT
    { 
        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);

        if (fl.is_empty_())
            return this->is_empty_();

        if (fl.is_full_())
            return this->is_full_();

        if (this->is_full_())
            return fl.is_empty_() ? false: true;

        const int he = static_cast<int>(fl.m_flags);
        const int my = static_cast<int>(this->m_flags);
        return (he & my) == he; 
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE template<class intT>
    bool dCLASS::has_any(const intT& fl) const dNOEXCEPT 
        { return this->has_any(flag(fl)); } 

    dTEMPLATE bool dCLASS::has_any(const Enum& fl) const dNOEXCEPT 
        { return this->has_any(flag(fl)); } 

    dTEMPLATE bool dCLASS::has_any(const flag& fl) const dNOEXCEPT
    {
        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);

        if (fl.is_full_())
            return !this->is_empty_();

        if (fl.is_empty_())
            return this->is_empty_();

        if (this->is_full_())
            return fl.is_empty_() ? false: true;
       
        const int he = static_cast<int>(fl.m_flags);
        const int my = static_cast<int>(this->m_flags);
        return (he & my) != 0; 
    }

//==============================================================================
//=== implementation ===========================================================

    dTEMPLATE void dCLASS::clear_() dNOEXCEPT 
    {
        namespace x = ::tools::detail_flag;
        x::copy_from_to(0, this->m_flags);
    } 
    dTEMPLATE void dCLASS::full_() dNOEXCEPT 
    {
        namespace x = ::tools::detail_flag;
        x::copy_from_to(1, this->m_flags);
    } 


    dTEMPLATE void dCLASS::clear() dNOEXCEPT 
    {
        const synch_guard lock(this->m_synch);
        this->clear_();
    } 

    dTEMPLATE void dCLASS::full() dNOEXCEPT 
    {
        const synch_guard lock(this->m_synch);
        this->full_();
    } 

//==============================================================================
//=== implementation ===========================================================
    
    dTEMPLATE template<class intT>
    void dCLASS::add(const intT& fl) dNOEXCEPT 
        { this->add(flag(fl)); } 

    dTEMPLATE
    void dCLASS::add(const Enum& fl) dNOEXCEPT 
        { this->add(flag(fl)); } 

    dTEMPLATE void dCLASS::add(const flag& fl) dNOEXCEPT 
    {
        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);

        if (fl.is_empty_())
            return;

        if (this->is_full_())
            return;

        if (fl.is_full_())
            this->full_();

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
    void dCLASS::del(const Enum& fl) dNOEXCEPT
        { this->del(flag(fl)); }

    dTEMPLATE void dCLASS::del(const flag& fl) dNOEXCEPT
    {
        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);

        if (this->is_empty_())
            return;

        if (fl.is_full_())
            this->clear_();
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
    void dCLASS::valid_only(const Enum& fl) dNOEXCEPT 
        { this->valid_only(flag(fl)); } 

    dTEMPLATE void dCLASS::valid_only(const flag& fl) dNOEXCEPT
    {
        const synch_guard lock1(fl.m_synch);
        const synch_guard lock2(this->m_synch);

        if(this->is_empty_())
            return;

        if(fl.is_full_())
            return;

        namespace x = ::tools::detail_flag;
        if(this->is_full_())
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
    void dCLASS::change(const Old& oldFlags, const New& newFlags) dNOEXCEPT
    {
        const int oldFlag = static_cast<int>(oldFlags);
        const int newFlag = static_cast<int>(newFlags);

        if(newFlag == 0)
            this->clear();
        else
        {
            const synch_guard lock(this->m_synch);
            namespace x = ::tools::detail_flag;

            if (newFlag == 1)
                x::copy_from_to(1, this->m_flags);
            else if (newFlag == 0)
                x::copy_from_to(0, this->m_flags);
            else if (oldFlag == 1)
                this->set_(newFlag);
            else
            {
                const int cur = static_cast<int>(this->m_flags);
                const int del = cur & (~oldFlag);
                const int res = del | newFlag;
                x::copy_from_to(res, this->m_flags);
            }
        }
    }

    #undef dTEMPLATE
    #undef dCLASS

}//namespace tools

//==============================================================================
//==============================================================================
   
#endif // !dTOOLS_FLAG_SYNCH_USED_
