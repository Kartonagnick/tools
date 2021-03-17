// [2021y-02m-20d][18:40:18] Idrisov Denis R.
// [2021y-03m-17d][20:49:29] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_DEGRADATE

#include <tools/features.hpp>
#ifdef dHAS_USING_ALIAS
// #pragma message("build for msvc2013 (or newer) or other compiler")

#define dTEST_COMPONENT tools, types
#define dTEST_METHOD degradate
#define dTEST_TAG tdd

#include <tools/types/common.hpp>
#include <string>

//==============================================================================
//=== make_test ================================================================
namespace
{
    #define make_test(type, etalon)                         \
        static_assert(                                      \
            ::std::is_same<                                 \
                ::tools::degradate<type>,                   \
                etalon                                      \
            >::value,                                       \
            "tools::degradate<" #type "> -> '" #etalon "'"  \
        )                                                  \

    make_test(int       , int);
    make_test(const int , int);
    make_test(const int&, int);

}//namespace

//==============================================================================
//=== stringed(char) ===========================================================
namespace
{
    make_test(signed char        , signed char   ); 
    make_test(unsigned char      , unsigned char ); 

    make_test(const char         , char          ); // 00
    make_test(char               , char          ); // 01
                                                              
    make_test(const std::string&&, std::string   ); // 02   
    make_test(std::string&&      , std::string   ); // 03
    make_test(const std::string& , std::string   ); // 04
    make_test(std::string&       , std::string   ); // 05
    make_test(const std::string  , std::string   ); // 06
    make_test(std::string        , std::string   ); // 07
                                                              
    make_test(char*const&&       , char*         ); // 09
    make_test(char*&&            , char*         ); // 10      
    make_test(char*const&        , char*         ); // 11      
    make_test(char*&             , char*         ); // 12      
    make_test(char*const         , char*         ); // 13      
    make_test(char*              , char*         ); // 14      
                                                              
    make_test(const char*const&& , const char*   ); // 15      
    make_test(const char*&&      , const char*   ); // 16      
    make_test(const char*const&  , const char*   ); // 17      
    make_test(const char*&       , const char*   ); // 18      
    make_test(const char*const   , const char*   ); // 19      
    make_test(const char*        , const char*   ); // 20      
                                                              
    make_test(const char(&&)[255], char[255]     ); // 21      
    make_test(char(&&)[255]      , char[255]     ); // 22      
    make_test(const char(&)[255] , char[255]     ); // 23      
    make_test(char(&)[255]       , char[255]     ); // 24      
    make_test(const char[255]    , char[255]     ); // 25      
    make_test(char[255]          , char[255]     ); // 26      
                                                              
    make_test(const char(&&)[]   , char[]        ); // 27        
    make_test(char(&&)[]         , char[]        ); // 28        
    make_test(const char(&)[]    , char[]        ); // 29        
    make_test(char(&)[]          , char[]        ); // 30        
    make_test(const char[]       , char[]        ); // 31        
    make_test(char[]             , char[]        ); // 32        

    #ifdef dHAS_ZERO_SIZE_ARRAY
    dPRAGMA_PUSH_WARNING_ZERO_SIZE_ARRAY
        make_test(const char(&&)[0]  , char[0]       ); // 33        invalid types
        make_test(char(&&)[0]        , char[0]       ); // 34        invalid types
        make_test(const char(&)[0]   , char[0]       ); // 35        invalid types
        make_test(char(&)[0]         , char[0]       ); // 36        invalid types
        make_test(const char[0]      , char[0]       ); // 37        invalid types
        make_test(char[0]            , char[0]       ); // 38        invalid types
    dPRAGMA_POP
    #endif // !dHAS_ZERO_SIZE_ARRAY

}//namespace

//==============================================================================
//=== stringed(wchar_t) ========================================================
namespace 
{
    make_test(const wchar_t         , wchar_t          ); // 00
    make_test(wchar_t               , wchar_t          ); // 01
                                                              
    make_test(const std::wstring&&  , std::wstring     ); // 02   
    make_test(std::wstring&&        , std::wstring     ); // 03
    make_test(const std::wstring&   , std::wstring     ); // 04
    make_test(std::wstring&         , std::wstring     ); // 05
    make_test(const std::wstring    , std::wstring     ); // 06
    make_test(std::wstring          , std::wstring     ); // 07
                                                              
    make_test(wchar_t*const&&       , wchar_t*         ); // 09
    make_test(wchar_t*&&            , wchar_t*         ); // 10      
    make_test(wchar_t*const&        , wchar_t*         ); // 11      
    make_test(wchar_t*&             , wchar_t*         ); // 12      
    make_test(wchar_t*const         , wchar_t*         ); // 13      
    make_test(wchar_t*              , wchar_t*         ); // 14      
                                                              
    make_test(const wchar_t*const&& , const wchar_t*   ); // 15      
    make_test(const wchar_t*&&      , const wchar_t*   ); // 16      
    make_test(const wchar_t*const&  , const wchar_t*   ); // 17      
    make_test(const wchar_t*&       , const wchar_t*   ); // 18      
    make_test(const wchar_t*const   , const wchar_t*   ); // 19      
    make_test(const wchar_t*        , const wchar_t*   ); // 20      
                                                              
    make_test(const wchar_t(&&)[255], wchar_t[255]     ); // 21      
    make_test(wchar_t(&&)[255]      , wchar_t[255]     ); // 22      
    make_test(const wchar_t(&)[255] , wchar_t[255]     ); // 23      
    make_test(wchar_t(&)[255]       , wchar_t[255]     ); // 24      
    make_test(const wchar_t[255]    , wchar_t[255]     ); // 25      
    make_test(wchar_t[255]          , wchar_t[255]     ); // 26      
                                                              
    make_test(const wchar_t(&&)[]   , wchar_t[]        ); // 27        
    make_test(wchar_t(&&)[]         , wchar_t[]        ); // 28        
    make_test(const wchar_t(&)[]    , wchar_t[]        ); // 29        
    make_test(wchar_t(&)[]          , wchar_t[]        ); // 30        
    make_test(const wchar_t[]       , wchar_t[]        ); // 31        
    make_test(wchar_t[]             , wchar_t[]        ); // 32        

    #ifdef dHAS_ZERO_SIZE_ARRAY
    dPRAGMA_PUSH_WARNING_ZERO_SIZE_ARRAY
        make_test(const wchar_t(&&)[0]  , wchar_t[0]       ); // 33        invalid types
        make_test(wchar_t(&&)[0]        , wchar_t[0]       ); // 34        invalid types
        make_test(const wchar_t(&)[0]   , wchar_t[0]       ); // 35        invalid types
        make_test(wchar_t(&)[0]         , wchar_t[0]       ); // 36        invalid types
        make_test(const wchar_t[0]      , wchar_t[0]       ); // 37        invalid types
        make_test(wchar_t[0]            , wchar_t[0]       ); // 38        invalid types
    dPRAGMA_POP
    #endif

} // namespace

//==============================================================================
//=== stringed(int) ============================================================
namespace
{
    using string_t = std::basic_string<int>;

    make_test(const int         , int          ); // 00
    make_test(int               , int          ); // 01
                                                              
    make_test(const string_t&&  , string_t     ); // 02   
    make_test(string_t&&        , string_t     ); // 03
    make_test(const string_t&   , string_t     ); // 04
    make_test(string_t&         , string_t     ); // 05
    make_test(const string_t    , string_t     ); // 06
    make_test(string_t          , string_t     ); // 07
                                                              
    make_test(int*const&&       , int*         ); // 09
    make_test(int*&&            , int*         ); // 10      
    make_test(int*const&        , int*         ); // 11      
    make_test(int*&             , int*         ); // 12      
    make_test(int*const         , int*         ); // 13      
    make_test(int*              , int*         ); // 14      
                                                              
    make_test(const int*const&& , const int*   ); // 15      
    make_test(const int*&&      , const int*   ); // 16      
    make_test(const int*const&  , const int*   ); // 17      
    make_test(const int*&       , const int*   ); // 18      
    make_test(const int*const   , const int*   ); // 19      
    make_test(const int*        , const int*   ); // 20      
                                                              
    make_test(const int(&&)[255], int[255]     ); // 21      
    make_test(int(&&)[255]      , int[255]     ); // 22      
    make_test(const int(&)[255] , int[255]     ); // 23      
    make_test(int(&)[255]       , int[255]     ); // 24      
    make_test(const int[255]    , int[255]     ); // 25      
    make_test(int[255]          , int[255]     ); // 26      
                                                              
    make_test(const int(&&)[]   , int[]        ); // 27        
    make_test(int(&&)[]         , int[]        ); // 28        
    make_test(const int(&)[]    , int[]        ); // 29        
    make_test(int(&)[]          , int[]        ); // 30        
    make_test(const int[]       , int[]        ); // 31        
    make_test(int[]             , int[]        ); // 32        
                
    #ifdef dHAS_ZERO_SIZE_ARRAY
    dPRAGMA_PUSH_WARNING_ZERO_SIZE_ARRAY
        make_test(const int(&&)[0]  , int[0]       ); // 33        invalid types
        make_test(int(&&)[0]        , int[0]       ); // 34        invalid types
        make_test(const int(&)[0]   , int[0]       ); // 35        invalid types
        make_test(int(&)[0]         , int[0]       ); // 36        invalid types
        make_test(const int[0]      , int[0]       ); // 37        invalid types
        make_test(int[0]            , int[0]       ); // 38        invalid types
    dPRAGMA_POP
    #endif

} // namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000){}

//==============================================================================
//==============================================================================

#endif // !dHAS_USING_ALIAS
#endif // !TEST_TOOLS_DEGRADATE

