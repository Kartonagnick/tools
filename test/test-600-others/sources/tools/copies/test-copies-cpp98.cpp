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

#include <tools/windows.hpp>
#include <process.h>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    struct sample: me::copies<sample> {};

    volatile LONG flag = 0;

    void foo(::LPVOID param)
    {
        (void) param;
        volatile size_t cnt = 0;
        for(size_t i = 0; i!=10; ++i)
        {
            sample s;
            cnt += sample::instances();
        }
        ::InterlockedExchangeAdd(&flag, 1);
    }

    std::vector<sample> samples;
    void bar(::LPVOID param)
    {
        (void) param;
        size_t cnt = 0;
        for(size_t i = 0; i!=10; ++i)
        {
			sample obj;
            samples.push_back(obj);
            cnt += sample::instances();
        }
        ::InterlockedExchangeAdd(&flag, 1);
    }

    void prepare()
    {
        flag = 0;
        samples.clear();
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
    ::prepare();
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
        ::Sleep(100);
    }
    ASSERT_TRUE(sample::instances() == 0)
        << "[0] samples.instances() = " << sample::instances() << '\n';
}

TEST_COMPONENT(002)
{
    ::prepare();
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
        ::Sleep(100);
    }
    ASSERT_TRUE(samples.size() == 100)
        << "[0] samples.size() = " << samples.size() << '\n';

    ASSERT_TRUE(sample::instances() == 100)
        << "[1] samples.instances() = " << sample::instances() << '\n';

    samples.clear();
    ASSERT_TRUE(sample::instances() == 0)
        << "[2] samples.instances() = " << sample::instances() << '\n';
}

#endif // !_MSC_VER
#endif // !TEST_TOOLS_COPIES

