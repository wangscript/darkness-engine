/*
 *  D_SmallCrate.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _D_SmallCrate_h_
#define _D_SmallCrate_h_

#include "DynObject.h"
#include "Translator.h"

namespace Dark
{

  class  D_SmallCrate : public DynObject
  {
    protected:

      void onDestroy();
      void onFrictBegin();
      void onFrictEnd();

    public:

      static const int TYPE = D_SMALL_CRATE;
      static const char *NAME;

      Object *content;

      explicit D_SmallCrate( const Vec3 &p = Vec3::zero(), Object *content = null );
      ~D_SmallCrate();
  };

}

#endif // _D_SmallCrate_h_
