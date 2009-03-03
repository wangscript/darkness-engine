/*
 *  Camera.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Camera_h_
#define _Client_Camera_h_

#include "matrix/Matrix.h"

namespace oz
{
namespace Client
{

  class Camera
  {
    protected:

      float smoothCoef;
      float smoothCoef_1;

      Vec3  oldP;

    public:

      Vec3  p;
      float h, v, r;

      Vec3  at;
      Vec3  up;

      Mat44 rotMat;
      Mat44 rotTMat;

      Bot     *player;
      World   *world;
      Matrix  *matrix;

      Camera();

      void init();
      void update();
  };

  extern Camera camera;

}
}

#endif // _Client_Camera_h_
