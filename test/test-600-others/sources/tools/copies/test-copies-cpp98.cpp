// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_COPIES
#ifdef _MSC_VER

#define dTEST_COMPONENT tools
#define dTEST_METHOD copies
#define dTEST_TAG cpp98

#include <tools/copies.hpp>
#include <vector>

#include <tools/synch.hpp>
#include <tools/windows.hpp>
#include <process.h>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    struct sample: me::copies<sample> {};

    volatile ::LONG flag = 0;

    void foo(::LPVOID param)
    {
        (void) param;
        volatile size_t cnt = 0;
        for(size_t i = 0; i != 10; ++i)
        {
            sample s;
            cnt += sample::instances();
        }
        ::InterlockedExchangeAdd(&flag, 1);
    }

    me::synch sync;
    std::vector<sample> samples;
    void bar(::LPVOID param)
    {
        (void) param;
        volatile size_t cnt = 0;
        for(size_t i = 0; i != 10; ++i)
        {
			sample obj;
            me::synch_guard guard(sync);
            samples.push_back(obj);
            cnt += sample::instances();
        }
        ::InterlockedExchangeAdd(&flag, 1);
    }

    void prepare()
    {
        flag = 0;
        samples.clear();

        ASSERT_TRUE(sample::instances() == 0)
            << "[prepare] samples.instances() = " 
            << sample::instances() << '\n';
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
    ASSERT_TRUE(sample::instances() == 0)
        << "[0] samples.instances() = " << sample::instances() << '\n';
    for(size_t i = 0; i != 10; ++i)
    {
        const ::uintptr_t re = ::_beginthread(foo, 0, 0);
	    ASSERT_TRUE(re != -1);
    }
    ::Sleep(100);

    ::LONG result = 0;
    for(;;)
    {
        result = ::InterlockedCompareExchange(&flag, 100, 10);
        if(result == 100)
            break;
        ::Sleep(30);
    }
    ASSERT_TRUE(sample::instances() == 0)
        << "[1] samples.instances() = " << sample::instances() << '\n';
}

TEST_COMPONENT(002)
{
    ::prepare();

    ASSERT_TRUE(sample::instances() == 0)
        << "[0] samples.instances() = " << sample::instances() << '\n';

    for(size_t i = 0; i != 10; ++i)
    {
        const ::uintptr_t re = ::_beginthread(bar, 0, 0);
	    ASSERT_TRUE(re != -1);
    }
    ::Sleep(100);

    ::LONG result = 0;
    for(;;)
    {
        result = ::InterlockedCompareExchange(&flag, 100, 10);
        if(result == 100)
            break;
        ::Sleep(30);
    }
    ASSERT_TRUE(samples.size() == 100)
        << "[1] samples.size() = " << samples.size() << '\n';

    ASSERT_TRUE(sample::instances() == 100)
        << "[2] samples.instances() = " << sample::instances() << '\n';

    samples.clear();
    ASSERT_TRUE(sample::instances() == 0)
        << "[3] samples.instances() = " << sample::instances() << '\n';
}

#endif // !_MSC_VER
#endif // !TEST_TOOLS_COPIES

