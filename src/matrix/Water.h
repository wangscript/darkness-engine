/*
 *  Water.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Water.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Water_h_
#define _Water_h_

#include "Object.h"
#include "Translator.h"

namespace Dark
{

  class Water : public Object
  {
    protected:

      void onUpdate();

    public:

      static const char *NAME;
      static const int TYPE = WATER;

      Water( const Vec3 &p, const Vec3 &dim );
  };

}

#endif // _Water_h_
