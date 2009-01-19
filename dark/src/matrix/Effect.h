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

namespace Dark
{

  struct Effect : Reuser<Effect>
  {
    static const int SPLASH_SOFT = 1;
    static const int SPLASH_HARD = 2;

    Effect *next[1];
    int    id;

    explicit Effect( int id_ ) : id( id_ )
    {}
  };

}
