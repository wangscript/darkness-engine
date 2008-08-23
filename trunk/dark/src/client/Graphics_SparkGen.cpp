/*
 *  Graphics_SparkGenRenderer.cpp
 *
 *  Visual particle generator
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Graphics_SparkGenRenderer.h"

namespace Dark
{
namespace Graphics
{

  void SparkGenRenderer::createSpark( int i )
  {
    float velocitySpread2 = sparkGen->velocitySpread * 0.5;
    Vec3 velDisturb = Vec3( sparkGen->velocitySpread * Math::frand() - velocitySpread2,
                            sparkGen->velocitySpread * Math::frand() - velocitySpread2,
                            sparkGen->velocitySpread * Math::frand() - velocitySpread2 );

    Vec3 colorDisturb = Vec3( sparkGen->colorSpread.x * Math::frand(),
                              sparkGen->colorSpread.y * Math::frand(),
                              sparkGen->colorSpread.z * Math::frand() );

    sparks[i].p = sparkGen->p;
    sparks[i].velocity = sparkGen->velocity + velDisturb;
    sparks[i].color = sparkGen->color + colorDisturb;
    sparks[i].lifeTime = sparkGen->lifeTime;
  }

  SparkGenRenderer::SparkGenRenderer( Dark::SparkGen *sparkGen_ ) : sparkGen( sparkGen_ )
  {
    sparks = new Spark[sparkGen->number];
    startMillis = timer.millis;

    for( int i = 0; i < sparkGen->number; i++ ) {
      sparks[i].lifeTime = 0.0;
    }
  }

  SparkGenRenderer::~SparkGenRenderer()
  {
    delete[] sparks;
  }

  // TODO: spark rendering
  void SparkGenRenderer::draw()
  {
    for( int i = 0; i < nSparks; i++ ) {

    }
  }

  void SparkGenRenderer::update() {
    if( nSparks != sparkGen->number ) {
      int desiredNSparks = ( timer.millis - startMillis ) * sparksPerTick;

      nSparks = min( desiredNSparks, sparkGen->number );
    }
    for( int i = 0; i < nSparks; i++ ) {
      sparks[i].lifeTime -= timer.frameTime;

      if( sparks[i].lifeTime <= 0.0 ) {
        createSpark( i );
      }
    }
  }

}
}
