/*
 *  Hit.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace oz
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
