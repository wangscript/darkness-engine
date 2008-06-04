/*
 *  B_Human.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: B_Human.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "B_Human.h"

#include "Translator.h"
#include "Physics.h"

namespace Dark
{

  const char *B_Human::NAME = "B_Human";

  const Vec3  B_Human::CAM_POS            = Vec3( 0.00, 0.00, 0.73 );
  const Vec3  B_Human::CAM_POS_CROUCH     = Vec3( 0.00, 0.00, 0.23 );
  const Vec3  B_Human::DIM                = Vec3( 0.29, 0.29, 0.89 );
  const Vec3  B_Human::DIM_CROUCH         = Vec3( 0.29, 0.29, 0.39 );

  const float B_Human::BOB_INC            = 0.05;
  const float B_Human::BOB_AMPLITUDE      = 0.05;

  const float B_Human::WALK_VELOCITY      = 0.7;
  const float B_Human::RUN_VELOCITY       = 1.5;
  const float B_Human::JUMP_VELOCITY      = 4.5;
  const float B_Human::CROUCH_VELOCITY    = 0.5;
  const float B_Human::AIR_CONTROL        = 0.15;
  const float B_Human::GRAB_DIST          = 1.0;

  const float B_Human::STEP_INC           = 0.1;
  const float B_Human::STEP_MAX           = 0.5;

  B_Human::B_Human( const Vec3 &p_, float h_, float v_, Mind *mind_ )
  {
    p       = p_;
    dim     = DIM;

    flags   = Object::UPDATE_FUNC_BIT | Object::HIT_FUNC_BIT | Object::CLIP_BIT |
        Object::DYNAMIC_BIT | Object::PUSHING_BIT | Object::BOT_BIT;
    type    = B_HUMAN;

    damage  = 2.0;

    model   = ~0;
    anim    = ANIM_STAND;

    newVelocity.setZero();
    lower   = -1;
    mass    = 50.0;

    h       = h_;
    v       = v_;

    camPos  = CAM_POS;
    bob     = 0.0;

    state   = STEPPING_BIT;
    keys    = 0;
    oldKeys = 0;

    mind    = mind_;
  }

  void B_Human::onUpdate()
  {
    h = Math::mod( h + 360.0, 360.0 );
    v = bound( v, -89.0, 89.0 );

    rotZ = h;

    if( state & CROUCHING_BIT ) {
      if( state & MOVING_BIT ) {
        anim = ANIM_CROUCH_WALK;
      }
      else {
        anim = ANIM_CROUCH_STAND;
      }
    }
    else {
      anim = ANIM_STAND;

      if( state & GROUNDED_BIT ) {
        if( state & MOVING_BIT ) {
          anim = ANIM_RUN;
        }
        else if( state & GESTURE0_BIT ) {
          anim = ANIM_FLIP;
        }
        else if( state & GESTURE0_BIT ) {
          anim = ANIM_WAVE;
        }
        else if( state & GESTURE1_BIT ) {
          anim = ANIM_SALUTE;
        }
      }
    }

    // { hsine, hcosine, vsine, vcosine, vcosine * hsine, vcosine * hcosine }
    float hvsc[6];

    Math::sincos( Math::rad( h ), &hvsc[0], &hvsc[1] );
    Math::sincos( Math::rad( v ), &hvsc[2], &hvsc[3] );

    hvsc[4] = hvsc[3] * hvsc[0];
    hvsc[5] = hvsc[3] * hvsc[1];

    // BOT SPECIFIC UPDATE BEGIN
    if( lower >= 0 || ( flags & Object::ON_FLOOR_BIT ) ) {
      state |= GROUNDED_BIT;
    }
    else {
      state &= ~GROUNDED_BIT;
    }

    if( ( keys & KEY_RUN ) && !( oldKeys & KEY_RUN ) ) {
      state ^= RUNNING_BIT;
    }

    if( ( keys & KEY_STEP ) && !( oldKeys & KEY_STEP ) ) {
      state ^= STEPPING_BIT;
    }

    if( keys & KEY_GESTURE0 ) {
      state |= GESTURE0_BIT;
    }
    else {
      state &= ~GESTURE0_BIT;
    }
    if( keys & KEY_GESTURE1 ) {
      state |= GESTURE1_BIT;
    }
    else {
      state &= ~GESTURE1_BIT;
    }

    if( ( keys & KEY_JUMP ) && ( state & GROUNDED_BIT ) ) {
      flags &= ~DISABLED_BIT;

      newVelocity.z = JUMP_VELOCITY;
      addSound( SND_JUMP );
      return;
    }
    if( ( keys & KEY_CROUCH ) && !( oldKeys & KEY_CROUCH ) ) {
      flags &= ~DISABLED_BIT;

      if( state & CROUCHING_BIT ) {
        float oldZ = p.z;

        p.z += DIM.z - DIM_CROUCH.z + 0.1;
        dim = DIM;

        if( collider.test( *this, this ) ) {
          camPos = CAM_POS;
          state  &= ~CROUCHING_BIT;
        }
        else {
          dim = DIM_CROUCH;
          p.z = oldZ;
        }
      }
      else {
        p.z    += dim.z - DIM_CROUCH.z;
        dim.z  = DIM_CROUCH.z;
        camPos = CAM_POS_CROUCH;

        lower =  -1;
        flags &= ~Object::ON_FLOOR_BIT;
        state |= CROUCHING_BIT;
      }
    }

    float velocity = ( state & CROUCHING_BIT ) ? CROUCH_VELOCITY :
        ( state & RUNNING_BIT ) ? RUN_VELOCITY : WALK_VELOCITY;

    if( !( state & GROUNDED_BIT ) ) {
      velocity *= AIR_CONTROL;
    }

    Vec3 move = Vec3::zero();

    if( keys & KEY_FORWARD ) {
      flags &= ~DISABLED_BIT;

      move.x -= hvsc[0];
      move.y += hvsc[1];
    }
    if( keys & KEY_BACKWARD ) {
      flags &= ~DISABLED_BIT;

      move.x += hvsc[0];
      move.y -= hvsc[1];
    }
    if( keys & KEY_RIGHT ) {
      flags &= ~DISABLED_BIT;

      move.x += hvsc[1];
      move.y += hvsc[0];
    }
    if( keys & KEY_LEFT ) {
      flags &= ~DISABLED_BIT;

      move.x -= hvsc[1];
      move.y -= hvsc[0];
    }

    Vec3 addVelocity = velocity * move;

    if( ( flags & Object::ON_FLOOR_BIT ) && floor.z != 1.0 ) {
      float dot = addVelocity * floor;

      if( dot > 0.0 ) {
        addVelocity -= dot * floor;
      }
    }

    newVelocity += addVelocity;

    if( state & STEPPING_BIT ) {
      Vec3 desiredMove = newVelocity * timer.frameTime;

      collider.translate( *this, desiredMove, this );

      float orgRatio = collider.hit.ratio;

      if( orgRatio != 1.0 && collider.hit.normal.z == 0.0 ) {
        float orgZ = p.z;

        for( float raise = STEP_INC; raise < STEP_MAX; raise += STEP_INC ) {
          p.z += STEP_INC;

          if( !collider.test( *this, this ) ) {
            break;
          }
          else {
            collider.translate( *this, desiredMove, this );

            if( collider.hit.ratio > orgRatio + EPSILON ) {
              goto stepSucceeded;
            }
          }
        }
        p.z = orgZ;
        stepSucceeded:;
      }
    }

    // BOT SPECIFIC UPDATE END
    if( ( keys & KEY_USE ) && !( oldKeys & KEY_USE ) ) {
      Vec3 look( -hvsc[4], hvsc[5], hvsc[2] );

      collider.translate( p + camPos, look * GRAB_DIST );

      if( collider.hit.sObj != null ) {
        collider.hit.sObj->destroy();
      }
    }

    oldKeys = keys;
    keys = 0;
  }

  void B_Human::onHit( const Hit *hit )
  {
    float deltaVel = ( newVelocity - velocity ).sqL();

    if( deltaVel >= 1000.0 ) {
      damage += deltaVel;
    }

    if( !( state & GROUNDED_BIT ) && hit->normal.z >= Physics::FLOOR_NORMAL_Z && deltaVel > 4.0 ) {
      addSound( SND_LAND );
    }
  }

  void B_Human::onDestroy()
  {
    world.remove( this );
  }

}
