
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FLAG

#define dTEST_COMPONENT tools
#define dTEST_METHOD flag
#define dTEST_TAG synch_cpp98

#include <tools/flag.hpp>
namespace me = ::tools;
//==============================================================================
//==============================================================================
namespace
{
    enum eFLAGS 
    { 
        eNONE  = 0, 
        eALL   = 1, 
        eONE   = 1<<1, 
        eTWO   = 1<<2,
        eTHREE = 1<<3
    };
	typedef me::flag<eFLAGS> flag_t;

}//namespace

//==============================================================================
//==============================================================================

TEST_COMPONENT(000) 
{
}

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FLAG



