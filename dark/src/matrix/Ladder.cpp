/*
 *  Ladder.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Ladder.h"

#include "Collider.h"
#include "DynObject.h"

namespace Dark
{

  const char *Ladder::NAME = "Ladder";

  Ladder::Ladder( const Vec3 &p_, const Vec3 &dim_ )
  {
    p = p_;
    dim = dim_;

    flags = Object::UPDATE_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;

    model = -1;
  }

  void Ladder::onUpdate()
  {
    Vector<Object*> objects;
    collider.getOverlaps( *this, &objects, null );

    const int iMax = objects.length();
    for( int i = 0; i < iMax; i++ ) {
      DynObject *obj = (DynObject*) objects[i];

      if( obj->flags & Object::DYNAMIC_BIT ) {
      }
    }
  }

}
