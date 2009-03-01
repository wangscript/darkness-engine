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

namespace oz
{

  const char *Ladder::NAME = "Ladder";
  const int Ladder::TYPE = String::hash( Ladder::NAME );

  Ladder::Ladder( const Vec3 &p_, const Vec3 &dim_ )
  {
    p = p_;
    dim = dim_;

    flags = Object::UPDATE_FUNC_BIT;
    type = TYPE;

    damage = Math::INF;
  }

  void Ladder::onUpdate()
  {
    Vector<Object*> objects;
    collider.getOverlaps( *this, &objects, null );

    const int iMax = objects.length();
    for( int i = 0; i < iMax; i++ ) {
      DynObject *obj = (DynObject*) objects[i];

      if( obj->flags & Object::CLIMBER_BIT ) {
        obj->setOnLadder();
      }
    }
  }

}
