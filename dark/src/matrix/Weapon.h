/*
 *  Weapon.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Weapon_h_
#define _Weapon_h_

#include "Object.h"

namespace Dark
{

  struct Weapon : Object
  {
    explicit Weapon( const Vec3 &p = Vec3::zero() );
  };

}

#endif // _Weapon_h_
