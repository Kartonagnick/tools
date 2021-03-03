
// [2021y-02m-28d][18:05:26] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_HASH
#if defined(dHAS_HASH) && defined (dHAS_VARIADIC_TEMPLATE)

#include <tools/hash.hpp>
#include <string>
#include <map>

#define dTEST_COMPONENT tools
#define dTEST_METHOD hash
#define dTEST_TAG tdd

namespace me  = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace 
{
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

    using map_t = ::std::map<size_t, some>;

    template<class s> 
    size_t hash_text(const s& text) dNOEXCEPT
    {
        using calc = me::hash<s>;
        return calc()(text);
    }

} //namespace

dMAKE_TOOLS_HASHABLE(some, v.a, v.b);

//==============================================================================

TEST_COMPONENT(000)
{
    int a = 10; int b = 20;
    const size_t h1 = me::hash<int>()(a);
    const size_t h2 = me::hash<int>()(b);
    ASSERT_TRUE(h1 != h2);
}

TEST_COMPONENT(001)
{
    int a = 10; int b = 20;
    const size_t h1 = me::hash<int, int>()(a, b);
    const size_t h2 = me::hash<int, int>()(b, a);
    ASSERT_TRUE(h1 != h2);
}

TEST_COMPONENT(002)
{
    map_t map;
    using calc = me::hash<some>;
    for(int x = 0; x != 9; ++x)
    {
        for(int y = 0; y != 9; ++y)
        {
            const some obj(x, y);
            const size_t hkey = calc()(obj);
            map.emplace(hkey, obj);
        }
    }
    const size_t count = map.size();
    ASSERT_TRUE(count == 81);
}

TEST_COMPONENT(003)
{
    map_t map;
    size_t seed = 0;
    using calc = me::hash<some>;
    for(int x = 0; x!= 9; ++x)
    {
        for(int y = 0; y!= 9; ++y)
        {
            const some obj(x, y);
            seed = calc(seed)(obj);
            map.emplace(seed, obj);
        }
    }
    const size_t count = map.size();
    ASSERT_TRUE(count == 81);
}

TEST_COMPONENT(004)
{
    const size_t hash1 = hash_text( "123");
    const size_t hash2 = hash_text(L"123");
    const size_t hash3 = hash_text(std::string("123"));
    const size_t hash4 = hash_text(std::wstring(L"123"));

    ASSERT_TRUE(hash1 == hash3);
    ASSERT_TRUE(hash2 == hash4);
}

TEST_COMPONENT(005)
{
    char arr[] = "123";
    char* p = arr;
    const char* cp = arr;
    const char*& crp = cp;

    const size_t hash1 = hash_text(arr);
    const size_t hash2 = hash_text(p);
    const size_t hash3 = hash_text(cp);
    const size_t hash4 = hash_text(crp);

    ASSERT_TRUE(hash1 == hash2);
    ASSERT_TRUE(hash1 == hash3);
    ASSERT_TRUE(hash1 == hash4);
}

//==============================================================================
//==============================================================================
#endif // !defined(dHAS_HASH) && defined (dHAS_VARIADIC_TEMPLATE)
#endif // !TEST_TOOLS_HASH

