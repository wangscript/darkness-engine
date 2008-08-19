/*
 *  D_BigCrate.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: D_BigCrate.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "D_BigCrate.h"

#include "World.h"

namespace Dark
{

  const char *D_BigCrate::NAME = "D_BigCrate";

  D_BigCrate::D_BigCrate( const Vec3 &p_, Object *content_ )
  {
    p = p_,
    dim = Vec3( 0.6, 0.6, 0.6 );

    flags = Object::DYNAMIC_BIT | Object::CLIP_BIT | Object::FRICT_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;

    model = LIST_BIG_CRATE;

    velocity = Vec3::zero();
    mass = 150.0;
    content = content_;
  }

  D_BigCrate::~D_BigCrate()
  {
    if( content != null ) {
      delete content;
    }
  }

  void D_BigCrate::onDestroy()
  {
    world.genParticles( 10, p, velocity, 1.2, 1.2, 0.0, 20.0, LIST_SPARK,
                        Vec3( 0.5, 0.5, 0.5 ), 0.2 );

    if( content != null ) {
      content->p = p;
      world.add( content );
      content = null;
    }
    world.remove( this );
  }

  void D_BigCrate::onFrictBegin()
  {
    addContSound( SND_FRICTION_SOFT );
  }

  void D_BigCrate::onFrictEnd()
  {
    excludeContSound( SND_FRICTION_SOFT );
  }

}
