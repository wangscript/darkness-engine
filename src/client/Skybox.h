/*
 *  Skybox.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Skybox_h_
#define _Client_Skybox_h_

#include "Context.h"

#define SKY_DIST   1.0f

namespace oz
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

#endif // _Client_Skybox_h_
