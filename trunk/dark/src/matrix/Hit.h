/*
 *  Hit.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Hit.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Hit_h_
#define _Hit_h_

#include "base.h"

namespace Dark
{

  class Object;

  struct Hit
  {
    float  ratio;

    Vec3   normal;
    Object *obj;
    Object *sObj;
    bool   isInWater;
  };

}

#endif // _Hit_h_
