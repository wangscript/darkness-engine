/*
 *  Weapon.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Weapon.h 11 2007-08-31 12:03:10Z davorin $
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
