/*
 *  Graphics_Sky.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_Sky.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "Graphics_Sky.h"

#include "Timer.h"
#include "World.h"

namespace Dark
{
namespace Graphics
{

  Sky sky;

  const float Sky::AMBIENT_COEF = 0.4;

  const float Sky::RED_COEF = +0.05;
  const float Sky::GREEN_COEF = -0.05;
  const float Sky::BLUE_COEF = -0.10;

  const float Sky::DAY_COLOR[] = { 0.45, 0.60, 0.90 };
  const float Sky::NIGHT_COLOR[] = { 0.02, 0.03, 0.06 };

  void Sky::init()
  {
    float heading = Math::rad( world.sky.heading );

    axis = Vec3( Math::cos( heading ), Math::sin( -heading ), 0.0 );
    originalLightDir = Vec3( Math::sin( heading ), Math::cos( heading ), 0.0 );

    update();
  }

  void Sky::update()
  {
    float angle = 2.0 * Math::PI * ( world.sky.time / world.sky.period );
    Vec3  dir = Quat::rotAxis( axis, angle ).rotate( originalLightDir );

    float ratio = bound( dir.z, 0.0, 1.0 );
    float ratio1 = 1.0 - ratio;
    float ratioDiff = ( 1.0 - abs( ratio - ratio1 ) );

    color[0] = ratio * DAY_COLOR[0] + ratio1 * NIGHT_COLOR[0] + RED_COEF * ratioDiff;
    color[1] = ratio * DAY_COLOR[1] + ratio1 * NIGHT_COLOR[1] + GREEN_COEF * ratioDiff;
    color[2] = ratio * DAY_COLOR[2] + ratio1 * NIGHT_COLOR[2] + BLUE_COEF * ratioDiff;
    color[3] = 1.0;

    lightDir[0] = dir.x;
    lightDir[1] = dir.y;
    lightDir[2] = dir.z;
    lightDir[3] = 0.0;

    diffuseColor[0] = ratio + RED_COEF * ratioDiff;
    diffuseColor[1] = ratio + GREEN_COEF * ratioDiff;
    diffuseColor[2] = ratio + BLUE_COEF * ratioDiff;
    diffuseColor[3] = 1.0;

    ambientColor[0] = AMBIENT_COEF * diffuseColor[0];
    ambientColor[1] = AMBIENT_COEF * diffuseColor[1];
    ambientColor[2] = AMBIENT_COEF * diffuseColor[2];
    ambientColor[3] = 1.0;
  }

}
}
