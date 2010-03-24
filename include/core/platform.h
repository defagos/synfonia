#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include <boost/static_assert.hpp>

/**
 * Integer types
 */
#if defined(_MSC_VER)
  // Microsoft compilers 32/64 bits
  typedef __int8 int8;
  typedef unsigned __int8 uint8;
  typedef __int16 int16;
  typedef unsigned __int16 uint16;
  typedef __int32 int32;
  typedef unsigned __int32 uint32;
  typedef __int64 int64;
  typedef unsigned __int64 uint64;
#elif defined(__GNUC__)
  // GNU compiler on Linux and Windows platforms (cygwin, MinGW)
  typedef char int8;
  typedef unsigned char uint8;
  typedef short int16;
  typedef unsigned short uint16;
  typedef int int32;
  typedef unsigned int uint32;
  typedef long long int64;
  typedef unsigned long long uint64;
#else
  // Other compiler
  typedef char int8;
  typedef unsigned char uint8;
  typedef short int16;
  typedef unsigned short uint16;
  typedef int int32;
  typedef unsigned int uint32;
  typedef long long int64;
  typedef unsigned long long uint64;
#endif

/* Check integer sizes */
BOOST_STATIC_ASSERT(sizeof(int8) == 1);
BOOST_STATIC_ASSERT(sizeof(int16) == 2);
BOOST_STATIC_ASSERT(sizeof(int32) == 4);
BOOST_STATIC_ASSERT(sizeof(int64) == 8);


/**
 * Implementation of Technical Report 1 (std::tr1)
 *
 * We introduce a PLATFORM_USE_NATIVE_TR1 macro for use by clients including
 * this file. If set to 1, then clients can assume their compiler implements
 * tr1. When set to 0, they must assume their compiler does not implement tr1.
 *
 * The value of this macro is automatically calculated. Do not override it
 * manually.
 */
#if defined(_MSC_VER)
  // Microsoft compilers 32/64 bits
  #if _MSC_VER >= 1600
    // Version 10 and above
    #include <yvals.h>
    #if _HAS_TR1
      #define PLATFORM_USE_NATIVE_TR1 1
    #else
      #define PLATFORM_USE_NATIVE_TR1 0
    #endif
  #else
    // Older versions
    #define PLATFORM_USE_NATIVE_TR1 0
  #endif
#elif defined(__GNUC__)
  // GNU compiler on Windows platforms (cygwin, MinGW)
  #define PLATFORM_USE_NATIVE_TR1 0
#else
  // Other compiler
  #define PLATFORM_USE_NATIVE_TR1 0
#endif

#endif
