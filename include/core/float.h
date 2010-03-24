#pragma once
#ifndef FLOAT_H
#define FLOAT_H

#include "core/platform.h"

#include <cmath>

/**
 * For a discussion of float comparison functions, see
 *   http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
 */

/**
 * Comparison function for floats numbers
 *  @param x First number
 *  @param y Second number
 *  @param maxDist Maximum distance between two (discrete) numbers considered to be equal
 *  @return bool true iff the two numbers are equal
 */
inline bool floateq(float x, float y, int32 maxDist = 5)
{
  BOOST_STATIC_ASSERT(sizeof(float) == sizeof(int32));

  int32 i_x = *(int32 *)&x;
  if (i_x < 0) {
    i_x = 0x80000000L - i_x;
  }

  int32 i_y = *(int32 *)&y;
  if (i_y < 0) {
    i_y = 0x80000000L - i_y;
  }

  return(abs(i_x - i_y) <= maxDist);
}

/**
 * Operator <= for float numbers
 */
inline bool floatle(float x, float y, int32 maxDist = 5)
{
  return x < y || floateq(x, y, maxDist);
}

/**
 * Operator >= for float numbers
 */
inline bool floatge(float x, float y, int32 maxDist = 5)
{
  return x > y || floateq(x, y, maxDist);
}

/**
 * Operator < for float numbers
 */
inline bool floatlt(float x, float y, int32 maxDist = 5)
{
  return !floatge(x, y, maxDist);
}

/**
 * Operator > for float numbers
 */
inline bool floatgt(float x, float y, int32 maxDist = 5)
{
  return !floatle(x, y, maxDist);
}

/**
 * Comparison function for double numbers
 *  @param x First number
 *  @param y Second number
 *  @param maxDist Maximum distance between two (discrete) numbers considered to be equal
 *  @return bool true iff the two numbers are equal
 */
inline bool doubleeq(double x, double y, int64 maxDist = 5)
{
  BOOST_STATIC_ASSERT(sizeof(double) == sizeof(int64));

  int64 i_x = *(int64 *)&x;
  if (i_x < 0) {
    i_x = 0x8000000000000000LL - i_x;
  }

  int64 i_y = *(int64 *)&y;
  if (i_y < 0) {
    i_y = 0x8000000000000000LL - i_y;
  }

  return(llabs(i_x - i_y) <= maxDist);
}

/**
 * Operator <= for double numbers
 */
inline bool doublele(double x, double y, int32 maxDist = 5)
{
  return x < y || doubleeq(x, y, maxDist);
}

/**
 * Operator >= for double numbers
 */
inline bool doublege(double x, double y, int32 maxDist = 5)
{
  return x > y || doubleeq(x, y, maxDist);
}

/**
 * Operator < for double numbers
 */
inline bool doublelt(double x, double y, int32 maxDist = 5)
{
  return !doublege(x, y, maxDist);
}

/**
 * Operator > for double numbers
 */
inline bool doublegt(double x, double y, int32 maxDist = 5)
{
  return !doublele(x, y, maxDist);
}

#endif
