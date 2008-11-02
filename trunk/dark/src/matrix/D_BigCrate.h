/*
 *  D_BigCrate.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
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

      static const char *NAME;
      static const int TYPE;

      Object *content;

      explicit D_BigCrate( const Vec3 &p = Vec3::zero(), Object *content = null );
      ~D_BigCrate();
  };

}

#endif // _D_BigCrate_h_
