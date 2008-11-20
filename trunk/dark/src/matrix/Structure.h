/*
 *  Structure.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "bv.h"

namespace Dark
{

  struct Structure : Bounds
  {
    Vec3 p;

    int  index;
    int  bsp;

    float damage;

    Structure();

    Structure( const Vec3 &p, int bsp );
  };

}
