/*
 *  Timer.h
 *
 *  Timer utility
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Timer.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Timer_h_
#define _Timer_h_

namespace Dark
{

  class Timer
  {
    protected:

      Vector<float*> timers;

    public:

      int   frameMilis;
      int   milis;

      float frameTime;
      float time;

      void update( int frameMilis );
  };

  extern Timer timer;

}

#endif // _Timer_h_
