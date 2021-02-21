
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ created: 2019y-10m-24d 19:22:08 october                    +
//+ changed: 2020y-02m-20d 23:40:00 february                   +
//+ raise.hpp                                                  +
//+                                            Tools's library +
//+                         Copyright @ 2019, Castle Of Dreams +
//+                                     [author: Idrisov D. R] +
//+                                   CastleOfDreams@yandex.ru +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#pragma once
#ifndef dTOOLS_RAISE_USED_ 
#define dTOOLS_RAISE_USED_ 100
//==============================================================================
//==============================================================================

#ifdef NDEBUG
    //release
    #include <stdexcept>

    #define dRAISE(...) \
        throw ::std::runtime_error(__VA_ARGS__);

    #define dVERIFY(...)                         \
        if(!(__VA_ARGS__))                       \
            throw ::std::runtime_error("verify(failed): " # __VA_ARGS__)
#else
    //debug
    #include <cassert>

    #define dRAISE(...) \
        assert(0  &&  __VA_ARGS__ )

    #define dVERIFY(...) \
        assert("verify(failed):" && __VA_ARGS__)

#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_RAISE_USED_
