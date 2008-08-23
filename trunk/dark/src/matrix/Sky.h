/*
 *  Sky.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Sky_h_
#define _Sky_h_

#include "Timer.h"

namespace Dark
{

  struct Sky
  {
    float time;
    float period;

    float heading;

    void init( float heading, float period );

    void update()
    {
      time = Math::mod( time + timer.frameTime, period );
    }
  };

}

#endif // _Sky_h_
