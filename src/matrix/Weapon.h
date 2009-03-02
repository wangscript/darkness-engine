/*
 *  Weapon.h
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

  struct Weapon : Object
  {
    explicit Weapon( const Vec3 &p = Vec3::zero() );
  };

}
