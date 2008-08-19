/*
 *  Timer.cpp
 *
 *  Timer utility
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Timer.h"

namespace Dark
{

  Timer timer;

  void Timer::update( int frameMilis_ )
  {
    frameMilis = frameMilis_;
    frameTime  = frameMilis / 1000.0;

    milis      += frameMilis;
    time       = milis / 1000.0;
  }

}
