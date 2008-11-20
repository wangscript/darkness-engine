/*
 *  Timer.h
 *
 *  Timer utility
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  class Timer
  {
    protected:

      Vector<float*> timers;

    public:

      int   frameMillis;
      int   millis;

      float frameTime;
      float time;

      void update( int frameMillis );
  };

  extern Timer timer;

}
