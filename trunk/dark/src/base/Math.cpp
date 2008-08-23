/*
 *  Math.cpp
 *
 *  Math constants
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

namespace Dark
{

  const scalar Math::FLOAT_EPS  = 1.1920928955078125e-7;
  const scalar Math::DOUBLE_EPS = 2.2204460492503130808e-16;
  const scalar Math::E          = 2.7182818284590452354;
  const scalar Math::LOG2E      = 1.4426950408889634074;
  const scalar Math::LOG10E     = 0.43429448190325182765;
  const scalar Math::LN2        = 0.69314718055994530942;
  const scalar Math::LN10       = 2.30258509299404568402;
  const scalar Math::PI         = 3.14159265358979323846;
  const scalar Math::PI_2       = 1.57079632679489661923;
  const scalar Math::PI_4       = 0.78539816339744830962;
  const scalar Math::_1_PI      = 0.31830988618379067154;
  const scalar Math::_2_PI      = 0.63661977236758134308;
  const scalar Math::_2_SQRTPI  = 1.12837916709551257390;
  const scalar Math::SQRT2      = 1.41421356237309504880;
  const scalar Math::SQRT1_2    = 0.70710678118654752440;
  const scalar Math::NaN        = NAN;
  const scalar Math::INF        = INFINITY;

  void Math::init()
  {
    ::srand( time( null ) );
  }

}
