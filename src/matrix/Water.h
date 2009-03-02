/*
 *  Water.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

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
      static const int TYPE;

      Water( const Vec3 &p, const Vec3 &dim );
  };

}
