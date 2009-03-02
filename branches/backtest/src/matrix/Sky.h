/*
 *  Sky.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "Timer.h"

namespace Dark
{

  struct Sky
  {
    float time;
    float period;

    float heading;

		// heading of sun in degrees and day time in seconds
    void init( float heading, float period );

    void update()
    {
      time = Math::mod( time + timer.frameTime, period );
    }
  };

}
