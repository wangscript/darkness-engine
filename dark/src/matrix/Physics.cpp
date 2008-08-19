/*
 *  Physics.cpp
 *
 *  Physics engine
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Physics.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "Physics.h"

namespace Dark
{

  Physics physics;

  const float Physics::CLIP_BACKOFF     = 3.0 * EPSILON;
  const float Physics::STICK_VELOCITY   = 0.015;

  const float Physics::AIR_FRICTION     = 0.05;
  const float Physics::WATER_FRICTION   = 0.05;
  const float Physics::FLOOR_FRICTION   = 0.20;
  const float Physics::OBJ_FRICTION     = 0.20;

  // default 10000.0: 100 m/s
  const float Physics::MAX_VELOCITY2    = 10000.0;
  const float Physics::FLOOR_NORMAL_Z   = 0.70;

  //***********************************
  //*   PARTICLE COLLISION HANDLING   *
  //***********************************

  void Physics::handlePartHit()
  {
    part->velocity -= ( part->rejection * ( part->velocity * collider.hit.normal ) ) *
        collider.hit.normal;

    Object *sObj = collider.hit.sObj;

    if( sObj != null ) {
      if( sObj->flags & Object::DYNAMIC_BIT ) {
        DynObject *sDynObj = (DynObject*) sObj;

        sDynObj->hit( &collider.hit );
      }
      else {
        sObj->hit( &collider.hit );
      }
    }
  }

  void Physics::handlePartMove()
  {
    leftRatio = 1.0;
    move = part->velocity * timer.frameTime;

    Sector *oldSector = part->sector;

    int traceSplits = 0;
    do {
      collider.translate( part->p, move );
      part->p += collider.hit.ratio * move;
      leftRatio -= leftRatio * collider.hit.ratio;

      if( collider.hit.ratio == 1.0 ) {
        break;
      }
      // collision response
      handlePartHit();

      if( traceSplits >= MAX_TRACE_SPLITS ) {
        break;
      }
      traceSplits++;

      move *= 1.0 - collider.hit.ratio;
      move -= ( move * collider.hit.normal - CLIP_BACKOFF ) * collider.hit.normal;
    }
    while( true );

    Sector *newSector = world.getSector( part->p );

    if( oldSector != newSector ) {
      oldSector->particles.remove( part );
      newSector->particles << part;
      part->sector = newSector;
    }
  }

  //***********************************
  //*    OBJECT COLLISION HANDLING    *
  //***********************************

  bool Physics::handleObjFriction()
  {
    if( obj->flags & Object::HOVER_BIT ) {
      if( obj->newVelocity.sqL() <= STICK_VELOCITY ) {
        obj->newVelocity.setZero();
      }
      else {
        obj->newVelocity *= 1.0 - AIR_FRICTION;
      }
    }
    else {
      if( obj->flags & Object::ON_WATER_BIT ) {
        obj->flags &= ~Object::ON_WATER_BIT;

        if( obj->flags & Object::UNDER_WATER_BIT ) {
          obj->flags &= ~Object::UNDER_WATER_BIT;

          obj->newVelocity *= 1.0 - WATER_FRICTION;
          obj->newVelocity.z += obj->lift;
          return true;
        }
      }
      else {
        obj->flags &= ~Object::IN_WATER_BIT;
      }

      if( obj->flags & Object::ON_FLOOR_BIT ) {
        float xyDot = obj->newVelocity.x * obj->newVelocity.x +
            obj->newVelocity.y * obj->newVelocity.y;

        if( xyDot > STICK_VELOCITY ) {
          obj->newVelocity.x *= 1.0 - FLOOR_FRICTION;
          obj->newVelocity.y *= 1.0 - FLOOR_FRICTION;

          obj->newVelocity += ( gVelocity * obj->floor.z ) * obj->floor;
          obj->flags &= ~Object::ON_FLOOR_BIT;

          obj->frictBegin();
        }
        else {
          obj->newVelocity.x = 0.0;
          obj->newVelocity.y = 0.0;

          obj->frictEnd();

          if( obj->newVelocity.z <= STICK_VELOCITY ) {
            obj->newVelocity.z = 0.0;
            return false;
          }
          else {
            obj->flags &= ~Object::ON_FLOOR_BIT;
          }
        }
      }
      else if( obj->lower >= 0 ) {
        DynObject *sObj = (DynObject*) world.objects[obj->lower];

        if( obj->newVelocity.x != 0.0 || obj->newVelocity.y != 0.0 ||
            sObj->velocity.x != 0.0 || sObj->velocity.y != 0.0 )
        {
          float dx = sObj->velocity.x - obj->newVelocity.x;
          float dy = sObj->velocity.y - obj->newVelocity.y;

          obj->newVelocity.z += gVelocity;
          obj->lower = -1;

          if( ( dx*dx + dy*dy ) > STICK_VELOCITY ) {
            obj->newVelocity.x += dx * OBJ_FRICTION;
            obj->newVelocity.y += dy * OBJ_FRICTION;

            obj->frictBegin();
          }
          else {
            obj->newVelocity.x = sObj->velocity.x;
            obj->newVelocity.y = sObj->velocity.y;

            obj->frictEnd();
          }
        }
        else {
          obj->frictEnd();

          if( obj->newVelocity.z == 0.0 && sObj->velocity.z == 0.0 ) {
            return false;
          }
          else {
            obj->newVelocity.z += gVelocity;
            obj->lower = -1;
          }
        }
      }
      else {
        obj->newVelocity.x *= 1.0 - AIR_FRICTION;
        obj->newVelocity.y *= 1.0 - AIR_FRICTION;
        obj->newVelocity.z += gVelocity;
      }
    }
    return true;
  }

  void Physics::handleObjHit()
  {
    Object *sObj = collider.hit.sObj;
    Vec3 oldVelocity = obj->newVelocity;

    if( collider.hit.sObj != null && ( collider.hit.sObj->flags & Object::DYNAMIC_BIT ) ) {
      DynObject *sDynObj = (DynObject*) sObj;

      if( collider.hit.normal.z == 0.0 ) {
        if( obj->flags & Object::PUSHING_BIT ) {
          float pushX = ( obj->newVelocity.x - sDynObj->velocity.x ) / ( obj->mass + sDynObj->mass );
          float pushY = ( obj->newVelocity.y - sDynObj->velocity.y ) / ( obj->mass + sDynObj->mass );

          obj->newVelocity.x -= pushX * sDynObj->mass;
          obj->newVelocity.y -= pushY * sDynObj->mass;

          sDynObj->newVelocity.x += pushX * obj->mass;
          sDynObj->newVelocity.y += pushY * obj->mass;
        }
        else if( collider.hit.normal.y == 0.0 ) {
          float pushX = ( obj->newVelocity.x - sDynObj->velocity.x ) / ( obj->mass + sDynObj->mass );

          obj->newVelocity.x -= pushX * sDynObj->mass;
          sDynObj->newVelocity.x += pushX * obj->mass;
        }
        else {
          float pushY = ( obj->newVelocity.y - sDynObj->velocity.y ) / ( obj->mass + sDynObj->mass );

          obj->newVelocity.y -= pushY * sDynObj->mass;
          sDynObj->newVelocity.y += pushY * obj->mass;
        }
      }
      else if( collider.hit.normal.z == -1.0 ) {
        float pushZ = ( obj->newVelocity.z - sDynObj->velocity.z ) / ( obj->mass + sDynObj->mass );

        obj->newVelocity.z -= pushZ * sDynObj->mass;
        sDynObj->newVelocity.z += pushZ * obj->mass;

        sDynObj->flags &= ~Object::ON_FLOOR_BIT;
        sDynObj->lower = obj->index;
      }
      else {
        float pushZ = ( obj->newVelocity.z - sDynObj->velocity.z ) / ( obj->mass + sDynObj->mass );

        obj->newVelocity.z = sDynObj->velocity.z;
        sDynObj->newVelocity.z += pushZ * obj->mass;

        obj->flags &= ~Object::ON_FLOOR_BIT;
        obj->lower = sDynObj->index;
      }
      if( sDynObj != null ) {
        sDynObj->hit( &collider.hit );
      }
    }
    else {
      obj->newVelocity -= ( obj->newVelocity * collider.hit.normal ) * collider.hit.normal;

      if( !( obj->flags & Object::HOVER_BIT ) && collider.hit.normal.z > FLOOR_NORMAL_Z ) {
        obj->lower = -1;
        obj->floor = collider.hit.normal;
        obj->flags |= Object::ON_FLOOR_BIT;
      }
      if( sObj != null ) {
        sObj->hit( &collider.hit );
      }
    }
    if( obj->flags ) {
      obj->hit( &collider.hit );
    }
  }

  void Physics::handleObjMove()
  {
    leftRatio = 1.0;
    move = obj->newVelocity * timer.frameTime;

    Sector *oldSector = obj->sector;

    int traceSplits = 0;
    do {
      collider.translate( *obj, move, obj );
      obj->p += collider.hit.ratio * move;
      leftRatio -= leftRatio * collider.hit.ratio;

      if( collider.hit.ratio == 1.0 ) {
        break;
      }
      // collision response
      handleObjHit();

      if( traceSplits >= MAX_TRACE_SPLITS ) {
        break;
      }
      traceSplits++;

      move *= 1.0 - collider.hit.ratio;
      move -= ( move * collider.hit.normal - CLIP_BACKOFF ) * collider.hit.normal;

      // to prevent to get stuck in corners < 90 deg and to prevent oscillations in corners > 90 deg
      if( traceSplits > 1 ) {
        float dot = lastNormals[0] * collider.hit.normal;

        if( dot != 0.0 ) {
          Vec3 cross = collider.hit.normal ^ lastNormals[0];

          if( !cross.isZero() ) {
            cross.norm();
            move = ( move * cross ) * cross;
            move += ( collider.hit.normal + lastNormals[0] ) * EPSILON;
          }
        }
        if( traceSplits > 2 ) {
          dot = lastNormals[1] * collider.hit.normal;

          if( dot != 0.0 ) {
            Vec3 cross = collider.hit.normal ^ lastNormals[1];

            if( !cross.isZero() ) {
              cross.norm();
              move = ( move * cross ) * cross;
              move += ( collider.hit.normal + lastNormals[1] ) * EPSILON;
            }
          }
        }
        else {
          lastNormals[1] = lastNormals[0];
          lastNormals[0] = collider.hit.normal;
        }
      }
      else {
        lastNormals[0] = collider.hit.normal;
      }
    }
    while( true );

    Sector *newSector = world.getSector( obj->p );

    if( oldSector != newSector ) {
      oldSector->objects.remove( obj );
      newSector->objects << obj;
      obj->sector = newSector;
    }
  }

  //***********************************
  //*             PUBLIC              *
  //***********************************

  void Physics::init( float gAccel_ )
  {
    gAccel = gAccel_;
  }

  void Physics::updateObj( DynObject *obj_ )
  {
    obj = obj_;

    assert( obj->flags & Object::DYNAMIC_BIT );
    assert( obj->sector != null );

    if( obj->flags & Object::CLIP_BIT ) {
      // clear lower object if doesn't exist any more
      if( obj->lower >= 0 &&
          ( obj->lower >= world.objects.length() || world.objects[obj->lower] == null ) )
      {
        obj->lower = -1;
        obj->flags &= ~Object::DISABLED_BIT;
      }
      // check if object can still remain disabled
      else if( obj->flags & Object::DISABLED_BIT ) {
        if( obj->lower >= 0 && !( world.objects[obj->lower]->flags & Object::DISABLED_BIT ) ) {
          obj->flags &= ~Object::DISABLED_BIT;
        }
        if( obj->flags & Object::UNDER_WATER_BIT ) {
          obj->flags &= ~Object::DISABLED_BIT;
        }
      }
      // disable object if it is still and on surface
      else {
        bool isStill = obj->newVelocity.isZero();
        bool isOnFloor = obj->flags & Object::ON_FLOOR_BIT;
        bool isOnStillObject = obj->lower > 0 &&
            ( (DynObject*) world.objects[obj->lower] )->newVelocity.isZero();

        if( isStill && ( isOnFloor || isOnStillObject ) ) {
          obj->flags |= Object::DISABLED_BIT;
          obj->frictEnd();
        }
      }
      // handle physics
      if( !( obj->flags & Object::DISABLED_BIT ) ) {
        if( handleObjFriction() ) {
          // if objects is still in movement or not on a still surface after friction changed its
          // velocity, handle physics
          handleObjMove();
          obj->newVelocity *= 1.0 - leftRatio;
        }
        obj->velocity = obj->newVelocity;
      }
    }
    else {
      if( !( obj->flags & Object::DISABLED_BIT ) ) {
        if( obj->newVelocity * obj->newVelocity <= STICK_VELOCITY ) {
          obj->newVelocity.setZero();
          obj->flags |= Object::DISABLED_BIT;
        }
        else {
          obj->newVelocity *= 1.0 - AIR_FRICTION;
        }

        obj->p += obj->newVelocity * timer.frameTime;
        obj->velocity = obj->newVelocity;

        Sector *sector = world.getSector( obj->p );

        if( obj->sector != sector ) {
          obj->sector->objects.remove( obj );
          sector->objects << obj;
          obj->sector = sector;
        }
      }
    }
  }

}
