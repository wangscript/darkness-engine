/*
 *  Structure.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Structure_h_
#define _Structure_h_

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

#endif // _Structure_h_
