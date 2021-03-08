// [2021y-02m-28d][18:05:26] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_HASH

#include <tools/hash/accum.hpp>
#include <string>
#include <map>

#define dTEST_COMPONENT tools, hash
#define dTEST_METHOD accum
#define dTEST_TAG tdd

namespace me  = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace 
{
    typedef me::hash_accum::u32 u32;

    struct some
    {
        some(const int x = 0, const int y = 0) 
            : a(x), b(y)
        {}

        some(const some& rhs)
            : a(rhs.a), b(rhs.b)
        {}

        int a, b;
    };

    typedef ::std::map<u32, some> 
        map_t;

    template<class s>
    u32 hash_text(const s& text) dNOEXCEPT
    {
        me::hash_accum acc;
        acc.add(text);
        return acc;
    }

} //namespace
//==============================================================================

TEST_COMPONENT(000)
{
    const int a = 10;
    const int b = 20;

    me::hash_accum acc;
    acc.add(a);

    const u32 f1 = acc.get();
    acc.add(b);

    const u32 f2 = acc.get();
    ASSERT_TRUE(f1 != f2);
}

TEST_COMPONENT(001)
{
    map_t map;
    for(int x = 0; x != 9; ++x)
    {
        for(int y = 0; y != 9; ++y)
        {
            const some obj(x, y);
            me::hash_accum acc;
            acc.add(obj);
            map[acc.get()] = obj;
        }
    }
    const size_t count = map.size();
    ASSERT_TRUE(count == 81);
}

TEST_COMPONENT(002)
{
    me::hash_accum acc;
    map_t map;
    for(int x = 0; x!= 9; ++x)
    {
        for(int y = 0; y!= 9; ++y)
        {
            const some obj(x, y);
            acc.add(obj);
            map[acc.get()] = obj;
        }
    }
    const size_t count = map.size();
    ASSERT_TRUE(count == 81);
}

TEST_COMPONENT(003)
{
    const u32 hash1 = hash_text( "123");
    const u32 hash2 = hash_text(L"123");
    const u32 hash3 = hash_text(std::string("123"));
    const u32 hash4 = hash_text(std::wstring(L"123"));

    ASSERT_TRUE(hash1 == hash3);
    ASSERT_TRUE(hash2 == hash4);
}

TEST_COMPONENT(004)
{
    char arr[] = "123";
    char* p = arr;
    const char* cp = arr;
    const char*& crp = cp;

    const u32 hash1 = hash_text(arr);
    const u32 hash2 = hash_text(p);
    const u32 hash3 = hash_text(cp);
    const u32 hash4 = hash_text(crp);

    ASSERT_TRUE(hash1 == hash2);
    ASSERT_TRUE(hash1 == hash3);
    ASSERT_TRUE(hash1 == hash4);
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_HASH
