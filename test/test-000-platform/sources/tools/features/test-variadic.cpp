// [2021y-02m-28d][01:43:52] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_VARIADIC_TEMPLATE

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_VARIADIC_TEMPLATE
#define dTEST_TAG tdd

#include <tools/features.hpp>

#ifndef dHAS_VARIADIC_TEMPLATE
    dMESSAGE("[test] tools: disabled -> dHAS_VARIADIC_TEMPLATE")
#else
    dMESSAGE("[test] tools: enabled -> dHAS_VARIADIC_TEMPLATE")
#endif

#ifdef dHAS_VARIADIC_TEMPLATE
#include <string>
//==============================================================================
//==============================================================================
namespace
{
    template<class Val> struct swither
    {
        swither( const Val & v )
            :val(v)
        {}

        void operator()() const dNOEXCEPT {}

        template <class E, class F, class ... Args>
        void operator()(E&& e, F&& f, Args&& ... args) const 
        {
            if(e == std::string(val))
                f(); 
            else
                (*this)(::std::forward<Args>(args)...);
        }
    private:
        Val val;
    };

    template<class Val> swither<Val> Swith(const Val& v)
        { return swither<Val>(v); }

    #define dCASE(n) n,[]()

    int result = 0;

}//namespace

TEST_COMPONENT(000)
{
    auto x = "trololo";
    Swith(x) (
        dCASE("ololo")   { result = 1; },
        dCASE("trololo") { result = 2; }
    );
    ASSERT_TRUE(result == 2);
}

//==============================================================================
//==============================================================================
#endif // ! dHAS_VARIADIC_TEMPLATE
#endif // ! TEST_TOOLS_FEATURE_VARIADIC_TEMPLATE



