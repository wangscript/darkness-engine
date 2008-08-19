/*
 *  Graphics_Frustum.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Graphics_Frustum.h"

namespace Dark
{
namespace Graphics
{

  Frustum frustum;

  void Frustum::init( float fovY_, float aspect, float maxDistance_ )
  {
    maxDistance = maxDistance_;

    float fovX = Math::atan( Math::tan( Math::rad( fovY_ / 2.0 ) ) * aspect );
    float fovY = Math::atan( Math::tan( Math::rad( fovY_ / 2.0 ) ) );
    float sx, cx, sy, cy;

    Math::sincos( fovX, &sx, &cx );
    Math::sincos( fovY, &sy, &cy );

    nLeft0  = Vec3(  cx, sx,  0.0 );
    nRight0 = Vec3( -cx, sx,  0.0 );
    nUp0    = Vec3( 0.0, sy, -cy );
    nDown0  = Vec3( 0.0, sy,  cy );

    cosX2 = cx;
  }

  void Frustum::update()
  {
    nLeft  = camera.rotMat * nLeft0;
    nRight = camera.rotMat * nRight0;
    nDown  = camera.rotMat * nDown0;
    nUp    = camera.rotMat * nUp0;
    nFront = camera.at;

    dLeft  = camera.p * nLeft;
    dRight = camera.p * nRight;
    dDown  = camera.p * nDown;
    dUp    = camera.p * nUp;
    dFront = camera.p * nFront + maxDistance;
  }

}
}
