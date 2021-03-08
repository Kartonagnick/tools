// [2021y-02m-28d][18:05:26] Idrisov Denis R.
#include <mygtest/modern.hpp>

//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_HASH
#if defined(dHAS_HASH) && defined (dHAS_VARIADIC_TEMPLATE)
#include <tools/hash/combine.hpp>
#include <functional>
#include <string>
#include <map>

#define dTEST_COMPONENT tools, hash
#define dTEST_METHOD combine
#define dTEST_TAG tdd

namespace me  = ::tools;
//==============================================================================
//=== TDD ======================================================================
namespace 
{
    struct some
    {
        some(const int x = 0, const int y = 0) dNOEXCEPT
            : a(x), b(y)
        {}

        some(const some& rhs) dNOEXCEPT
            : a(rhs.a), b(rhs.b)
        {}

        int a, b;
    };

    using map_t = ::std::map<size_t, some>;

} //namespace

dMAKE_HASHABLE(some, v.a, v.b);

//==============================================================================

TEST_COMPONENT(000)
{
    int a = 10; int b = 20;

    const size_t re1 = me::hash_combine(0u, a, b);
    const size_t re2 = me::hash_combine(0u, b, a);

    ASSERT_TRUE(re1 != re2);
}

TEST_COMPONENT(001)
{
    using calc = std::hash<some>;

    map_t map;
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

TEST_COMPONENT(002)
{
    size_t seed = 0;
    map_t map;
    for(int x = 0; x!= 9; ++x)
    {
        for(int y = 0; y!= 9; ++y)
        {
            const some obj(x, y);
            seed = me::hash_combine(seed, obj);
            map.emplace(seed, obj);
        }
    }
    const size_t count = map.size();
    ASSERT_TRUE(count == 81);
}

TEST_COMPONENT(003)
{
    const size_t hash1 = me::hash_combine(0,  "123");
    const size_t hash2 = me::hash_combine(0, L"123");
    const size_t hash3 = me::hash_combine(0, std::string("123"));
    const size_t hash4 = me::hash_combine(0, std::wstring(L"123"));

    ASSERT_TRUE(hash1 == hash3);
    ASSERT_TRUE(hash2 == hash4);
}

TEST_COMPONENT(004)
{
    char arr[] = "123";
    char* p = arr;
    const char* cp = arr;
    const char*& crp = cp;

    const size_t hash1 = me::hash_combine(0, arr);
    const size_t hash2 = me::hash_combine(0, p  );
    const size_t hash3 = me::hash_combine(0, cp );
    const size_t hash4 = me::hash_combine(0, crp);

    ASSERT_TRUE(hash1 == hash2);
    ASSERT_TRUE(hash1 == hash3);
    ASSERT_TRUE(hash1 == hash4);
}

//==============================================================================
//==============================================================================
#endif // !defined(dHAS_HASH) && defined (dHAS_VARIADIC_TEMPLATE)
#endif // !TEST_TOOLS_HASH
