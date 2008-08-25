/*
 *  Graphics_SparkGenRender.cpp
 *
 *  Visual particle generator
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Graphics_SparkGenRender.h"

#include "Graphics_Frustum.h"

namespace Dark
{
namespace Graphics
{

  void SparkGenRender::createSpark( int i )
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

  SparkGenRender::SparkGenRender( Dark::SparkGen *sparkGen_ ) : sparkGen( sparkGen_ )
  {
    sparks = new Spark[sparkGen->number];
    startMillis = timer.millis;
    nSparks = 0;

    for( int i = 0; i < sparkGen->number; i++ ) {
      sparks[i].lifeTime = 0.0;
    }
  }

  SparkGenRender::SparkGenRender( const SparkGenRender &sparkGenRender ) :
      sparkGen( sparkGenRender.sparkGen ),
      startMillis( sparkGenRender.startMillis ),
      sparksPerTick( sparkGenRender.sparksPerTick ),
      nSparks( sparkGenRender.nSparks )
  {
    sparks = new Spark[nSparks];
    aCopy( sparks, sparkGenRender.sparks, nSparks );
  }

  SparkGenRender::~SparkGenRender()
  {
    delete[] sparks;
  }

  void SparkGenRender::draw()
  {
    float sparkDim = sparkGen->sparkDim;

    glPushMatrix();

    glMultMatrixf( camera.rotMat );

    for( int i = 0; i < nSparks; i++ ) {
      Vec3 &p = sparks[i].p;

      glTranslatef( p.x, p.y, p.z );

      glBegin( GL_QUADS );
        glTexCoord2f( 0.0, 0.0 );
        glVertex3f( -sparkDim, -sparkDim, 0.0 );
        glTexCoord2f( 0.0, 1.0 );
        glVertex3f( +sparkDim, -sparkDim, 0.0 );
        glTexCoord2f( 1.0, 1.0 );
        glVertex3f( +sparkDim, +sparkDim, 0.0 );
        glTexCoord2f( 1.0, 0.0 );
        glVertex3f( -sparkDim, +sparkDim, 0.0 );
      glEnd();

      glTranslatef( -p.x, -p.y, -p.z );
    }

    glPopMatrix();
  }

  void SparkGenRender::update() {
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
