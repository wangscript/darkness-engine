/*
 *  Sky.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Sky.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Sky_h_
#define _Sky_h_

#include "base.h"
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
