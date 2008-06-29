/*
 *  Camera.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Camera.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "Camera.h"

namespace Dark
{

  Camera camera;

  Camera::Camera() : h( 0.0 ), v( 0.0 ), r( 0.0 )
  {
    p.setZero();
    at = Vec3( 0.0, 1.0, 0.0 );
    up = Vec3( 0.0, 0.0, 1.0 );

    rotMat.setId();
    rotTMat.setId();
  }

  void Camera::init()
  {
    sscanf( config["render.camera.smoothCoef"], "%f", &smoothCoef );
    smoothCoef_1 = 1.0 - smoothCoef;
  }

  void Camera::update()
  {
    h = player->h;
    v = player->v;
    p = ( player->p + player->camPos ) * smoothCoef_1 + oldP * smoothCoef;
    oldP = p;

    float hRad = Math::rad( h );
    float vRad = Math::rad( v );
    float hSine, hCosine, vSine, vCosine;

    Math::sincos( hRad, &hSine, &hCosine );
    Math::sincos( vRad, &vSine, &vCosine );

    at = Vec3( -hSine * vCosine,  hCosine * vCosine, vSine );
    up = Vec3(  hSine * vSine,   -hCosine * vSine,   vCosine );

    rotTMat = Mat44( hCosine, -hSine * vCosine,    hSine * vSine,   0.0,
                     hSine,    hCosine * vCosine, -hCosine * vSine, 0.0,
                     0.0,      vSine,              vCosine,         0.0,
                     0.0,      0.0,                0.0,             1.0 );

    rotMat = ~rotTMat;
  }

}
