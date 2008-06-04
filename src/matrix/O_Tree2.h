/*
 *  O_Tree2.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: O_Tree2.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _O_Tree2_h_
#define _O_Tree2_h_

#include "Object.h"
#include "Translator.h"

namespace Dark
{

  struct O_Tree2 : Object
  {
    protected:

      void onDestroy();

    public:

      static const int TYPE = O_TREE2;
      static const char *NAME;

      explicit O_Tree2( const Vec3 &p );
      O_Tree2( float x, float y );

      void load( FILE *stream );
      void save( FILE *stream );
  };

}

#endif // _O_Tree2_h_
