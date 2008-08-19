/*
 *  O_Tree1.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: O_Tree1.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "O_Tree1.h"

#include "World.h"

namespace Dark
{

  const char *O_Tree1::NAME = "O_Tree1";

  O_Tree1::O_Tree1( const Vec3 &p_ )
  {
    logFile.println( "%g %g %g", p_.x, p_.y, p_.z );
    p = p_,
    dim = Vec3( 0.7, 0.7, 3.8 );

    flags = Object::CLIP_BIT | Object::RELEASED_CULL_BIT;
    type = TYPE;

    damage = Math::INF;

    model = LIST_TREE1;
  }

  O_Tree1::O_Tree1( float x, float y )
  {
    p = Vec3( x, y, world.terrain.height( x, y ) + 2.5 ),
    dim = Vec3( 0.7, 0.7, 3.8 );

    flags = Object::CLIP_BIT | Object::RELEASED_CULL_BIT;
    type = O_TREE1;

    damage = Math::INF;

    model = LIST_TREE1;
  }

  void O_Tree1::onDestroy()
  {
    world.genParticles( 10, p, Vec3::zero(), 1.2, 1.2, 0.0, 20.0, LIST_SPARK,
                        Vec3( 0.5, 0.5, 0.5 ), 0.2 );
    world.remove( this );
  }

  void O_Tree1::load( FILE *stream )
  {
    Object::load( stream );
  }

  void O_Tree1::save( FILE *stream )
  {
    fwrite( NAME, sizeof( NAME ), 1, stream );

    Object::save( stream );
  }

}
