/*
 *  Effect.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace oz
{

  struct Effect : ReuseAlloc<Effect>
  {
    static const int HIT          = 0;
    static const int SPLASH_SOFT  = 1;
    static const int SPLASH_HARD  = 2;

    int    id;
    void   *dual;
    Effect *next[1];

    explicit Effect( int id_ ) : id( id_ )
    {}
  };

}
