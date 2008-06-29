/*
 *  B_Spirit.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: B_Spirit.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "B_Spirit.h"

#include "Collider.h"

namespace Dark
{

  const char *B_Spirit::NAME = "B_Spirit";

  const Vec3  B_Spirit::CAM_POS       = Vec3( 0.00, 0.00, 0.13 );
  const float B_Spirit::BOB_INC       = 0.04;
  const float B_Spirit::BOB_AMPLITUDE = 0.03;
  const float B_Spirit::WALK_VELOCITY = 0.15;
  const float B_Spirit::RUN_VELOCITY  = 0.5;
  const float B_Spirit::GRAB_DIST     = 1.0;

  B_Spirit::B_Spirit( const Vec3 &p_, float h_, float v_, Mind *mind_ )
  {
    p       = p_;
    dim     = Vec3( 0.29, 0.29, 0.29 );

    flags   = Object::UPDATE_FUNC_BIT | Object::DYNAMIC_BIT | Object::HOVER_BIT |
        Object::SPIRIT_BIT | Object::BOT_BIT;
    type    = B_SPIRIT;
    damage  = Math::INF;

    model   = ~0;
    anim    = ANIM_STAND;

    newVelocity.setZero();
    lower   = -1;
    mass    = 5.0;

    h       = h_;
    v       = v_;

    camPos  = Vec3( 0.00, 0.00, 0.13 );
    bob     = 0.0;

    state   = 0;
    keys    = 0;
    oldKeys = 0;

    mind    = mind_;

    origin  = Vec3::zero();
  }

  void B_Spirit::onUpdate()
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
        else {
          anim = ANIM_STAND;
        }
      }
      else {
        anim = ANIM_JUMP;
      }
    }

    // { hsine, hcosine, vsine, vcosine, vcosine * hsine, vcosine * hcosine }
    float hvsc[6];

    Math::sincos( Math::rad( h ), &hvsc[0], &hvsc[1] );
    Math::sincos( Math::rad( v ), &hvsc[2], &hvsc[3] );

    hvsc[4] = hvsc[3] * hvsc[0];
    hvsc[5] = hvsc[3] * hvsc[1];

    // BOT SPECIFIC UPDATE BEGIN
    camPos.z = CAM_POS.z + BOB_AMPLITUDE * Math::sin( bob );
    bob += BOB_INC;

    if( ( keys & KEY_RUN ) && !( oldKeys & KEY_RUN ) ) {
      state ^= RUNNING_BIT;
    }

    if( ( keys & KEY_NOCLIP ) && !( oldKeys & KEY_NOCLIP ) ) {
      flags ^= Object::CLIP_BIT;
    }

    float velocity = ( state & RUNNING_BIT ) ? RUN_VELOCITY : WALK_VELOCITY;

    Vec3 move = Vec3::zero();

    if( keys & KEY_FORWARD ) {
      flags &= ~DISABLED_BIT;

      move.x -= hvsc[4];
      move.y += hvsc[5];
      move.z += hvsc[2];
    }
    if( keys & KEY_BACKWARD ) {
      flags &= ~DISABLED_BIT;

      move.x += hvsc[4];
      move.y -= hvsc[5];
      move.z -= hvsc[2];
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
    if( keys & KEY_JUMP ) {
      flags &= ~DISABLED_BIT;

      move.z += 1.0;
    }
    if( keys & KEY_CROUCH ) {
      flags &= ~DISABLED_BIT;

      move.z -= 1.0;
    }
    newVelocity += velocity * ( move.isZero() ? move : move.norm() );

    // BOT SPECIFIC UPDATE END
    if( ( keys & KEY_FIRE ) && !( oldKeys & KEY_FIRE ) ) {
      p = origin;
      newVelocity = Vec3::zero();
    }

    oldKeys = keys;
    keys = 0;
  }

  void B_Spirit::load( FILE *stream )
  {
    stream = null;
  }

  void B_Spirit::save( FILE *stream )
  {
    stream = null;
  }

}
