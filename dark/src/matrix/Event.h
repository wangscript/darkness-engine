/*
 *  Event.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: h 31 2008-11-02 11:45:37Z Davorin.Ucakar $
 */

#pragma once

namespace oz
{

  struct Event : PoolAlloc<Event, 0>
  {
    static const int HIT           = 0;
    static const int SPLASH_SOFT   = 1;
    static const int SPLASH_HARD   = 2;

    int   id;
    Event *next[1];

    Event()
    {}

    explicit Event( int id_ ) : id( id_ )
    {}
  };

}
