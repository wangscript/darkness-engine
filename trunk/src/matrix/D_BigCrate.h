/*
 *  D_BigCrate.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: D_BigCrate.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _D_BigCrate_h_
#define _D_BigCrate_h_

#include "DynObject.h"
#include "Translator.h"

namespace Dark
{

  class D_BigCrate : public DynObject
  {
    protected:

      void onDestroy();
      void onFrictBegin();
      void onFrictEnd();

    public:

      static const int TYPE = D_BIG_CRATE;
      static const char *NAME;

      Object *content;

      explicit D_BigCrate( const Vec3 &p = Vec3::zero(), Object *content = null );
      ~D_BigCrate();
  };

}

#endif // _D_BigCrate_h_
