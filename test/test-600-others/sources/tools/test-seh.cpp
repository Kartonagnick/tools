// [2019y-10m-24d][19:22:08] Idrisov Denis R.
// [2021y-03m-07d][08:47:11] Idrisov Denis R.
#include <mygtest/test-list.hpp>

#ifdef TEST_TOOLS_SEH

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) seh_##n

#include <tools/seh.hpp>
#include <algorithm>
#include <iostream>
#include <cstdarg>
#include <cassert>
#include <cstdio>
#include <vector>

#ifndef dDISABLE_DPRINT
    #include <tools/synch.hpp>
#endif

namespace me = ::TEST_CASE_NAME::seh;
//==============================================================================
//=== TDD ======================================================================
namespace
{
    typedef ::std::string 
        str_t;

    typedef ::std::vector<str_t>
        vec_t;

    template<class container, class iter>
    inline void insert(container& collection, const iter& cur, const iter& lst)
    {
        const size_t length
            = static_cast<size_t>(cur - lst);

        #ifdef dHAS_RVALUE_REFERENCES
            collection.emplace_back(&(*lst), length);
        #else
            collection.push_back(str_t(&(*lst), length));
        #endif
    }

    inline vec_t tokenizePath(const str_t& path)
    {
        typedef str_t::const_iterator it;

        vec_t result;
        result.reserve(20);

        it lst_pos = path.begin();
        it cur_pos = lst_pos;
        const it end_string   = path.end();
        const char separators[3] = "\\/";

        for(;;)
        {
            cur_pos = ::std::find_first_of(
                lst_pos,
                end_string,
                separators,
                separators + 2
            );

            if(cur_pos == end_string)
            {
                if(cur_pos != lst_pos)
                    insert(result, cur_pos, lst_pos);
                break;
            }
            if(cur_pos != lst_pos)
                insert(result, cur_pos, lst_pos);
            lst_pos = cur_pos + 1;
        }
        return result;
    }

    inline void output_seh_exception_(const char* func, const char* reason) dNOEXCEPT
    {
        (void) func;
        (void) reason;

        assert(func);
        assert(reason);
        dprint(::std::cerr << func << "(seh-exception): " << reason << '\n');
    }

    inline void output_std_exception_(const char* func, const char* reason) dNOEXCEPT
    {
        (void) func;
        (void) reason;

        assert(func);
        assert(reason);
        dprint(::std::cerr << func << "(std::exception): " << reason << '\n');
    }

    inline void output_unknown_exception_(const char* func) dNOEXCEPT
    {
        (void) func;
        assert(func);
        dprint(::std::cerr << func << "(exception): unknown\n");
    }

    void stress() dNOEXCEPT
    {
        int* p = 0;
        std::cout << *p;
    }

    long double proc()
    {
        long double res, x;
        
        long double ve[10] = {};

        x = 1.123;
        // int n = 5;

        // В процедуре могут возникать различные исключения,например,
        // деление на ноль: 
        // res = x / sin(x - x);
        // res = n / (n - 5);

        // переполнение:
        // res = pow(x, x * 1000);

        // неверная операция:
        // res = pow(-x, x);

        // ошибка доступа:
        res = x + ve[20];

        return res;
    }


}//namespace
//==============================================================================
TEST_COMPONENT(000)
{
    me::guard guard;
    try 
    {
        int* p = 0;
        std::cout << *p;
    }
    catch (const ::std::exception& e) 
    {
        (void) e;
        dprint(::std::cerr << e.what() << "\n");
    }

    try
    {
        int* p = 0;
        *p = 0;
        std::cout << *p;
    }
    catch (const ::std::exception& e) 
    {
        (void)e;
        dprint(::std::cerr << e.what() << "\n");
    }

    try 
    {
        int a = 42;
        volatile int b = 0;
        std::cout << a / b;
    }
    catch (const ::std::exception& e) 
    {
        (void) e;
        dprint(::std::cerr << e.what() << "\n");
    }

    try 
    {
        throw std::runtime_error("ololo");
    }
    catch (const ::std::exception& e) 
    {
        (void) e;
        dprint(::std::cerr << e.what() << "\n");
    }
}
TEST_COMPONENT(001)
{
    dBEGIN_SEH_EXCEPTION 
    {
        int* p = 0;
        std::cout << *p;
    }
    dEND_SEH_EXCEPTION;

    dBEGIN_SEH_EXCEPTION
    {
        int* p = 0;
        *p = 0;
        std::cout << *p;
    }
    dEND_SEH_EXCEPTION;

    dBEGIN_SEH_EXCEPTION 
    {
        int a = 42;
        volatile int b = 0;
        std::cout << a / b;
    }
    dEND_SEH_EXCEPTION;

    dBEGIN_SEH_EXCEPTION 
    {
        int* a = reinterpret_cast<int*>(1);
        std::cout << *a;
    }
    dEND_SEH_EXCEPTION;

    dBEGIN_SEH_EXCEPTION 
    {
        int* a = reinterpret_cast<int*>(1);
        *a = 10;
    }
    dEND_SEH_EXCEPTION;


    dBEGIN_SEH_EXCEPTION 
    {
        int* a = reinterpret_cast<int*>(0xFF0000);
        *a = 10;
    }
    dEND_SEH_EXCEPTION;

    dBEGIN_SEH_EXCEPTION 
    {
        throw std::runtime_error("ololo");
    }
    dEND_SEH_EXCEPTION;

    dBEGIN_SEH_EXCEPTION 
    {
        throw 1;
    }
    dEND_SEH_EXCEPTION;
}
TEST_COMPONENT(002)
{
    const vec_t re = tokenizePath("C:\\test1\\test2\\test3.exe");
    ASSERT_TRUE( re.size()==4         );
    ASSERT_TRUE( re[0] == "C:"        );
    ASSERT_TRUE( re[1] == "test1"     );
    ASSERT_TRUE( re[2] == "test2"     );
    ASSERT_TRUE( re[3] == "test3.exe" );
}
TEST_COMPONENT(003)
{
    const vec_t re = tokenizePath("C:\\test1\\..\\test3.exe");
    ASSERT_TRUE( re.size()==4         );
    ASSERT_TRUE( re[0] == "C:"        );
    ASSERT_TRUE( re[1] == "test1"     );
    ASSERT_TRUE( re[2] == ".."        );
    ASSERT_TRUE( re[3] == "test3.exe" );
}
TEST_COMPONENT(004)
{
    const vec_t re = tokenizePath("test3.exe");
    ASSERT_TRUE( re.size()==1         );
    ASSERT_TRUE( re[0] == "test3.exe" );
}
TEST_COMPONENT(005)
{
    const vec_t re = tokenizePath("C:\\test1\\../\\test3.exe");
    ASSERT_TRUE( re.size()==4         );
    ASSERT_TRUE( re[0] == "C:"        );
    ASSERT_TRUE( re[1] == "test1"     );
    ASSERT_TRUE( re[2] == ".."        );
    ASSERT_TRUE( re[3] == "test3.exe" );
}
TEST_COMPONENT(006)
{
    const vec_t re = tokenizePath("C:\\test1\\../\\test3.exe//\\");
    ASSERT_TRUE( re.size()==4         );
    ASSERT_TRUE( re[0] == "C:"        );
    ASSERT_TRUE( re[1] == "test1"     );
    ASSERT_TRUE( re[2] == ".."        );
    ASSERT_TRUE( re[3] == "test3.exe" );
}
TEST_COMPONENT(007)
{
    const vec_t re = tokenizePath("");
    ASSERT_TRUE(re.size()==0);
}
TEST_COMPONENT(008)
{
    const vec_t re = tokenizePath("//\\");
    ASSERT_TRUE(re.size()==0);
}
TEST_COMPONENT(009)
{
    const vec_t re = tokenizePath("/example/");
    ASSERT_TRUE(re.size()==1);
    ASSERT_TRUE(re[0] == "example");
}
TEST_COMPONENT(010)
{
    me::guard guard;
    try 
    {
        stress();
    }
    catch (const ::std::exception& e) 
    {
        (void)e;
        dprint(::std::cerr << "std::exception: " <<  e.what() << "\n");
    }
}

TEST_COMPONENT(011)
{
    me::guard guard;
    try 
    {
        proc();
    }
    catch (const ::std::exception& e) 
    {
        (void)e;
        dprint(::std::cerr << "std::exception: " <<  e.what() << "\n");
    }
}

TEST_COMPONENT(012)
{
    me::exception e1("hello");
    me::exception e2 = e1;
    e2 = e1;
    const str_t msg = e2.what();
    ASSERT_TRUE(msg == "hello");
}

//==============================================================================
//==============================================================================
#endif  // !TEST_TOOLS_SEH



