/*
 *  Matrix.h
 *
 *  World model
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "World.h"
#include "Bot.h"

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
