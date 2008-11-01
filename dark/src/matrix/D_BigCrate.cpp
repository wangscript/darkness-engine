/*
 *  D_BigCrate.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
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
    dim = Vec3( 0.6f, 0.6f, 0.6f );

    flags = Object::DYNAMIC_BIT | Object::CLIP_BIT | Object::FRICT_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;

    model = LIST_BIG_CRATE;

    velocity = Vec3::zero();
    mass = 150.0f;

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
    world.genParticles( 10, p, velocity, 1.2f, 1.2f, 0.0f, 20.0f, LIST_SPARK,
                        Vec3( 0.5f, 0.5f, 0.5f ), 0.2f );

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
    removeContSound( SND_FRICTION_SOFT );
  }

}
