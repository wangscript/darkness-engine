/*
 *  D_MetalBarrel.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "DynObject.h"

namespace Dark
{

  class D_MetalBarrel : public DynObject
  {
    protected:

      void onDestroy();
      void onFrictBegin();
      void onFrictEnd();

    public:

      static const char *NAME;
      static const int TYPE;

      static Object *build( const Vec3 &p );

      explicit D_MetalBarrel( const Vec3 &p = Vec3::zero() );
  };

}
