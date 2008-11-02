/*
 *  D_SmallCrate.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "D_SmallCrate.h"

#include "World.h"

namespace Dark
{

  const char *D_SmallCrate::NAME = "D_SmallCrate";
  const int D_SmallCrate::TYPE = String::hash( D_SmallCrate::NAME );

  D_SmallCrate::D_SmallCrate( const Vec3 &p_, Object *content_ )
  {
    p = p_,
    dim = Vec3( 0.3f, 0.3f, 0.3f );

    flags = Object::DYNAMIC_BIT | Object::CLIP_BIT | Object::FRICT_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;

    model = LIST_SMALL_CRATE;

    velocity = Vec3::zero();
    mass = 20.0f;

    content = content_;
  }

  D_SmallCrate::~D_SmallCrate()
  {
    if( content != null ) {
      delete content;
    }
  }

  void D_SmallCrate::onDestroy()
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

  void D_SmallCrate::onFrictBegin()
  {
    addContSound( SND_FRICTION_SOFT );
  }

  void D_SmallCrate::onFrictEnd()
  {
    removeContSound( SND_FRICTION_SOFT );
  }

}