/*
 *  Graphics_SparkGenRenderer.h
 *
 *  Visual particle generator
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_SparkGenRenderer_h_
#define _Graphics_SparkGenRenderer_h_

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

  class SparkGenRenderer
  {
    protected:

      Dark::SparkGen *sparkGen;
      Spark          *sparks;
      float          startMillis;
      float          sparksPerTick;
      int            nSparks;

      void createSpark( int i );

    public:

      SparkGenRenderer( Dark::SparkGen *sparkGen );
      ~SparkGenRenderer();

      void update();
      void draw();
  };

}
}

#endif // _Graphics_SparkGenRenderer_h_
