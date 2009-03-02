/*
 *  SparkGenRender.h
 *
 *  Visual particle generator
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_SparkGenRender_h_
#define _Client_SparkGenRender_h_

#include "matrix/World.h"

namespace Dark
{
namespace Client
{

  struct Spark
  {
    Vec3  p;
    Vec3  velocity;
    Vec3  color;
    float lifeTime;
  };

  class SparkGenRender
  {
    public:

      enum State
      {
        NOT_UPDATED,
        UPDATED
      };

    protected:

      Dark::SparkGen *sparkGen;
      Spark          *sparks;
      float          startMillis;
      float          sparksPerTick;
      int            nSparks;

      void createSpark( int i );

    public:

      State          state;

      explicit SparkGenRender( Dark::SparkGen *sparkGen );
      SparkGenRender( const SparkGenRender &sparkGenRender );
      ~SparkGenRender();

      void update();
      void draw();
  };

}
}

#endif // _Client_SparkGenRender_h_
