﻿// [2021y-02m-16d][00:01:43] Idrisov Denis R.
// [2021y-02m-20d][00:01:43] birthday of the project
#pragma once
//================================================================================
//================================================================================

#if defined(_MSC_VER) && !defined(WIN32_LEAN_AND_MEAN)
    #define WIN32_LEAN_AND_MEAN
#endif

#define dBUILD_TARGET [test-600-others] tools
#include <tools/confbuild.hpp>
#include <mygtest/confinfo.hpp>
#include <mygtest/pch_used.hpp>
#include <mygtest/main.hpp>

//================================================================================
//================================================================================

#include <tools/features.hpp>
#include <tools/assert.hpp>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

#ifdef dHAS_ATOMIC
    #include <thread>
#endif

//==============================================================================
//==============================================================================
