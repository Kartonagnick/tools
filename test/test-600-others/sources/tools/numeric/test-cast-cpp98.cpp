
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_NUMERIC

#define dTEST_COMPONENT tools, numeric
#define dTEST_METHOD cast
#define dTEST_TAG cpp98

#include <tools/numeric.hpp>
#include <tools/types/fixed.hpp>
#include "test-staff.hpp"

namespace ut = ::tools;
namespace me = ut::numeric;
//=================================================================================
//=================================================================================
namespace
{
    #define dINVALID(ret, value) \
        ASSERT_THROW(me::cast<ret>(value), ::std::exception)

    #ifdef dHAS_ENUM_CLASS
    template<class t> 
    typename ut::type_of_enum<t>::type adopt(const t v)
    {
        typedef typename ut::type_of_enum<t>::type x;
        return static_cast<x>(v);
    }
    #else
    template<class t> t adopt(const t v)
        { return v; }
    #endif

    template<class ret, class from>
    void test_can_cast(const char* msg, const from value,
        const ret etalon)
    {
        dASSERT(msg);
        const ret real = me::cast<ret>(value);
        ASSERT_EQ(real, etalon)
            << msg << '\n'
            << "etalon = " << adopt(etalon) << '\n'
            << "real = "   << adopt(real)   << '\n'
        ;
    }

    #define test(ret, input, etalon)               \
        test_can_cast<ret>(                        \
            "numeric_cast<" #ret ">(" #input "): " \
            "failed",                              \
            input, etalon                          \
        )

} // namespace
using namespace test_can_numeric_cast;

//=================================================================================
//=== [floating] ==================================================================
TEST_COMPONENT(000)
{
    //  |    type       |      input  |   expected   |
    test( float         , 13.13f      , 13.13f       );
    test( double        , 13.13f      , 13.13f       );
    test( long double   , 13.13f      , 13.13f       );
    test( double        , 13.13       , 13.13        );
    test( long double   , 13.13       , 13.13        );
    test( long double   , long_double , long_double  );

} // namespace

//=================================================================================
//=== [same types] ================================================================
TEST_COMPONENT(001)
{
    //  | type     |     input    |    expected   |
    test( int      ,      10      ,      10       );
    test( int      ,      -1      ,      -1       );
//..................................................................
    test( int8_t   , int8_t(10)   ,  int8_t(10)   ); 
    test( int8_t   , int8_t(-1)   ,  int8_t(-1)   );
    test( int16_t  , int16_t(10)  ,  int16_t(10)  ); 
    test( int16_t  , int16_t(-1)  ,  int16_t(-1)  );
    test( int32_t  , int32_t(10)  ,  int32_t(10)  ); 
    test( int32_t  , int32_t(-1)  ,  int32_t(-1)  );
    test( int64_t  , int64_t(10)  ,  int64_t(10)  ); 
    test( int64_t  , int64_t(-1)  ,  int64_t(-1)  );
//..................................................................
    test( int8_t   , int8_t(10)   ,  int8_t(10)   ); 
    test( int8_t   , int8_t(-1)   ,  int8_t(-1)   );
    test( int16_t  , int16_t(10)  ,  int16_t(10)  ); 
    test( int16_t  , int16_t(-1)  ,  int16_t(-1)  );
    test( int32_t  , int32_t(10)  ,  int32_t(10)  ); 
    test( int32_t  , int32_t(-1)  ,  int32_t(-1)  );
    test( int64_t  , int64_t(10)  ,  int64_t(10)  ); 
    test( int64_t  , int64_t(-1)  ,  int64_t(-1)  );
//..................................................................
    test( uint8_t  , uint8_t(10)  ,  uint8_t(10)  ); 
    test( uint8_t  , uint8_t(-1)  ,  uint8_t (-1) );
    test( uint16_t , uint16_t(10) ,  uint16_t(10) ); 
    test( uint16_t , uint16_t(-1) ,  uint16_t(-1) );
    test( uint32_t , uint32_t(10) ,  uint32_t(10) ); 
    test( uint32_t , uint32_t(-1) ,  uint32_t(-1) );
    test( uint64_t , uint64_t(10) ,  uint64_t(10) ); 
    test( uint64_t , uint64_t(-1) ,  uint64_t(-1) );
//..................................................................
    test( uint8_t  , uint8_t(10)  ,  uint8_t(10)  ); 
    test( uint8_t  , uint8_t(-1)  ,  uint8_t(-1)  );
    test( uint16_t , uint16_t(10) ,  uint16_t(10) ); 
    test( uint16_t , uint16_t(-1) ,  uint16_t(-1) );
    test( uint32_t , uint32_t(10) ,  uint32_t(10) ); 
    test( uint32_t , uint32_t(-1) ,  uint32_t(-1) );
    test( uint64_t , uint64_t(10) ,  uint64_t(10) ); 
    test( uint64_t , uint64_t(-1) ,  uint64_t(-1) );

} // namespace

//=================================================================================
//=== [from-unsigned < to-unsigned] ===============================================
TEST_COMPONENT(002)
{
    // --- sizeof(from-unsigned) <= sizeof(to-unsigned)

    //  |  type    |    input     |       expected      |
    test( uint16_t , uint8_t(10)  , uint16_t(10)        );
    test( uint16_t , uint8_t(-1)  , uint16_t(uint8max)  );
    test( uint16_t , uint8_t(0)   , uint16_t(0)         );
    test( uint16_t , uint8max     , uint16_t(uint8max)  );
//.................................................................................
    test( uint32_t , uint8_t(10)  , uint32_t(10)        );
    test( uint32_t , uint8_t(-1)  , uint32_t(uint8max)  );
    test( uint32_t , uint8_t(0)   , uint32_t(0)         );
    test( uint32_t , uint8max     , uint32_t(uint8max)  );

    test( uint32_t , uint16_t(10) , uint32_t(10)        );
    test( uint32_t , uint16_t(-1) , uint32_t(uint16max) );
    test( uint32_t , uint16_t(0)  , uint32_t(0)         );
    test( uint32_t , uint16max    , uint32_t(uint16max) );
//.................................................................................
    test( uint64_t , uint8_t(10)  , uint64_t(10)        );
    test( uint64_t , uint8_t(-1)  , uint64_t(uint8max)  );
    test( uint64_t , uint8_t(0)   , uint64_t(0)         );
    test( uint64_t , uint8max     , uint64_t(uint8max)  );

    test( uint64_t , uint16_t(10) , uint64_t(10)        );
    test( uint64_t , uint16_t(-1) , uint64_t(uint16max) );
    test( uint64_t , uint16_t(0)  , uint64_t(0)         );
    test( uint64_t , uint16max    , uint64_t(uint16max) );

    test( uint64_t , uint32_t(10) , uint64_t(10)        );
    test( uint64_t , uint32_t(-1) , uint64_t(uint32max) );
    test( uint64_t , uint32_t(0)  , uint64_t(0)         );
    test( uint64_t , uint32max    , uint64_t(uint32max) );

} // namespace

//=================================================================================
//=== [from-unsigned > to-unsigned] ===============================================
TEST_COMPONENT(003)
{
    // --- sizeof(from-unsigned) > sizeof(to-unsigned)

    //  |  type    |     input    |    expected  |
    test( uint8_t  , uint16_t(0)  , uint8_t(0)   );
    test( uint8_t  , uint16_t(10) , uint8_t(10)  );
//.................................................................................
    test( uint16_t , uint32_t(0)  , uint16_t(0)  );
    test( uint16_t , uint32_t(10) , uint16_t(10) );
//.................................................................................
    test( uint32_t , uint64_t(0)  , uint32_t(0)  );
    test( uint32_t , uint64_t(10) , uint32_t(10) );

} // namespace

//=================================================================================
//=== [from(unsigned) to signed] ==================================================
TEST_COMPONENT(004)
{
    // --- cast from 'unsigned' to 'signed'

    //  |  type    |    input     |         expected       |
    test( int8_t   , uint8_t(0)   ,  int8_t(0)             );
    test( int8_t   , uint8_t(10)  ,  int8_t(10)            );
//.................................................................................    
    test( int16_t  , uint8_t(0 )  ,  int16_t(0)            );
    test( int16_t  , uint8_t(10)  ,  int16_t(10)           );
    test( int16_t  , uint16_t(0)  ,  int16_t(0)            );
    test( int16_t  , uint16_t(10) ,  int16_t(10)           );
    test( int16_t  , int8maxPlus  ,  int16_t(int8maxPlus)  );
//.................................................................................
    test( int32_t  , uint8_t(0)   ,  int32_t(0)            );
    test( int32_t  , uint8_t(10)  ,  int32_t(10)           );
    test( int32_t  , uint16_t(0)  ,  int32_t(0)            );
    test( int32_t  , uint16_t(10) ,  int32_t(10)           );
    test( int32_t  , uint32_t(0)  ,  int32_t(0)            );
    test( int32_t  , uint32_t(10) ,  int32_t(10)           );
    test( int32_t  , int8maxPlus  ,  int32_t(int8maxPlus)  );
    test( int32_t  , int16maxPlus ,  int32_t(int16maxPlus) );
//.................................................................................
    test( int64_t  , uint8_t(0)   ,  int64_t(0)            );
    test( int64_t  , uint8_t(10)  ,  int64_t(10)           );
    test( int64_t  , uint16_t(0)  ,  int64_t(0)            );
    test( int64_t  , uint16_t(10) ,  int64_t(10)           );
    test( int64_t  , uint32_t(0)  ,  int64_t(0)            );
    test( int64_t  , uint32_t(10) ,  int64_t(10)           );
    test( int64_t  , int8maxPlus  ,  int64_t(int8maxPlus)  );
    test( int64_t  , int16maxPlus ,  int64_t(int16maxPlus) );
    test( int64_t  , int32maxPlus ,  int64_t(int32maxPlus) );

} // namespace

//=================================================================================
//=== [from(signed) to unsigned] ==================================================
TEST_COMPONENT(005)
{
    // --- cast from 'signed' to 'unsigned'

    //  |    type       |      input       | expected |
    test( uint8_t  , int8_t(0)   ,  uint8_t(0)             );
    test( uint8_t  , int8_t(10)  ,  uint8_t(10)            );
    test( uint8_t  , int8max     ,  uint8_t(int8max)       );
    test( uint8_t  , int8maxPlus ,  uint8_t(int8maxPlus)   );

    test( uint8_t  , int16_t(0)  ,  uint8_t(0)             );
    test( uint8_t  , int16_t(10) ,  uint8_t(10)            );
                                                                          
    test( uint8_t  , int32_t(0)  ,  uint8_t(0)             );
    test( uint8_t  , int32_t(10) ,  uint8_t(10)            );
                                                                          
    test( uint8_t  , int64_t(0)  ,  uint8_t(0)             );
    test( uint8_t  , int64_t(10) ,  uint8_t(10)            );
//---------------------------------------------------------------------------------
    test( uint16_t , int8_t(0)   ,  uint16_t(0)            );
    test( uint16_t , int8_t(10)  ,  uint16_t(10)           );
    test( uint16_t , int8max     ,  uint16_t(int8max)      );
    test( uint16_t , int8maxPlus ,  uint16_t(int8maxPlus)  );

    test( uint16_t , int16_t(0)  ,  uint16_t(0)            );
    test( uint16_t , int16_t(10) ,  uint16_t(10)           );
    test( uint16_t , int16max    ,  uint16_t(int16max)     );
    test( uint16_t , int16maxPlus,  uint16_t(int16maxPlus) );

    test( uint16_t , int32_t(0)  ,  uint16_t(0)            );
    test( uint16_t , int32_t(10) ,  uint16_t(10)           );
                                                                          
    test( uint16_t , int64_t(0)  ,  uint16_t(0)            );
    test( uint16_t , int64_t(10) ,  uint16_t(10)           );
//---------------------------------------------------------------------------------
    test( uint32_t , int8_t(0)   ,  uint32_t(0)            );
    test( uint32_t , int8_t(10)  ,  uint32_t(10)           );
    test( uint32_t , int8max     ,  uint32_t(int8max)      );
    test( uint32_t , int8maxPlus ,  uint32_t(int8maxPlus)  );

    test( uint32_t , int16_t(0)  ,  uint32_t(0)            );
    test( uint32_t , int16_t(10) ,  uint32_t(10)           );
    test( uint32_t , int16max    ,  uint32_t(int16max)     );
    test( uint32_t , int16maxPlus,  uint32_t(int16maxPlus) );

    test( uint32_t , int32_t(0)  ,  uint32_t(0)            );
    test( uint32_t , int32_t(10) ,  uint32_t(10)           );
    test( uint32_t , int32max    ,  uint32_t(int32max)     );
    test( uint32_t , int32maxPlus,  uint32_t(int32maxPlus) );

    test( uint32_t , int64_t(0)  ,  uint32_t(0)            );
    test( uint32_t , int64_t(10) ,  uint32_t(10)           );
//---------------------------------------------------------------------------------
    test( uint64_t , int8_t(0)   ,  uint64_t(0)            );
    test( uint64_t , int8_t(10)  ,  uint64_t(10)           );
    test( uint64_t , int8max     ,  uint64_t(int8max)      );
    test( uint64_t , int8maxPlus ,  uint64_t(int8maxPlus)  );

    test( uint64_t , int16_t(0)  ,  uint64_t(0)            );
    test( uint64_t , int16_t(10) ,  uint64_t(10)           );
    test( uint64_t , int16max    ,  uint64_t(int16max)     );
    test( uint64_t , int16maxPlus,  uint64_t(int16maxPlus) );

    test( uint64_t , int32_t(0)  ,  uint64_t(0)            );
    test( uint64_t , int32_t(10) ,  uint64_t(10)           );
    test( uint64_t , int32max    ,  uint64_t(int32max)     );
    test( uint64_t , int32maxPlus,  uint64_t(int32maxPlus) );

    test( uint64_t , int64_t(0)  ,  uint64_t(0)            );
    test( uint64_t , int64_t(10) ,  uint64_t(10)           );
    test( uint64_t , int64max    ,  uint64_t(int64max)     );

} // namespace

//=================================================================================
//=== [from(signed) to signed] ====================================================
TEST_COMPONENT(006)
{
    // --- cast from 'signed' to 'signed'

    //  |  type   |     input    |        expected         |
    test( int8_t  , int8_t(0)    ,  int8_t(0)              );
    test( int8_t  , int8_t(10)   ,  int8_t(10)             );
    test( int8_t  , int8_t(-1)   ,  int8_t(-1)             );
    test( int8_t  , int8max      ,  int8_t(int8max)        );
    test( int8_t  , int8min      ,  int8_t(int8min)        );
                                           
    test( int8_t  , int16_t(0)   ,  int8_t(0)              );
    test( int8_t  , int16_t(10)  ,  int8_t(10)             );
    test( int8_t  , int16_t(-1)  ,  int8_t(-1)             );
                                                                          
    test( int8_t  , int32_t(0)   ,  int8_t(0)              );
    test( int8_t  , int32_t(10)  ,  int8_t(10)             );
    test( int8_t  , int32_t(-1)  ,  int8_t(-1)             );
                                                                          
    test( int8_t  , int64_t(0)   ,  int8_t(0)              );
    test( int8_t  , int64_t(10)  ,  int8_t(10)             );
    test( int8_t  , int64_t(-1)  ,  int8_t(-1)             );
//.................................................................................
    test( int16_t , int8_t(0)    ,  int16_t(0)             );
    test( int16_t , int8_t(10)   ,  int16_t(10)            );
    test( int16_t , int8_t(-1)   ,  int16_t(-1)            );
    test( int16_t , int8max      ,  int16_t(int8max)       );
    test( int16_t , int8min      ,  int16_t(int8min)       );
    test( int16_t , int8maxPlus  ,  int16_t(int8maxPlus)   );
    test( int16_t , int8minMinus ,  int16_t(int8minMinus)  );
                                 
    test( int16_t , int16_t(0)   ,  int16_t(0)             );
    test( int16_t , int16_t(10)  ,  int16_t(10)            );
    test( int16_t , int16_t(-1)  ,  int16_t(-1)            );
    test( int16_t , int16max     ,  int16_t(int16max)      );
    test( int16_t , int16min     ,  int16_t(int16min)      );
                                 
    test( int16_t , int32_t(0)   ,  int16_t(0)             );
    test( int16_t , int32_t(10)  ,  int16_t(10)            );
    test( int16_t , int32_t(-1)  ,  int16_t(-1)            );
                                                                          
    test( int16_t , int64_t(0)   ,  int16_t(0)             );
    test( int16_t , int64_t(10)  ,  int16_t(10)            );
    test( int16_t , int64_t(-1)  ,  int16_t (-1)           );
//.................................................................................
    test( int32_t , int8_t(0)    ,  int32_t(0)             );
    test( int32_t , int8_t(10)   ,  int32_t(10)            );
    test( int32_t , int8_t(-1)   ,  int32_t(-1)            );
    test( int32_t , int8max      ,  int32_t(int8max)       );
    test( int32_t , int8min      ,  int32_t(int8min)       );
    test( int32_t , int8maxPlus  ,  int32_t(int8maxPlus)   );
    test( int32_t , int8minMinus ,  int32_t(int8minMinus)  );
                  
    test( int32_t , int16_t(0)   ,  int32_t(0)             );
    test( int32_t , int16_t(10)  ,  int32_t(10)            );
    test( int32_t , int16_t(-1)  ,  int32_t(-1)            );
    test( int32_t , int16max     ,  int32_t(int16max)      );
    test( int32_t , int16min     ,  int32_t(int16min)      );
    test( int32_t , int16maxPlus ,  int32_t(int16maxPlus)  );
    test( int32_t , int16minMinus,  int32_t(int16minMinus) );
                  
    test( int32_t , int32_t(0)   ,  int32_t(0)             );
    test( int32_t , int32_t(10)  ,  int32_t(10)            );
    test( int32_t , int32_t(-1)  ,  int32_t(-1)            );
    test( int32_t , int32max     ,  int32_t(int32max)      );
    test( int32_t , int32min     ,  int32_t(int32min)      );
                                                                          
    test( int32_t , int64_t(0)   ,  int32_t(0)             );
    test( int32_t , int64_t(10)  ,  int32_t(10)            );
    test( int32_t , int64_t(-1)  ,  int32_t(-1)            );
//.................................................................................
    test( int64_t , int8_t(0)    ,  int64_t(0)             );
    test( int64_t , int8_t(10)   ,  int64_t(10)            );
    test( int64_t , int8_t(-1)   ,  int64_t(-1)            );
    test( int64_t , int8max      ,  int64_t(int8max)       );
    test( int64_t , int8min      ,  int64_t(int8min)       );
    test( int64_t , int8maxPlus  ,  int64_t(int8maxPlus)   );
    test( int64_t , int8minMinus ,  int64_t(int8minMinus)  );
                  
    test( int64_t , int16_t(0)   ,  int64_t(0)             );
    test( int64_t , int16_t(10)  ,  int64_t(10)            );
    test( int64_t , int16_t(-1)  ,  int64_t(-1)            );
    test( int64_t , int16max     ,  int64_t(int16max)      );
    test( int64_t , int16min     ,  int64_t(int16min)      );
    test( int64_t , int16maxPlus ,  int64_t(int16maxPlus)  );
    test( int64_t , int16minMinus,  int64_t(int16minMinus) );
                  
    test( int64_t , int32_t(0)   ,  int64_t(0)             );
    test( int64_t , int32_t(10)  ,  int64_t(10)            );
    test( int64_t , int32_t(-1)  ,  int64_t(-1)            );
    test( int64_t , int32max     ,  int64_t(int32max)      );
    test( int64_t , int32min     ,  int64_t(int32min)      );
    test( int64_t , int32maxPlus ,  int64_t(int32maxPlus)  );
    test( int64_t , int32minMinus,  int64_t(int32minMinus) );
                  
    test( int64_t , int64_t(0)   ,  int64_t(0)             );
    test( int64_t , int64_t(10)  ,  int64_t(10)            );
    test( int64_t , int64_t(-1)  ,  int64_t(-1)            );
    test( int64_t , int64max     ,  int64_t(int64max)      );
    test( int64_t , int64min     ,  int64_t(int64min)      );

} // namespace

//=================================================================================
//=== [enumerations types] ========================================================
#if defined(dHAS_ENUM_CLASS) && !defined(NDEBUG)
TEST_COMPONENT(007)
{
    enum class u_enum : unsigned char { eONE = 128 };
    enum class s_enum : signed   char { eSIG = 125 };

    /*
    typedef signed char 
        s_char_t;
    */

    typedef unsigned char 
        u_char_t;

    //  |  type    |      input      |    expected     |
//................................................................................. signed
    test( s_enum   , s_enum::eSIG    , s_enum::eSIG    );
    test( s_enum   ,      125        , s_enum::eSIG    );
    test( s_enum   , unsigned(125)   , s_enum::eSIG    );
    test(  int     , s_enum::eSIG    ,      125        );
//................................................................................. unsigned
    test( u_enum   , u_enum::eONE    , u_enum::eONE    );
    test( u_enum   , unsigned(128)   , u_enum::eONE    );
    test( u_enum   ,      128        , u_enum::eONE    );
    test( unsigned , u_enum::eONE    , unsigned(128)   );
//.................................................................................
  //test( s_char_t ,  u_enum::eONE   , s_char_t(128)   );  // <--- safety compile time 
    test( u_char_t ,  u_enum::eONE   , u_char_t(128)   );

} // namespace
#endif // !dHAS_ENUM_CLASS
//=================================================================================
//=================================================================================

// [floating]
TEST_COMPONENT(008)
{
    ASSERT_THROW(me::cast<float>(13.13) , ::std::exception);
    ASSERT_THROW(me::cast<float>(13.13l), ::std::exception);
    bool check = !may_be;

    // implementation behavior
    if(check)
    {
        ASSERT_THROW(
            me::cast<double>(13.13l),
            ::std::exception
        );
    }
}

// [from-unsigned > to-unsigned]
TEST_COMPONENT(009)
{
    //      |   ret   |     value     |
    dINVALID(uint8_t  , uint8maxPlus  );
    dINVALID(uint16_t , uint16maxPlus );
    dINVALID(uint32_t , uint32maxPlus );
}

// [from(unsigned) to signed]
TEST_COMPONENT(010)
{
    //      |   ret   |     value     |
    dINVALID(int8_t   , uint8maxPlus  );
    dINVALID(int16_t  , uint16maxPlus );
    dINVALID(int32_t  , uint32maxPlus );
}

//=================================================================================
//=================================================================================

// [uint8_t][from(signed) to unsigned]
TEST_COMPONENT(011)
{
    //      |   ret   |       value      |
    dINVALID(uint8_t  , int8_t(-1)       );
    dINVALID(uint8_t  , int8min          );
    dINVALID(uint8_t  , int8minMinus     );
//.................................................................................
    dINVALID(uint8_t  , int16_t(-1)      );
    dINVALID(uint8_t  , int16min         );
    dINVALID(uint8_t  , int16max         );
    dINVALID(uint8_t  , int16maxPlus     );
    dINVALID(uint8_t  , int16minMinus    );
//.................................................................................
    dINVALID(uint8_t  , int32_t(-1)      );
    dINVALID(uint8_t  , int32min         );
    dINVALID(uint8_t  , int32max         );
    dINVALID(uint8_t  , int32maxPlus     );
    dINVALID(uint8_t  , int32minMinus    );
//.................................................................................
    dINVALID(uint8_t  , int64_t(-1)      );
    dINVALID(uint8_t  , int64min         );
    dINVALID(uint8_t  , int64max         );
}

// [uint16_t][from(signed) to unsigned]
TEST_COMPONENT(012)
{
    //      |   ret    |       value   |
    dINVALID(uint16_t  , int8_t(-1)    );
    dINVALID(uint16_t  , int8min       );
    dINVALID(uint16_t  , int8minMinus  );
//.................................................................................
    dINVALID(uint16_t  , int16_t(-1)   );
    dINVALID(uint16_t  , int16min      );
    dINVALID(uint16_t  , int16minMinus );
//.................................................................................
    dINVALID(uint16_t  , int32_t(-1)   );
    dINVALID(uint16_t  , int32min      );
    dINVALID(uint16_t  , int32max      );
    dINVALID(uint16_t  , int32maxPlus  );
    dINVALID(uint16_t  , int32minMinus );
//.................................................................................
    dINVALID(uint16_t  , int64_t(-1)   );
    dINVALID(uint16_t  , int64min      );
    dINVALID(uint16_t  , int64max      );
}

// [uint32_t][from(signed) to unsigned]
TEST_COMPONENT(013)
{
    //      |   ret   |     value     |
    dINVALID(uint32_t , int8_t(-1)    );
    dINVALID(uint32_t , int8min       );
    dINVALID(uint16_t , int8minMinus  );
//.................................................................................
    dINVALID(uint32_t , int16_t(-1)   );
    dINVALID(uint32_t , int16min      );
    dINVALID(uint16_t , int16minMinus );
//.................................................................................
    dINVALID(uint32_t , int32_t(-1)   );
    dINVALID(uint32_t , int32min      );
    dINVALID(uint16_t , int32minMinus );
//.................................................................................
    dINVALID(uint32_t , int64_t(-1)   );
    dINVALID(uint32_t , int64min      );
    dINVALID(uint32_t , int64max      );
}

// [uint64_t][from(signed) to unsigned]
TEST_COMPONENT(014)
{
    //      |   ret   |       value   |
    dINVALID(uint64_t , int8_t(-1)    );
    dINVALID(uint64_t , int8min       );
    dINVALID(uint16_t , int8minMinus  );
//.................................................................................
    dINVALID(uint64_t , int16_t(-1)   );
    dINVALID(uint64_t , int16min      );
    dINVALID(uint16_t , int16minMinus );
//.................................................................................
    dINVALID(uint64_t , int32_t(-1)   );
    dINVALID(uint64_t , int32min      );
    dINVALID(uint16_t , int32minMinus );
//.................................................................................
    dINVALID(uint64_t , int64_t(-1)   );
    dINVALID(uint64_t , int64min      );
}

//=================================================================================
//=================================================================================

// [uint8_t][from(signed) to signed]
TEST_COMPONENT(015)
{
    //      |   ret  |     value     |
    dINVALID( int8_t , int8maxPlus   );
    dINVALID( int8_t , int8minMinus  );
//.................................................................................
    dINVALID( int8_t , int16max      );
    dINVALID( int8_t , int16min      );
    dINVALID( int8_t , int16maxPlus  );
    dINVALID( int8_t , int16minMinus );
//.................................................................................
    dINVALID( int8_t , int32max      );
    dINVALID( int8_t , int32min      );
    dINVALID( int8_t , int32maxPlus  );
    dINVALID( int8_t , int32minMinus );
//.................................................................................
    dINVALID( int8_t , int64max      );
    dINVALID( int8_t , int64min      );
}

// [uint16_t][from(signed) to signed]
TEST_COMPONENT(016)
{
    //      |   ret   |     value     |
    dINVALID( int16_t , int16maxPlus  );
    dINVALID( int16_t , int16minMinus );
//.................................................................................
    dINVALID( int16_t , int32max      );
    dINVALID( int16_t , int32min      );
    dINVALID( int16_t , int32maxPlus  );
    dINVALID( int16_t , int32minMinus );
//.................................................................................
    dINVALID( int16_t , int64max      );
    dINVALID( int16_t , int64min      );
}

// [uint32_t][from(signed) to signed]
TEST_COMPONENT(017)
{
    //      |   ret   |     value     |
    dINVALID( int32_t , int32maxPlus  );
    dINVALID( int32_t , int32minMinus );
//.................................................................................
    dINVALID( int32_t , int64max      );
    dINVALID( int32_t , int64min      );
}

// [enumeration]
#ifdef dHAS_ENUM_CLASS
TEST_COMPONENT(018)
{
    enum class u_enum : unsigned char { eONE = 128 };
    enum class s_enum : signed   char { eSIG = 125 };

    typedef signed char
        s_char_t;

    typedef unsigned char
        u_char_t;

    //      | ret-type |     value     |
    dINVALID( s_char_t , u_enum::eONE  );
    dINVALID( s_enum   , u_char_t(128) );
    dINVALID( s_enum   , u_enum::eONE  );
}
#endif

//=================================================================================
//=================================================================================
#endif // !TEST_TOOLS_NUMERIC
