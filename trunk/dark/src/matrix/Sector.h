/*
 *  Sector.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Sector.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Sector_h_
#define _Sector_h_

namespace Dark
{

  class Object;
  class SparkGen;
  class Particle;

  struct Sector
  {
    static const scalar DIM;
    static const scalar RADIUS;

    Vector<int> structures;

    DList<Object, 0>    objects;
    DList<SparkGen, 0>  sparkGens;
    DList<Particle, 0>  particles;
  };

}

#endif // _Sector_h_
