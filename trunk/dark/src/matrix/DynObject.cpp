/*
 *  DynObject.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "DynObject.h"

namespace Dark
{

  const float DynObject::DEFAULT_MASS = 10.0;
  const float DynObject::DEFAULT_LIFT = 0.03;

  void DynObject::load( FILE *stream )
  {
    Object::load( stream );

    fread( &velocity, sizeof( velocity ), 1, stream );
    fread( &newVelocity, sizeof( newVelocity ), 1, stream );
    fread( &mass, sizeof( mass ), 1, stream );
    fread( &lower, sizeof( lower ), 1, stream );
    fread( &floor, sizeof( floor ), 1, stream );

    lower = SDL_SwapBE32( lower );
  }

  void DynObject::save( FILE *stream )
  {
    Object::load( stream );

    lower = SDL_SwapBE32( lower );

    fwrite( &velocity, sizeof( velocity ), 1, stream );
    fwrite( &newVelocity, sizeof( newVelocity ), 1, stream );
    fwrite( &mass, sizeof( mass ), 1, stream );
    fwrite( &lower, sizeof( lower ), 1, stream );
    fwrite( &floor, sizeof( floor ), 1, stream );

    lower = SDL_SwapBE32( lower );
  }

}
