/*
 *  Skybox.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "Context.h"

#define SKY_DIST   1.0f

namespace Dark
{
namespace Client
{

  class Skybox {
    protected:
      uint list;

      void drawUpper( uint top, uint front, uint left, uint back, uint right );

    public:
      void init( Context *context, uint top, uint front, uint left, uint back, uint right );
      void init( Context *context, uint top, uint front, uint left, uint back, uint right,
                 uint bottom );
      void draw();
  };

}
}
