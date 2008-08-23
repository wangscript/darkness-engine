/*
 *  Weapon.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Weapon.h"

#include "Translator.h"

namespace Dark
{

  Weapon::Weapon( const Vec3 &p_ )
  {
    p = p_,
    dim = Vec3( 0.3, 0.3, 0.3 );

    flags = 0;
    type = 0;

    damage = Math::INF;
  }
}
