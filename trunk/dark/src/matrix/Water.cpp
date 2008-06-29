/*
 *  Water.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Water.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "Water.h"

#include "Collider.h"
#include "DynObject.h"

namespace Dark
{

  const char *Water::NAME = "Water";

  Water::Water( const Vec3 &p_, const Vec3 &dim_ )
  {
    p = p_;
    dim = dim_;

    flags = Object::UPDATE_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;

    model = LIST_WATER;
  }

  void Water::onUpdate()
  {
    Vector<Object*> objects;
    collider.getOverlaps( *this, &objects, null );

    const int iMax = objects.length();
    for( int i = 0; i < iMax; i++ ) {
      DynObject *obj = (DynObject*) objects[i];

      if( obj->flags & Object::DYNAMIC_BIT ) {
        obj->flags |= Object::ON_WATER_BIT;

        if( !( obj->flags & Object::IN_WATER_BIT ) ) {
          obj->flags |= Object::IN_WATER_BIT;

          if( obj->newVelocity.z < -4.0 ) {
            obj->addSound( SND_SPLASH_HARD );
          }
          else if( obj->newVelocity.z < -2.0 ) {
            obj->addSound( SND_SPLASH_SOFT );
          }
        }
        if( includes( obj->p ) ) {
          obj->flags |= Object::UNDER_WATER_BIT;
          obj->flags &= ~Object::ON_FLOOR_BIT;
          obj->lower = -1;

          obj->frictEnd();
        }
      }
    }
  }

}
