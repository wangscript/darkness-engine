/*
 *  Matrix.cpp
 *
 *  World model
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Matrix.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "Matrix.h"

#include "Physics.h"

#include "Water.h"

#include "O_Tree1.h"
#include "O_Tree2.h"

#include "D_SmallCrate.h"
#include "D_BigCrate.h"
#include "D_WoodBarrel.h"
#include "D_MetalBarrel.h"

#include "B_Spirit.h"
#include "B_Human.h"
#include "B_Goblin.h"

#include <assert.h>

namespace Dark
{

  Matrix matrix;

  const float Matrix::G_ACCEL = -9.81;

  void Matrix::load()
  {
    semaphore = SDL_CreateSemaphore( 0 );

    physics.init( G_ACCEL );

    world.sky.init( 70.0, 60.0 );
    world.terrain.loadIMG( "terra/heightmap.png" );

    world.add( new BSP() );
    world.add( new BSP() );
    world.add( new BSP() );
    world.add( new BSP() );

    world.bsps[0]->loadQBSP( "bsp/center.bsp", BSP::BSP_SCALE, 4.0 );
    world.bsps[1]->loadQBSP( "bsp/house.bsp", BSP::BSP_SCALE, 4.0 );
    world.bsps[2]->loadQBSP( "bsp/temple.bsp", BSP::BSP_SCALE, 4.0 );
    world.bsps[3]->loadQBSP( "bsp/pool.bsp", BSP::BSP_SCALE, 4.0 );

    world.add( new Structure( Vec3( 47, -33, 75.5 ), 0 ) );
    world.add( new Structure( Vec3( 33, -34, 75.5 ), 1 ) );
    world.add( new Structure( Vec3( 40, -40, 75.8 ), 2 ) );

    world.add( new B_Goblin( Vec3( 40, -70, 90 ), 0.0, 0.0 ) );

    world.add( new B_Goblin( Vec3( 40, -35, 85 ) ) );

    world.add( new B_Goblin( Vec3( 41, -35, 85 ) ) );

    world.genParticles( 1000, Vec3( 40, -42, 74 ), Vec3( 0, 0, 10 ), 15.0, 1.95, 0.1, 5.0,
                        LIST_SPARK, Vec3( 0.4, 0.4, 0.4 ), 0.2 );

    world.add( new D_MetalBarrel( Vec3( 51.0, -42.0, 80.0 ) ) );
    world.add( new D_MetalBarrel( Vec3( 51.0, -42.0, 82.0 ) ) );
    world.add( new D_MetalBarrel( Vec3( 51.0, -42.0, 84.0 ) ) );

    world.add( new D_WoodBarrel( Vec3( 51.0, -38.0, 80.0 ) ) );
    world.add( new D_WoodBarrel( Vec3( 51.0, -38.0, 82.0 ) ) );
    world.add( new D_WoodBarrel( Vec3( 51.0, -38.0, 84.0 ) ) );

    world.add( new D_SmallCrate( Vec3( 41.0, -41.0, 80.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 41.0, -41.0, 81.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 41.0, -41.0, 82.0 ) ) );

    world.add( new D_SmallCrate( Vec3( 41.0, -42.0, 80.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 41.0, -42.0, 81.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 41.0, -42.0, 82.0 ) ) );

    world.add( new D_SmallCrate( Vec3( 42.0, -42.0, 80.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 42.0, -42.0, 81.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 42.0, -42.0, 82.0 ) ) );

    world.add( new D_SmallCrate( Vec3( 42.0, -41.0, 80.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 42.0, -41.0, 81.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 42.0, -40.0, 82.0 ) ) );

    world.add( new D_BigCrate( Vec3( 40.0, -55.0, 80.0 ), new D_SmallCrate() ) );
    world.add( new D_BigCrate( Vec3( 40.0, -55.0, 82.0 ), new D_SmallCrate() ) );
    world.add( new D_BigCrate( Vec3( 40.0, -55.0, 84.0 ), new D_SmallCrate() ) );

    world.add( new O_Tree1( 0.0, -30.0 ) );
    world.add( new O_Tree2( 0.0, -42.0 ) );

    world.add( new Water( Vec3( -80.0, 112.0, 33.0 ), Vec3( 3.0, 3.0, 1.0 ) ) );
    world.add( new Water( Vec3( -86.0, 112.0, 33.0 ), Vec3( 3.0, 3.0, 1.0 ) ) );
    world.add( new Water( Vec3( -80.0, 118.0, 33.0 ), Vec3( 3.0, 3.0, 1.0 ) ) );

    world.add( new Structure( Vec3( 40.0, -60.0, 75.0 ), 3 ) );
    world.add( new Water( Vec3( 40.0, -60.0, 75.0 ), Vec3( 3.0, 3.0, 3.0 ) ) );

    world.add( new D_SmallCrate( Vec3( 42.0, -61.0, 81.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 42.0, -61.0, 82.0 ) ) );
    world.add( new D_SmallCrate( Vec3( 42.0, -61.0, 83.0 ) ) );
  }

  void Matrix::update()
  {
    world.beginUpdate();
    physics.beginUpdate();

    const int iMax = world.particles.length();
    for( int i = 0; i < iMax; i++ ) {
      Particle *part = world.particles[i];

      if( part != null ) {
        part->update();
        physics.updatePart( part );

        if( part->lifeTime <= 0.0 || part->velocity.sqL() > Physics::MAX_VELOCITY2 ) {
          world.remove( part );
        }
      }
    }

    const int jMax = world.objects.length();
    for( int j = 0; j < jMax; j++ ) {
      Object *obj = world.objects[j];

      if( obj != null ) {
        obj->update();

        if( ( obj->flags & Object::DYNAMIC_BIT ) && obj->sector != null ) {
          DynObject *dynObj = (DynObject*) obj;

          physics.updateObj( dynObj );

          if( dynObj->newVelocity.sqL() > Physics::MAX_VELOCITY2 ) {
            world.remove( obj );
            continue;
          }
        }
        if( obj->damage <= 0.0 ) {
          obj->destroy();
        }
      }
    }

    physics.endUpdate();
    world.endUpdate();
  }

  void Matrix::free()
  {
    world.free();
    SDL_DestroySemaphore( semaphore );
  }

}
