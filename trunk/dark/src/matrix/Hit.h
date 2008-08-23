/*
 *  Hit.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Hit_h_
#define _Hit_h_

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
