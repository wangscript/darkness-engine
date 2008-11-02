/*
 *  D_MetalBarrel.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _D_MetalBarrel_h_
#define _D_MetalBarrel_h_

#include "DynObject.h"
#include "Translator.h"

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

      explicit D_MetalBarrel( const Vec3 &p = Vec3::zero() );
  };

}

#endif // _D_MetalBarrel_h_
