/*
 *  Matrix.h
 *
 *  World model
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Matrix.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Matrix_h_
#define _Matrix_h_

#include "World.h"
#include "Bot.h"

#include <SDL/SDL.h>

namespace Dark
{

  class Matrix
  {
    public:

      static const float G_ACCEL;

      // thread synchronization
      SDL_semaphore *semaphore;

      void load();
      void update();
      void free();
  };

  extern Matrix matrix;

}

#endif // _Matrix_h_
