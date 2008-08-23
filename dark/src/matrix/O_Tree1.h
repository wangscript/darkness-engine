/*
 *  O_Tree1.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _O_Tree1_h_
#define _O_Tree1_h_

#include "Object.h"
#include "Translator.h"

namespace Dark
{

  struct O_Tree1 : Object
  {
    protected:

      void onDestroy();

    public:

      static const int TYPE = O_TREE1;
      static const char *NAME;

      explicit O_Tree1( const Vec3 &p );
      O_Tree1( float x, float y );

      void load( FILE *stream );
      void save( FILE *stream );
  };

}

#endif // _O_Tree1_h_
