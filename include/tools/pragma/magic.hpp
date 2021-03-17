
// [2019y-04m-12d] Idrisov Denis R.
// NOTE: without unit-test
//==============================================================================
//==============================================================================

#pragma once
#ifndef dTOOLS_PRAGMA_MAGIC_USED_ 
#define dTOOLS_PRAGMA_MAGIC_USED_ 1

//==============================================================================
//==============================================================================

#define dSTRINGIFY_(a) #a
#define dSTRINGIFY(a) dSTRINGIFY_(a)

#if defined(__GNUC__) || defined(__MINGW__) || defined(__MINGW32__)
    #define dMAGIC(x) _Pragma(dSTRINGIFY_(message #x)) x

#elif defined(_MSC_VER)
    #define dMAGIC(x) __pragma(message(dSTRINGIFY_(x))) x

#else
     #error: compiler not support
#endif

//==============================================================================
//==============================================================================
        
#if 0

// USAGE:
        
#include <iostream>

using namespace std;
 
int main()
{
    cout<<"begin programm\n";
    int Fedya = 40;
    dMAGIC(cout << "Fedya = " << Fedya << endl);
}

#endif

//==============================================================================
//==============================================================================

#endif //!dTOOLS_PRAGMA_MAGIC_USED_