/*
 *  O_Tree1.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "Object.h"

namespace Dark
{

  struct O_Tree1 : Object
  {
    protected:

      void onDestroy();

    public:

      static const char *NAME;
      static const int TYPE;

      static Object *build( const Vec3 &p );

      explicit O_Tree1( const Vec3 &p );
      O_Tree1( float x, float y );

      void load( FILE *stream );
      void save( FILE *stream );
  };

}
