/*
 *  Weapon.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Weapon.cpp 11 2007-08-31 12:03:10Z davorin $
 */

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
