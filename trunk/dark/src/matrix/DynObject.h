/*
 *  DynObject.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "Object.h"

namespace Dark
{

  // dynamic object abstract class
  class DynObject : public Object
  {
    public:

      static const float DEFAULT_MASS;
      static const float DEFAULT_LIFT;

      Vec3    velocity;
      Vec3    newVelocity;  // temporary velocity for the next frame

      float   mass;
      float   lift;

      int     lower;        // index of lower object

      // if on ground, used as floor normal, if on other DynObject, used as a relative position
      // to the lower object, needed to synchronize moving with the lower object
      Vec3    floor;

    protected:

      virtual void onFrictBegin()
      {}

      virtual void onFrictEnd()
      {}

    public:

      DynObject() : velocity( Vec3::zero() ), newVelocity( Vec3::zero() ),
          mass( DEFAULT_MASS ), lift( DEFAULT_LIFT ), lower( -1 )
      {}

      void frictBegin()
      {
        if( ( flags & FRICT_FUNC_BIT ) && !( flags & FRICTING_BIT ) ) {
          flags |= FRICTING_BIT;
          onFrictBegin();
        }
      }

      void frictEnd()
      {
        if( ( flags & FRICT_FUNC_BIT ) && ( flags & FRICTING_BIT ) ) {
          flags &= ~FRICTING_BIT;
          onFrictEnd();
        }
      }

      void setInWater( const AABB &water )
      {
        flags |= Object::ON_WATER_BIT;

        if( !( flags & Object::IN_WATER_BIT ) ) {
          flags |= Object::IN_WATER_BIT;

          if( newVelocity.z < -4.0f ) {
            addSound( SND_SPLASH_HARD );
          }
          else if( newVelocity.z < -2.0f ) {
            addSound( SND_SPLASH_SOFT );
          }
        }
        if( water.includes( p ) ) {
          flags |= Object::UNDER_WATER_BIT;
          flags &= ~Object::ON_FLOOR_BIT;
          lower = -1;

          frictEnd();
        }
      }

      virtual void load( FILE *stream );
      virtual void save( FILE *stream );
  };

}
