/*
 *  D_MetalBarrel.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: D_MetalBarrel.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "D_MetalBarrel.h"

#include "World.h"

namespace Dark
{

  const char *D_MetalBarrel::NAME = "D_MetalBarrel";

  D_MetalBarrel::D_MetalBarrel( const Vec3 &p_ )
  {
    p = p_,
    dim = Vec3( 0.4032, 0.4032, 0.5922 );

    flags = Object::DYNAMIC_BIT | Object::CLIP_BIT | Object::FRICT_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;

    model = LIST_METAL_BARREL;

    velocity = Vec3::zero();
    mass = 50.0;
  }

  void D_MetalBarrel::onDestroy()
  {
    world.genParticles( 10, p, velocity, 1.2, 1.2, 0.0, 20.0, LIST_SPARK,
                        Vec3( 0.5, 0.5, 0.5 ), 0.2 );

    world.remove( this );
  }

  void D_MetalBarrel::onFrictBegin()
  {
    addContSound( SND_FRICTION_HARD );
  }

  void D_MetalBarrel::onFrictEnd()
  {
    excludeContSound( SND_FRICTION_HARD );
  }

}
