/*
 *  SparkGen.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _SparkGen_h_
#define _SparkGen_h_

#include "Sector.h"

namespace Dark
{

  struct SparkGen
  {
    Vec3      p;

    int       index;
    Sector    *sector;

    SparkGen  *prev[1];
    SparkGen  *next[1];

    int       number;

    Vec3      velocity;
    float     velocitySpread;

    Vec3      color;
    Vec3      colorSpread;

    Vec3      gravity;
    float     lifeTime;

    SparkGen( const Vec3 &p, int number,
              const Vec3 &velocity, float velocitySpread,
              const Vec3 &color, const Vec3 &colorSpread,
              const Vec3 &gravity, float lifeTime );
  };

}

#endif // _SparkGen_h_
