// [2021y-02m-27d][21:41:43] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FLAG

#include<tools/features.hpp>

#ifdef dHAS_CPP11

#include <tools/flag/function.hpp>

#define dTEST_COMPONENT tools, flag
#define dTEST_METHOD function
#define dTEST_TAG int_cpp11

namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    enum eFLAGS: int
    {
        eNONE     = 0,
        eALL      = 1,
        ePOINTER  = 1 << 1,
        eARRAY    = 1 << 2,
        eSTRING   = 1 << 3,
        eSYMBOL   = 1 << 4,
        eCONST    = 1 << 5,
        eVOLATILE = 1 << 6,
        eLVALUE   = 1 << 7,
        eRVALUE   = 1 << 8,
        eVALUE    = 1 << 9
    };

    #define has_flag_test(flags, what, etalon)             \
        static_assert(                                     \
            me::has_flags(what, flags) == (etalon),        \
            "tools::has_flags(" #what ", " #flags ") "     \
            "must be '" #etalon "'"                        \
        )

    #define has_any_flag_test(flags, what, etalon)         \
        static_assert(                                     \
            me::has_any_flags(what, flags) == (etalon),    \
            "tools::has_any_flags(" #what ", " #flags ") " \
            "must be '" #etalon "'"                        \
        )

    #define del_flag_test(flags, what, etalon)             \
        static_assert(                                     \
            me::del_flags(what, flags) == (etalon),        \
            "tools::del_flags(" #what ", " #flags ") "     \
            "must be '" #etalon "'"                        \
        )                                                  
                                                           
    #define add_flag_test(flags, what, etalon)             \
        static_assert(                                     \
            me::add_flags(what, flags) == (etalon),        \
            "tools::add_flags(" #what ", " #flags ") "     \
            "must be '" #etalon "'"                        \
        )

} // namespace

//==============================================================================
//==============================================================================

// --- has_flag
TEST_COMPONENT(000)
{
    //           |  flags                 | what                   | expected  |
    has_flag_test(ePOINTER|eARRAY         , eARRAY                 ,   true    );
    has_flag_test(ePOINTER|eARRAY         , ePOINTER               ,   true    );
    has_flag_test(ePOINTER|eARRAY         , ePOINTER|eARRAY        ,   true    );
    has_flag_test(ePOINTER|eARRAY         , eVALUE                 ,   false   );
    has_flag_test(ePOINTER|eARRAY         , eVALUE|ePOINTER        ,   false   );
    has_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY          ,   false   );
    has_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY|ePOINTER ,   false   );
                                                                              
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eARRAY                 ,   true    );
    has_flag_test(eLVALUE|ePOINTER|eARRAY , ePOINTER               ,   true    );
    has_flag_test(eLVALUE|ePOINTER|eARRAY , ePOINTER|ePOINTER      ,   true    );
                                                                              
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE                 ,   false   );
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE|ePOINTER        ,   false   );
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE|eARRAY          ,   false   );
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE|eARRAY|ePOINTER ,   false   );
                                                                              
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eALL                   ,   false   );
    has_flag_test(eNONE                   , eALL                   ,   false   );
    has_flag_test(eALL                    , eALL                   ,   true    );
                                                                              
    has_flag_test(eLVALUE|ePOINTER|eARRAY , eNONE                  ,   false   );
    has_flag_test(eNONE                   , eNONE                  ,   true    );
    has_flag_test(eALL                    , eNONE                  ,   false   );
    has_flag_test(eARRAY                  , ePOINTER|eARRAY        ,   false   );
}

// --- has_any_flag
TEST_COMPONENT(001)
{   
    //           |  flags                     | what                   | expected |
    has_any_flag_test(ePOINTER|eARRAY         , eARRAY                 ,   true   );
    has_any_flag_test(ePOINTER|eARRAY         , ePOINTER               ,   true   );
    has_any_flag_test(ePOINTER|eARRAY         , ePOINTER|eARRAY        ,   true   );
    has_any_flag_test(ePOINTER|eARRAY         , eVALUE                 ,   false  );
    has_any_flag_test(ePOINTER|eARRAY         , eVALUE|ePOINTER        ,   true   );
    has_any_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY          ,   true   );
    has_any_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY|ePOINTER ,   true   );
    has_any_flag_test(ePOINTER|eARRAY         , eVALUE|eSYMBOL         ,   false  );
                                                                           
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eARRAY                 ,   true   );
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , ePOINTER               ,   true   );
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , ePOINTER|ePOINTER      ,   true   );
                                                                           
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE                 ,   false  );
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE|ePOINTER        ,   true   );
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE|eARRAY          ,   true   );
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eVALUE|eARRAY|ePOINTER ,   true   );
                                                                           
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eALL                   ,   true   );
    has_any_flag_test(eNONE                   , eALL                   ,   false  );
    has_any_flag_test(eALL                    , eALL                   ,   true   );
                                                                           
    has_any_flag_test(eLVALUE|ePOINTER|eARRAY , eNONE                  ,   false  );
    has_any_flag_test(eNONE                   , eNONE                  ,   true   );
    has_any_flag_test(eALL                    , eNONE                  ,   false  );
    has_any_flag_test(eARRAY                  , ePOINTER|eARRAY        ,   true   );
}

// --- del_flag
TEST_COMPONENT(002)
{
    //           |  flags                 | what                   | expected                |
    del_flag_test(ePOINTER|eARRAY         , eARRAY                 , ePOINTER                );
    del_flag_test(ePOINTER|eARRAY         , ePOINTER               , eARRAY                  );
    del_flag_test(ePOINTER|eARRAY         , ePOINTER|eARRAY        , eNONE                   );
    del_flag_test(ePOINTER|eARRAY         , eVALUE                 , ePOINTER|eARRAY         );
    del_flag_test(ePOINTER|eARRAY         , eVALUE|ePOINTER        , eARRAY                  );
    del_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY          , ePOINTER                );
    del_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY|ePOINTER , eNONE                   );
    del_flag_test(ePOINTER|eARRAY         , eVALUE|eSYMBOL         , ePOINTER|eARRAY         );
    del_flag_test(ePOINTER|eARRAY         , eALL                   , eNONE                   );
    del_flag_test(ePOINTER|eARRAY         , eNONE                  , ePOINTER|eARRAY         );
                                                                                             
    del_flag_test(eLVALUE|ePOINTER|eARRAY , eALL                   , eNONE                   );
    del_flag_test(eNONE                   , eALL                   , eNONE                   );
    del_flag_test(eALL                    , eALL                   , eNONE                   );

    del_flag_test(eLVALUE|ePOINTER|eARRAY , eNONE                  , eLVALUE|ePOINTER|eARRAY );
    del_flag_test(eNONE                   , eNONE                  , eNONE                   );
    del_flag_test(eALL                    , eNONE                  , eALL                    );
    del_flag_test(eARRAY                  , ePOINTER|eARRAY        , eNONE                   );
}

// --- add_flag
TEST_COMPONENT(003)
{
    //           |  flags                 | what                   | expected                       |
    add_flag_test(ePOINTER|eARRAY         , eARRAY                 , ePOINTER|eARRAY                );
    add_flag_test(ePOINTER|eARRAY         , ePOINTER               , ePOINTER|eARRAY                );
    add_flag_test(ePOINTER|eARRAY         , ePOINTER|eARRAY        , ePOINTER|eARRAY                );
    add_flag_test(ePOINTER|eARRAY         , eVALUE                 , ePOINTER|eARRAY|eVALUE         );
    add_flag_test(ePOINTER|eARRAY         , eVALUE|ePOINTER        , ePOINTER|eARRAY|eVALUE         );
    add_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY          , ePOINTER|eARRAY|eVALUE         );
    add_flag_test(ePOINTER|eARRAY         , eVALUE|eARRAY|ePOINTER , ePOINTER|eARRAY|eVALUE         );
    add_flag_test(ePOINTER|eARRAY         , eVALUE|eSYMBOL         , ePOINTER|eARRAY|eVALUE|eSYMBOL );
    add_flag_test(ePOINTER|eARRAY         , eALL                   , eALL                           );
    add_flag_test(ePOINTER|eARRAY         , eNONE                  , ePOINTER|eARRAY                );
    
    add_flag_test(eLVALUE|ePOINTER|eARRAY , eALL                   , eALL                           );
    add_flag_test(eNONE                   , eALL                   , eALL                           );
    add_flag_test(eALL                    , eALL                   , eALL                           );
                                                                                                    
    add_flag_test(eLVALUE|ePOINTER|eARRAY , eNONE                  , eLVALUE|ePOINTER|eARRAY        );
    add_flag_test(eNONE                   , eNONE                  , eNONE                          );
    add_flag_test(eALL                    , eNONE                  , eALL                           );
    add_flag_test(eARRAY                  , ePOINTER|eARRAY        , ePOINTER|eARRAY                );
}

//==============================================================================
//==============================================================================
#endif // !dHAS_CPP11
#endif // !TEST_TOOLS_FLAG

