/*
 *  Graphics_Sky.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_Sky.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Graphics_Sky_h_
#define _Graphics_Sky_h_

#include "precompiled.h"

namespace Dark
{
namespace Graphics
{

  class Sky
  {
    protected:

      static const float AMBIENT_COEF;

      static const float RED_COEF;
      static const float GREEN_COEF;
      static const float BLUE_COEF;

      static const float DAY_COLOR[3];
      static const float NIGHT_COLOR[3];

      Vec3  originalLightDir;
      Vec3  axis;

    public:

      // sky color
      float color[4];

      float lightDir[4];
      float diffuseColor[4];
      float ambientColor[4];

      // heading in degrees, period in seconds
      void init();

      void update();
      void set( float time );
  };

  extern Sky sky;

}
}

#endif // _Graphics_Sky_h_
