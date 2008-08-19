/*
 *  Graphics_SparkGen.h
 *
 *  Visual particle generator
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_SparkGen_h_
#define _Graphics_SparkGen_h_

#include "World.h"

namespace Dark
{
namespace Graphics
{

  struct Spark
  {
    Vec3  p;
    Vec3  velocity;
    Vec3  color;
    float lifeTime;
  };

  class SparkGen
  {
    protected:

      Dark::SparkGen *sparkGen;
      Spark          *sparks;

    public:

      SparkGen( Dark::SparkGen *sparkGen );
      ~SparkGen();

      void update();
  };

}
}

#endif // _Graphics_SparkGen_h_
