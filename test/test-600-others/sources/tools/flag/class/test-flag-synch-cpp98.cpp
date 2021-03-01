// [2021y-02m-28d][00:53:48] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FLAG
#ifdef _MSC_VER

#define dTEST_COMPONENT tools
#define dTEST_METHOD flag
#define dTEST_TAG synch_cpp98

#include <tools/flag.hpp>
#include <tools/windows.hpp>
#include <process.h>

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    enum eFLAGS 
    { 
        eNONE = 0, 
        eALL  = 1, 
        eVAL1 = 1 << 1, 
        eVAL2 = 1 << 2, 
        eVAL3 = 1 << 3, 
        eVAL4 = 1 << 4, 
        eVAL5 = 1 << 5, 
        eVAL6 = 1 << 6, 
        eVAL7 = 1 << 7, 
    };
	typedef me::flag<eFLAGS> 
        flag_t;

    flag_t g_flags(eVAL1);

    const int change1 = eVAL2 | eVAL3 | eVAL4;
    const int change2 = eVAL5 | eVAL6 | eVAL7;

    volatile long started;
    volatile long finished;

    struct param { bool dir; size_t limit; };

    void loop(void* ptr)
    {
        ASSERT_TRUE(ptr);
        const param& ref = *static_cast<const param*>(ptr);

        dprint(std::cout << "started: " << ref.dir << " " << ref.limit << std::endl);
        ++started;
        while (started != 2)
			::Sleep(30);

        for (size_t i = 0; i < ref.limit; ++i)
        {
            if (ref.dir)
                g_flags.change(change1, change2);
            else
                g_flags.change(change2, change1);
        }
        dprint(std::cout << "done: " << ref.dir << " " << ref.limit << std::endl);
        ++finished;
    }

    size_t count_positive = 2000000;
    size_t count_negative = 1000000;

    void prepare()
    {
        started  = 0;
        finished = 0;
        g_flags = eVAL1;

        count_negative = testing::stress ? 1000000 : 100;
        count_positive = count_negative * 2;
    }

    void title(const size_t i, const size_t t)
    {
        (void)i;
        (void)t;
        dprint(
            std::cout << "generation(" << count_negative << "): " 
                << i + 1 << "/" << t << '\n'
        );
    }

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    #ifdef INCLUDE_LONG_LONG_TESTS
        const size_t total = 10;
    #elif defined (INCLUDE_LONG_TESTS)
        const size_t total = 5;
    #else
        const size_t total = 1;
    #endif

    const int etalon1 = eVAL1 | change1;
    const int etalon2 = eVAL1 | change2;

    prepare();
    ::param positive = { true , count_positive };
    ::param negative = { false, count_negative };

    for (size_t i = 0; i != total; ++i)
    {
        prepare();
        title(i, total);

        const uintptr_t re 
            = ::_beginthread(::loop, 0, &positive);
	    ASSERT_TRUE(re != -1);

        ::loop(&negative);

        while (finished != 2)
            ::Sleep(30);

        const int real = g_flags.as<int>();
        ASSERT_TRUE(g_flags == real);

        const bool success1 = g_flags == etalon1;
        const bool success2 = g_flags == etalon2;
        const bool success = success1 || success2;

        ASSERT_TRUE(success)
            << "etalon1 = " << etalon1 << '\n'
            << "etalon2 = " << etalon2 << '\n'
            << "real = "    << real    << '\n'
            << "change1 = " << change1 << '\n'
            << "change2 = " << change2 << '\n'
        ;
    }
    ::Sleep(30);
}

//==============================================================================
//==============================================================================
#endif // ! _MSC_VER
#endif // ! TEST_TOOLS_FLAG



