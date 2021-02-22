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
#include <mutex>

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

    std::mutex mut;
    ::std::vector<sample> samples;
    void bar()
    {
        size_t cnt = 0;
        for(size_t i = 0; i != 10; ++i)
        {
            std::lock_guard<std::mutex>
                lock(mut);
            samples.emplace_back();
            cnt += sample::instances();
        }
    }

    void prepare()
    {
        samples.clear();
    }

    void check(const size_t index, const size_t etalon)
    {
        const size_t count = sample::instances();
        ASSERT_TRUE(count == etalon)
            << index << ") "
            << "etalon = " << etalon << ", "
            << "real = "   << count << '\n';
    }

}//namespace
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    ::prepare();
    check(0, 0);
    {
        sample obj1, obj2;
        (void) obj1;
        (void) obj2;
        check(1, 2);
        {
            sample obj3, obj4;
            (void) obj3;
            (void) obj4;
            check(2, 4);
        }
        check(3, 2);
    }
    check(4, 0);
}

TEST_COMPONENT(001)
{
    ::prepare();
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
    ::prepare();
    ::std::vector<::std::thread> vec;
    for(size_t i = 0; i != 10; ++i)
        vec.emplace_back(bar);

    for(size_t i = 0; i != 10; ++i)
        if(vec[i].joinable())
            vec[i].join();

    ASSERT_TRUE(samples.size() == 100)
        << "[0] samples.size() = " << samples.size() << '\n';

    ASSERT_TRUE(sample::instances() == 100)
        << "[2] samples.instances() = " << sample::instances() << '\n';

    samples.clear();
    ASSERT_TRUE(sample::instances() == 0);
}

#endif // !dHAS_ATOMIC
#endif // !TEST_TOOLS_COPIES

