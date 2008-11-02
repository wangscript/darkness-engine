/*
 *  O_Tree2.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "O_Tree2.h"

#include "World.h"

namespace Dark
{

  const char *O_Tree2::NAME = "O_Tree2";

  O_Tree2::O_Tree2( const Vec3 &p_ )
  {
    p = p_,
    dim = Vec3( 0.6f, 0.6f, 2.25f );

    flags = Object::CLIP_BIT | Object::RELEASED_CULL_BIT;
    type = (int) NAME;

    model = LIST_TREE2;
  }

  O_Tree2::O_Tree2( float x, float y )
  {
    p = Vec3( x, y, world.terrain.height( x, y ) + 1.2f ),
    dim = Vec3( 0.6f, 0.6f, 2.25f );

    flags = Object::CLIP_BIT | Object::RELEASED_CULL_BIT;
    type = (int) NAME;

    model = LIST_TREE2;
  }

  void O_Tree2::onDestroy()
  {
    world.genParticles( 10, p, Vec3::zero(), 1.2f, 1.2f, 0.0f, 20.0f, LIST_SPARK,
                        Vec3( 0.5f, 0.5f, 0.5f ), 0.2f );
    world.remove( this );
  }

  void O_Tree2::load( FILE *stream )
  {
    Object::load( stream );
  }

  void O_Tree2::save( FILE *stream )
  {
//     fwrite( NAME, sizeof( NAME ), 1, stream );

    Object::save( stream );
  }

}