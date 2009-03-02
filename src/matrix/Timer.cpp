/*
 *  Timer.cpp
 *
 *  Timer utility
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Timer.h"

namespace Dark
{

  Timer timer;

  void Timer::update( int frameMillis_ )
  {
    frameMillis = frameMillis_;
    frameTime   = frameMillis / 1000.0f;

    millis      += frameMillis;
    time        = millis / 1000.0f;
  }

}
