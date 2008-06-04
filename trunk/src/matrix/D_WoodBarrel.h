/*
 *  D_WoodBarrel.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: D_WoodBarrel.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _D_WoodBarrel_h_
#define _D_WoodBarrel_h_

#include "DynObject.h"
#include "Translator.h"

namespace Dark
{

  class D_WoodBarrel : public DynObject
  {
    protected:

      void onDestroy();
      void onFrictBegin();
      void onFrictEnd();

    public:

      static const int TYPE = D_WOOD_BARREL;
      static const char *NAME;

      Object *content;

      explicit D_WoodBarrel( const Vec3 &p = Vec3::zero() );
      ~D_WoodBarrel();
  };

}

#endif // _D_WoodBarrel_h_
