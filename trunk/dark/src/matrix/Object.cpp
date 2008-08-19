/*
 *  Object.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Object.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "Object.h"

namespace Dark
{

  void Object::load( FILE *stream )
  {
    fread( &p, sizeof( p ), 1, stream );
    fread( &dim, sizeof( dim ), 1, stream );
    fread( &index, sizeof( index ), 1, stream );
    fread( &flags, sizeof( flags ), 1, stream );
    fread( &type, sizeof( type ), 1, stream );
    fread( &model, sizeof( model ), 1, stream );
    fread( &anim, sizeof( anim ), 1, stream );
    fread( &rotZ, sizeof( rotZ ), 1, stream );
    fread( &alpha, sizeof( alpha ), 1, stream );

    index = SDL_SwapBE32( index );
    flags = SDL_SwapBE32( flags );
    type  = SDL_SwapBE32( type );
    model = SDL_SwapBE32( model );
    anim  = SDL_SwapBE32( anim );
  }

  void Object::save( FILE *stream )
  {
    index = SDL_SwapBE32( index );
    flags = SDL_SwapBE32( flags );
    type  = SDL_SwapBE32( type );
    model = SDL_SwapBE32( model );
    anim  = SDL_SwapBE32( anim );

    fwrite( &p, sizeof( p ), 1, stream );
    fwrite( &dim, sizeof( dim ), 1, stream );
    fwrite( &index, sizeof( index ), 1, stream );
    fwrite( &flags, sizeof( flags ), 1, stream );
    fwrite( &type, sizeof( type ), 1, stream );
    fwrite( &model, sizeof( model ), 1, stream );
    fwrite( &anim, sizeof( anim ), 1, stream );
    fwrite( &rotZ, sizeof( rotZ ), 1, stream );
    fwrite( &alpha, sizeof( alpha ), 1, stream );

    index = SDL_SwapBE32( index );
    flags = SDL_SwapBE32( flags );
    type  = SDL_SwapBE32( type );
    model = SDL_SwapBE32( model );
    anim  = SDL_SwapBE32( anim );
  }

}
