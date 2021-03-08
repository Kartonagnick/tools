// [2019y-10m-24d][19:22:08] Idrisov Denis R.
//==============================================================================
//==============================================================================
#pragma once
#ifndef dTOOLS_MARKER_USED_ 
#define dTOOLS_MARKER_USED_ 1

//=== includes =================================================================
#include <tools/features.hpp>
#include <tools/synch.hpp>

#ifdef dHAS_TYPE_TRAITS
    #include <unordered_map>
#else
    #include <map>
#endif
//==============================================================================

namespace tools 
{
    template<class Key, class Value>
    class marker
    {
        #ifdef dHAS_TYPE_TRAITS
            typedef ::std::unordered_multimap<Key, Value> 
                multimap;
        #else
            typedef ::std::multimap<Key, Value> 
                multimap;
        #endif

        typedef typename multimap::value_type
            pair;

        typedef typename multimap::const_iterator
            iter;

        typedef ::std::pair<iter, iter>
            range_t;

        typedef ::tools::synch_lock<::tools::synch>
            synch_lock;

        bool emplace(const Key& key, const Value& value);
    public:
        dNOCOPYABLE(marker);

        marker() dNOEXCEPT
            : m_mutex()
            , m_map()
        {}

        // if success ---> true
        // if exists ----> false
        // add event mark
        bool add(const Key&, const Value&);

        // if exists -------> true 
        // if not exists ---> false
        // remove event mark
        bool del(const Key&, const Value&);

        // if exists ---> true 
        // else --------> false
        bool exists(const Key&, const Value&) const;
    private:
        mutable synch m_mutex;
        multimap      m_map;
    };

//==============================================================================
//==============================================================================

    #define dTEMPLATE \
        template<class Key, class Value>
    #define dCLASS \
        marker<Key, Value>

//==============================================================================

    dTEMPLATE
    bool dCLASS::emplace(const Key& key, const Value& value)
    {
        #ifdef dHAS_EMPLACE
            this->m_map.emplace(key, value);
        #else
            this->m_map.insert(pair(key, value));
        #endif
        return true;
    }

    dTEMPLATE
    bool dCLASS::add(const Key& key, const Value& value) 
    { 
        const synch_lock lock(this->m_mutex);
        const iter found = this->m_map.find(key);
        if(found == this->m_map.end())
            return this->emplace(key, value);

        range_t range = this->m_map.equal_range(found->first);
        for( ; range.first != range.second; ++range.first)
            if(range.first->second == value)
                return false;

        return this->emplace(key, value);
    }
//==============================================================================
    // if exists ---> true 
    // if not exists ---> false
    dTEMPLATE
    bool dCLASS::del(const Key& key, const Value& value) 
    { 
        const synch_lock lock(this->m_mutex);

        const iter found = this->m_map.find(key);
        if(found == this->m_map.end())
            return false;

        range_t range = this->m_map.equal_range(found->first);
        while(range.first != range.second)
            if(range.first->second != value)
                ++range.first;
            else
                return 
                    this->m_map.erase(range.first),
                    true;

        return false;
    }
//==============================================================================
    // if exists ---> true 
    // if not exists ---> false
    dTEMPLATE
    bool dCLASS::exists(const Key& key, const Value& value) const
    {
        const synch_lock lock(this->m_mutex);

        const iter found = this->m_map.find(key);
        if(found == this->m_map.end())
            return false;

        range_t range = this->m_map.equal_range(found->first);
        while(range.first != range.second)
            if(range.first->second == value)
                return true;
            else
                ++range.first;

        return false;
    }

    #undef dTEMPLATE
    #undef dCLASS

} // namespace tools

//==============================================================================
#endif // !dTOOLS_MARKER_USED_

