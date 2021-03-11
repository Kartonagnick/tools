// [2020y-12m-01d][14:06:17] Idrisov Denis R.
// [2021y-02m-20d][18:40:18] Idrisov Denis R.
// [2021y-03m-10d][06:14:37] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_CAST

#define dTEST_COMPONENT tools
#define dTEST_METHOD can_numeric_cast
#define dTEST_TAG cpp98

#include <tools/numeric_cast.hpp>
#include <tools/types/fixed.hpp>
#include "test-staff.hpp"

namespace me = ::tools;
//=================================================================================
//=== [constants] =================================================================
namespace
{
    template<class ret, class from>
    void test_can_cast(const char* msg, const from value,
        const bool etalon)
    {
        dASSERT(msg);
        const bool real 
            = me::can_numeric_cast<ret>(value);
        ASSERT_EQ(real, etalon)
            << msg << '\n'
            << "etalon = " << etalon << '\n'
            << "real = "   << real   << '\n'
        ;
    }

    #define test(ret, input, etalon)                   \
        test_can_cast<ret>(                            \
            "can_numeric_cast<" #ret ">(" #input "): " \
            "failed",                                  \
            input, etalon                              \
        )

} // namespace
using namespace test_can_numeric_cast;

//=================================================================================
//=== [same types] ================================================================
TEST_COMPONENT(000)
{
    //  |    type   |    input      | expected |
    test( int       , 10            ,  true    );
    test( int       , -1            ,  true    );
//............................................................
    test( int8_t    , int8_t(10)    ,  true    ); 
    test( int8_t    , int8_t(-1)    ,  true    );
    test( int16_t   , int16_t(10)   ,  true    ); 
    test( int16_t   , int16_t(-1)   ,  true    );
    test( int32_t   , int32_t(10)   ,  true    ); 
    test( int32_t   , int32_t(-1)   ,  true    );
    test( int64_t   , int64_t(10)   ,  true    ); 
    test( int64_t   , int64_t(-1)   ,  true    );
//............................................................
    test( int8_t    , int8_t(10)    ,  true    ); 
    test( int8_t    , int8_t(-1)    ,  true    );
    test( int16_t   , int16_t(10)   ,  true    ); 
    test( int16_t   , int16_t(-1)   ,  true    );
    test( int32_t   , int32_t(10)   ,  true    ); 
    test( int32_t   , int32_t(-1)   ,  true    );
    test( int64_t   , int64_t(10)   ,  true    ); 
    test( int64_t   , int64_t(-1)   ,  true    );
//............................................................
    test( uint8_t   , uint8_t(10)   ,  true    ); 
    test( uint8_t   , uint8_t(-1)   ,  true    );
    test( uint16_t  , uint16_t(10)  ,  true    ); 
    test( uint16_t  , uint16_t(-1)  ,  true    );
    test( uint32_t  , uint32_t(10)  ,  true    ); 
    test( uint32_t  , uint32_t(-1)  ,  true    );
    test( uint64_t  , uint64_t(10)  ,  true    ); 
    test( uint64_t  , uint64_t(-1)  ,  true    );
//............................................................
    test( uint8_t   , uint8_t(10)   ,  true    ); 
    test( uint8_t   , uint8_t(-1)   ,  true    );
    test( uint16_t  , uint16_t(10)  ,  true    ); 
    test( uint16_t  , uint16_t(-1)  ,  true    );
    test( uint32_t  , uint32_t(10)  ,  true    ); 
    test( uint32_t  , uint32_t(-1)  ,  true    );
    test( uint64_t  , uint64_t(10)  ,  true    ); 
    test( uint64_t  , uint64_t(-1)  ,  true    );
}

//=================================================================================
//=== [floating] ==================================================================
TEST_COMPONENT(001)
{
    //  |   ret-type    |      input        | expected |
    test( float         , 13.13f            ,  true    );
    test( double        , 13.13f            ,  true    );
    test( long double   , 13.13f            ,  true    );
    test( float         , 13.13             ,  false   );
    test( double        , 13.13             ,  true    );
    test( long double   , 13.13             ,  true    );
    test( float         , long_double       ,  false   );
    test( double        , long_double       ,  may_be  ); // implementation behavior
    test( long double   , long_double       ,  true    );
}

//=================================================================================
//=== [small -> big] ==============================================================
TEST_COMPONENT(002)
{
    // --- sizeof(from-unsigned) <= sizeof(to-unsigned)

    //  |    type       |      input        | expected |
    test( uint16_t , uint8_t(10)  ,  true    );
    test( uint16_t , uint8_t(-1)  ,  true    );
    test( uint16_t , uint8_t(0)   ,  true    );
    test( uint16_t , uint8max     ,  true    );
//.................................................................................
    test( uint32_t , uint8_t(10)  ,  true    );
    test( uint32_t , uint8_t(-1)  ,  true    );
    test( uint32_t , uint8_t(0)   ,  true    );
    test( uint32_t , uint8max     ,  true    );

    test( uint32_t , uint16_t(10) ,  true    );
    test( uint32_t , uint16_t(-1) ,  true    );
    test( uint32_t , uint16_t(0)  ,  true    );
    test( uint32_t , uint16max    ,  true    );
//.................................................................................
    test( uint64_t , uint8_t(10)  ,  true    );
    test( uint64_t , uint8_t(-1)  ,  true    );
    test( uint64_t , uint8_t(0)   ,  true    );
    test( uint64_t , uint8max     ,  true    );

    test( uint64_t , uint16_t(10) ,  true    );
    test( uint64_t , uint16_t(-1) ,  true    );
    test( uint64_t , uint16_t(0)  ,  true    );
    test( uint64_t , uint16max    ,  true    );

    test( uint64_t , uint32_t(10) ,  true    );
    test( uint64_t , uint32_t(-1) ,  true    );
    test( uint64_t , uint32_t(0)  ,  true    );
    test( uint64_t , uint32max    ,  true    );
}

//=================================================================================
//=== [big -> small] ==============================================================
TEST_COMPONENT(003)
{
    // --- sizeof(from-unsigned) > sizeof(to-unsigned)

    //  |   type   |     input    | expected |
    test( uint8_t  , uint16_t(0)  ,  true    );
    test( uint8_t  , uint16_t(10) ,  true    );
    test( uint8_t  , uint8maxPlus ,  false   );
//.................................................................................
    test( uint16_t , uint32_t(0)  ,  true    );
    test( uint16_t , uint32_t(10) ,  true    );
    test( uint16_t , uint16maxPlus,  false   );
//.................................................................................
    test( uint32_t , uint64_t(0)  ,  true    );
    test( uint32_t , uint64_t(10) ,  true    );
    test( uint32_t , uint32maxPlus,  false   );
}

//=================================================================================
//=== [from(unsigned) to signed] ==================================================
TEST_COMPONENT(004)
{
    // --- cast from 'unsigned' to 'signed'

    //  |  type    |    input     | expected |
    test( int8_t   , uint8_t(0)   ,  true    );
    test( int8_t   , uint8_t(10)  ,  true    );
    test( int8_t   , int8maxPlus  ,  false   );
    test( int8_t   , uint8maxPlus ,  false   );
//.................................................................................    
    test( int16_t  , uint8_t(0 )  ,  true    );
    test( int16_t  , uint8_t(10)  ,  true    );
    test( int16_t  , uint16_t(0)  ,  true    );
    test( int16_t  , uint16_t(10) ,  true    );
    test( int16_t  , int8maxPlus  ,  true    );
    test( int16_t  , uint8maxPlus ,  true    );
    test( int16_t  , int16maxPlus ,  false   );
    test( int16_t  , uint16maxPlus,  false   );
//.................................................................................
    test( int32_t  , uint8_t(0)   ,  true    );
    test( int32_t  , uint8_t(10)  ,  true    );
    test( int32_t  , uint16_t(0)  ,  true    );
    test( int32_t  , uint16_t(10) ,  true    );
    test( int32_t  , uint32_t(0)  ,  true    );
    test( int32_t  , uint32_t(10) ,  true    );
    test( int32_t  , int8maxPlus  ,  true    );
    test( int32_t  , int16maxPlus ,  true    );
    test( int32_t  , int32maxPlus ,  false   );
    test( int32_t  , uint8maxPlus ,  true    );
    test( int32_t  , uint16maxPlus,  true    );
    test( int32_t  , uint32maxPlus,  false   );
//.................................................................................
    test( int64_t  , uint8_t(0)   ,  true    );
    test( int64_t  , uint8_t(10)  ,  true    );
    test( int64_t  , uint16_t(0)  ,  true    );
    test( int64_t  , uint16_t(10) ,  true    );
    test( int64_t  , uint32_t(0)  ,  true    );
    test( int64_t  , uint32_t(10) ,  true    );
    test( int64_t  , int8maxPlus  ,  true    );
    test( int64_t  , int16maxPlus ,  true    );
    test( int64_t  , int32maxPlus ,  true    );
    test( int64_t  , uint8maxPlus ,  true    );
    test( int64_t  , uint16maxPlus,  true    );
    test( int64_t  , uint32maxPlus,  true    );
}

//=================================================================================
//=== [from(signed) to unsigned] ==================================================
TEST_COMPONENT(005)
{
    // --- cast from 'signed' to 'unsigned'

    //  |  type    |    input     | expected |
    test( uint8_t  , int8_t(-1)   ,  false   );
    test( uint8_t  , int8min      ,  false   );
    test( uint8_t  , int8_t(0)    ,  true    );
    test( uint8_t  , int8_t(10)   ,  true    );
    test( uint8_t  , int8max      ,  true    );
    test( uint8_t  , int8maxPlus  ,  true    );
    test( uint8_t  , int8minMinus ,  false   );
//.................................................................................
    test( uint8_t  , int16_t(-1)  ,  false   );
    test( uint8_t  , int16min     ,  false   );
    test( uint8_t  , int16_t(0)   ,  true    );
    test( uint8_t  , int16_t(10)  ,  true    );
    test( uint8_t  , int16max     ,  false   );
    test( uint8_t  , int16maxPlus ,  false   );
    test( uint8_t  , int16minMinus,  false   );
//.................................................................................
    test( uint8_t  , int32_t(-1)  ,  false   );
    test( uint8_t  , int32min     ,  false   );
    test( uint8_t  , int32_t(0)   ,  true    );
    test( uint8_t  , int32_t(10)  ,  true    );
    test( uint8_t  , int32max     ,  false   );
    test( uint8_t  , int32maxPlus ,  false   );
    test( uint8_t  , int32minMinus,  false   );
//.................................................................................
    test( uint8_t  , int64_t(-1)  ,  false   );
    test( uint8_t  , int64min     ,  false   );
    test( uint8_t  , int64_t(0)   ,  true    );
    test( uint8_t  , int64_t(10)  ,  true    );
    test( uint8_t  , int64max     ,  false   );
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
    test( uint16_t , int8_t(-1)   ,  false   );
    test( uint16_t , int8min      ,  false   );
    test( uint16_t , int8_t(0)    ,  true    );
    test( uint16_t , int8_t(10)   ,  true    );
    test( uint16_t , int8max      ,  true    );
    test( uint16_t , int8maxPlus  ,  true    );
    test( uint16_t , int8minMinus ,  false   );
//.................................................................................
    test( uint16_t , int16_t(-1)  ,  false   );
    test( uint16_t , int16min     ,  false   );
    test( uint16_t , int16_t(0)   ,  true    );
    test( uint16_t , int16_t(10)  ,  true    );
    test( uint16_t , int16max     ,  true    );
    test( uint16_t , int16maxPlus ,  true    );
    test( uint16_t , int16minMinus,  false   );
//.................................................................................
    test( uint16_t , int32_t(-1)  ,  false   );
    test( uint16_t , int32min     ,  false   );
    test( uint16_t , int32_t(0)   ,  true    );
    test( uint16_t , int32_t(10)  ,  true    );
    test( uint16_t , int32max     ,  false   );
    test( uint16_t , int32maxPlus ,  false   );
    test( uint16_t , int32minMinus,  false   );
//.................................................................................
    test( uint16_t , int64_t(-1)  ,  false   );
    test( uint16_t , int64min     ,  false   );
    test( uint16_t , int64_t(0)   ,  true    );
    test( uint16_t , int64_t(10)  ,  true    );
    test( uint16_t , int64max     ,  false   );
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
    test( uint32_t , int8_t(-1)   ,  false   );
    test( uint32_t , int8min      ,  false   );
    test( uint32_t , int8_t(0)    ,  true    );
    test( uint32_t , int8_t(10)   ,  true    );
    test( uint32_t , int8max      ,  true    );
    test( uint32_t , int8maxPlus  ,  true    );
    test( uint16_t , int8minMinus ,  false   );
//.................................................................................
    test( uint32_t , int16_t(-1)  ,  false   );
    test( uint32_t , int16min     ,  false   );
    test( uint32_t , int16_t(0)   ,  true    );
    test( uint32_t , int16_t(10)  ,  true    );
    test( uint32_t , int16max     ,  true    );
    test( uint32_t , int16maxPlus ,  true    );
    test( uint16_t , int16minMinus,  false   );
//.................................................................................
    test( uint32_t , int32_t(-1)  ,  false   );
    test( uint32_t , int32min     ,  false   );
    test( uint32_t , int32_t(0)   ,  true    );
    test( uint32_t , int32_t(10)  ,  true    );
    test( uint32_t , int32max     ,  true    );
    test( uint32_t , int32maxPlus ,  true    );
    test( uint16_t , int32minMinus,  false   );
//.................................................................................
    test( uint32_t , int64_t(-1)  ,  false   );
    test( uint32_t , int64min     ,  false   );
    test( uint32_t , int64_t(0)   ,  true    );
    test( uint32_t , int64_t(10)  ,  true    );
    test( uint32_t , int64max     ,  false   );
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
    test( uint64_t , int8_t(-1)   ,  false   );
    test( uint64_t , int8min      ,  false   );
    test( uint64_t , int8_t(0)    ,  true    );
    test( uint64_t , int8_t(10)   ,  true    );
    test( uint64_t , int8max      ,  true    );
    test( uint64_t , int8maxPlus  ,  true    );
    test( uint16_t , int8minMinus ,  false   );
//.................................................................................
    test( uint64_t , int16_t(-1)  ,  false   );
    test( uint64_t , int16min     ,  false   );
    test( uint64_t , int16_t(0)   ,  true    );
    test( uint64_t , int16_t(10)  ,  true    );
    test( uint64_t , int16max     ,  true    );
    test( uint64_t , int16maxPlus ,  true    );
    test( uint16_t , int16minMinus,  false   );
//.................................................................................
    test( uint64_t , int32_t(-1)  ,  false   );
    test( uint64_t , int32min     ,  false   );
    test( uint64_t , int32_t(0)   ,  true    );
    test( uint64_t , int32_t(10)  ,  true    );
    test( uint64_t , int32max     ,  true    );
    test( uint64_t , int32maxPlus ,  true    );
    test( uint16_t , int32minMinus,  false   );
//.................................................................................
    test( uint64_t , int64_t(-1)  ,  false   );
    test( uint64_t , int64min     ,  false   );
    test( uint64_t , int64_t(0)   ,  true    );
    test( uint64_t , int64_t(10)  ,  true    );
    test( uint64_t , int64max     ,  true    );
}

//=================================================================================
//=== [from(signed) to signed] ====================================================
TEST_COMPONENT(006)
{
    // --- cast from 'signed' to 'signed'

    //  |   type   |    input     | expected |
    test( int8_t   , int8_t(0)    ,  true    );
    test( int8_t   , int8_t(10)   ,  true    );
    test( int8_t   , int8_t(-1)   ,  true    );
    test( int8_t   , int8max      ,  true    );
    test( int8_t   , int8min      ,  true    );
    test( int8_t   , int8maxPlus  ,  false   );
    test( int8_t   , int8minMinus ,  false   );

    test( int8_t   , int16_t(0)   ,  true    );
    test( int8_t   , int16_t(10)  ,  true    );
    test( int8_t   , int16_t(-1)  ,  true    );
    test( int8_t   , int16max     ,  false   );
    test( int8_t   , int16min     ,  false   );
    test( int8_t   , int16maxPlus ,  false   );
    test( int8_t   , int16minMinus,  false   );

    test( int8_t   , int32_t(0)   ,  true    );
    test( int8_t   , int32_t(10)  ,  true    );
    test( int8_t   , int32_t(-1)  ,  true    );
    test( int8_t   , int32max     ,  false   );
    test( int8_t   , int32min     ,  false   );
    test( int8_t   , int32maxPlus ,  false   );
    test( int8_t   , int32minMinus,  false   );

    test( int8_t   , int64_t(0)   ,  true    );
    test( int8_t   , int64_t(10)  ,  true    );
    test( int8_t   , int64_t(-1)  ,  true    );
    test( int8_t   , int64max     ,  false   );
    test( int8_t   , int64min     ,  false   );
//.................................................................................
    test( int16_t  , int8_t(0)    ,  true    );
    test( int16_t  , int8_t(10)   ,  true    );
    test( int16_t  , int8_t(-1)   ,  true    );
    test( int16_t  , int8max      ,  true    );
    test( int16_t  , int8min      ,  true    );
    test( int16_t  , int8maxPlus  ,  true    );
    test( int16_t  , int8minMinus ,  true    );
                  
    test( int16_t  , int16_t(0)   ,  true    );
    test( int16_t  , int16_t(10)  ,  true    );
    test( int16_t  , int16_t(-1)  ,  true    );
    test( int16_t  , int16max     ,  true    );
    test( int16_t  , int16min     ,  true    );
    test( int16_t  , int16maxPlus ,  false   );
    test( int16_t  , int16minMinus,  false   );
                  
    test( int16_t  , int32_t(0)   ,  true    );
    test( int16_t  , int32_t(10)  ,  true    );
    test( int16_t  , int32_t(-1)  ,  true    );
    test( int16_t  , int32max     ,  false   );
    test( int16_t  , int32min     ,  false   );
    test( int16_t  , int32maxPlus ,  false   );
    test( int16_t  , int32minMinus,  false   );
                  
    test( int16_t  , int64_t(0)   ,  true    );
    test( int16_t  , int64_t(10)  ,  true    );
    test( int16_t  , int64_t(-1)  ,  true    );
    test( int16_t  , int64max     ,  false   );
    test( int16_t  , int64min     ,  false   );
//.................................................................................
    test( int32_t  , int8_t(0)    ,  true    );
    test( int32_t  , int8_t(10)   ,  true    );
    test( int32_t  , int8_t(-1)   ,  true    );
    test( int32_t  , int8max      ,  true    );
    test( int32_t  , int8min      ,  true    );
    test( int32_t  , int8maxPlus  ,  true    );
    test( int32_t  , int8minMinus ,  true    );
                  
    test( int32_t  , int16_t(0)   ,  true    );
    test( int32_t  , int16_t(10)  ,  true    );
    test( int32_t  , int16_t(-1)  ,  true    );
    test( int32_t  , int16max     ,  true    );
    test( int32_t  , int16min     ,  true    );
    test( int32_t  , int16maxPlus ,  true    );
    test( int32_t  , int16minMinus,  true    );
                  
    test( int32_t  , int32_t(0)   ,  true    );
    test( int32_t  , int32_t(10)  ,  true    );
    test( int32_t  , int32_t(-1)  ,  true    );
    test( int32_t  , int32max     ,  true    );
    test( int32_t  , int32min     ,  true    );
    test( int32_t  , int32maxPlus ,  false   );
    test( int32_t  , int32minMinus,  false   );
                  
    test( int32_t  , int64_t(0)   ,  true    );
    test( int32_t  , int64_t(10)  ,  true    );
    test( int32_t  , int64_t(-1)  ,  true    );
    test( int32_t  , int64max     ,  false   );
    test( int32_t  , int64min     ,  false   );
//.................................................................................
    test( int64_t  , int8_t(0)    ,  true    );
    test( int64_t  , int8_t(10)   ,  true    );
    test( int64_t  , int8_t(-1)   ,  true    );
    test( int64_t  , int8max      ,  true    );
    test( int64_t  , int8min      ,  true    );
    test( int64_t  , int8maxPlus  ,  true    );
    test( int64_t  , int8minMinus ,  true    );
                  
    test( int64_t  , int16_t(0)   ,  true    );
    test( int64_t  , int16_t(10)  ,  true    );
    test( int64_t  , int16_t(-1)  ,  true    );
    test( int64_t  , int16max     ,  true    );
    test( int64_t  , int16min     ,  true    );
    test( int64_t  , int16maxPlus ,  true    );
    test( int64_t  , int16minMinus,  true    );
                  
    test( int64_t  , int32_t(0)   ,  true    );
    test( int64_t  , int32_t(10)  ,  true    );
    test( int64_t  , int32_t(-1)  ,  true    );
    test( int64_t  , int32max     ,  true    );
    test( int64_t  , int32min     ,  true    );
    test( int64_t  , int32maxPlus ,  true    );
    test( int64_t  , int32minMinus,  true    );
                  
    test( int64_t  , int64_t(0)   ,  true    );
    test( int64_t  , int64_t(10)  ,  true    );
    test( int64_t  , int64_t(-1)  ,  true    );
    test( int64_t  , int64max     ,  true    );
    test( int64_t  , int64min     ,  true    );
}

//=================================================================================
//=== [enumerations types] ========================================================
#ifdef dHAS_ENUM_CLASS
TEST_COMPONENT(007)
{
    enum class u_enum : unsigned char { eONE = 128 };
    enum class s_enum : signed   char { eSIG = 125 };

    typedef signed char
        s_char_t;

    typedef unsigned char
        u_char_t;

    //  |  type    |      input      | expected |
//................................................................................. signed
    test( s_enum   , s_enum::eSIG    ,   true   );
    test( s_enum   ,      125        ,   true   );
    test( s_enum   , unsigned(125)   ,   true   );
    test(  int     , s_enum::eSIG    ,   true   );
//................................................................................. unsigned
    test( u_enum   , u_enum::eONE    ,   true   );
    test( u_enum   , unsigned(128)   ,   true   );
    test( u_enum   ,      128        ,   true   );
    test( unsigned , u_enum::eONE    ,   true   );
//.................................................................................
    test( s_char_t ,  u_enum::eONE   ,   false  ); 
    test( s_char_t ,  u_char_t(128)  ,   false  ); 
    test( s_enum   ,  u_char_t(128)  ,   false  );
    test( s_enum   ,  u_enum::eONE   ,   false  );
    test( u_char_t ,  u_enum::eONE   ,   true   );
    test( u_char_t ,  s_enum::eSIG   ,   true   );
    test( u_enum   ,  u_enum::eONE   ,   true   );
    test( u_enum   ,  s_enum::eSIG   ,   true   );
}
#endif // !dHAS_ENUM_CLASS

//=================================================================================
//=================================================================================
#endif // !TEST_TOOLS_CAST
