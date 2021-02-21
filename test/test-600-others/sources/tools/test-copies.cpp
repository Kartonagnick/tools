// [2021y-02m-21d] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_COPIES

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) copies_##n

#include <test-staff.hpp>
#include <tools/copies.hpp>
#include <vector>

#ifdef dHAS_ATOMIC
    #include <thread>
#endif

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    struct sample: me::copies<sample> {};

    size_t threadFunction()
    {
        size_t cnt = 0;
        for(size_t i = 0; i!=10; ++i)
        {
            sample s;
            cnt += sample::instances();
        }
        return cnt;
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

#ifdef dHAS_ATOMIC
TEST_COMPONENT(001)
{
    std::vector<std::thread> vec;

    for(size_t i = 0; i!=10; ++i)
        vec.emplace_back(threadFunction);

    for(size_t i = 0; i!=10; ++i)
        if(vec[i].joinable())
            vec[i].join();

    ASSERT_TRUE(sample::instances() == 0);
}
#endif // dHAS_ATOMIC

#if defined(_MSC_VER) && !defined(dHAS_ATOMIC)
#include <windows.h>
#include <process.h>

volatile LONG flag = 0;

void threadFunction(LPVOID param)
{
    (void) param;

    ::InterlockedExchangeAdd(&flag, 1);

    volatile size_t cnt = 0;
    for(size_t i = 0; i!=10; ++i)
    {
        sample s;
        cnt += sample::instances();
    }

    ::InterlockedExchangeAdd(&flag, -1);

    ::_endthread();
}

TEST_COMPONENT(001)
{
	unsigned id = 0; 
    for(size_t i = 0; i!=10; ++i)
    {
        const uintptr_t re 
            = ::_beginthread(threadFunction, 0, &id);
	    ASSERT_TRUE(re != -1);

    }

    ::Sleep(100);

    LONG fl = 0;
    for(;;)
    {
        fl = ::InterlockedCompareExchange(&flag, 0, 0);
        if(fl == 0)
            break;
        ::Sleep(100);
    }

    ASSERT_TRUE(sample::instances() == 0);
}
#endif // dHAS_ATOMIC



#endif // !TEST_TOOLS_COPIES

