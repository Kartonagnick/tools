// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_COPIES

#define dTEST_COMPONENT tools
#define dTEST_METHOD copies
#define dTEST_TAG cpp11

#include <tools/features.hpp>

#ifdef dHAS_ATOMIC

#include <tools/copies.hpp>
#include <vector>
#include <thread>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    struct sample: me::copies<sample> {};
    void foo()
    {
        size_t cnt = 0;
        for(size_t i = 0; i != 10; ++i)
        {
            sample s;
            cnt += sample::instances();
        }
    }

    ::std::vector<sample> samples;
    void bar()
    {
        size_t cnt = 0;
        for(size_t i = 0; i != 10; ++i)
        {
            samples.emplace_back();
            cnt += sample::instances();
        }
    }

}//namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    {
        sample obj1, obj2;
        (void) obj1;
        (void) obj2;
        ASSERT_TRUE(sample::instances() == 2);
        {
            sample obj3, obj4;
            (void) obj3;
            (void) obj4;
            ASSERT_TRUE(sample::instances() == 4);
        }
        ASSERT_TRUE(sample::instances() == 2);
    }
    ASSERT_TRUE(sample::instances() == 0);
}

TEST_COMPONENT(001)
{
    ::std::vector<::std::thread> vec;
    for(size_t i = 0; i != 10; ++i)
        vec.emplace_back(foo);

    for(size_t i = 0; i != 10; ++i)
        if(vec[i].joinable())
            vec[i].join();

    ASSERT_TRUE(sample::instances() == 0);
}

TEST_COMPONENT(002)
{
    ::std::vector<::std::thread> vec;
    for(size_t i = 0; i != 10; ++i)
        vec.emplace_back(bar);

    for(size_t i = 0; i != 10; ++i)
        if(vec[i].joinable())
            vec[i].join();

    ASSERT_TRUE(samples.size() == 100);
    ASSERT_TRUE(sample::instances() == 100);

    samples.clear();
    ASSERT_TRUE(sample::instances() == 0);
}

#endif // !dHAS_ATOMIC
#endif // !TEST_TOOLS_COPIES

