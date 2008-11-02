/*
 *  Water.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Water.h"

#include "Collider.h"
#include "DynObject.h"

namespace Dark
{

  const char *Water::NAME = "Water";
  const int Water::TYPE = String::hash( Water::NAME );

  Water::Water( const Vec3 &p_, const Vec3 &dim_ )
  {
    p = p_;
    dim = dim_;

    flags = Object::UPDATE_FUNC_BIT | Object::WATER_BIT;
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
        obj->setInWater( *this );
      }
    }
  }

}
