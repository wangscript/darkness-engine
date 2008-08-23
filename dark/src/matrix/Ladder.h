/*
 *  Ladder.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Ladder_h_
#define _Ladder_h_

#include "Object.h"
#include "Translator.h"

namespace Dark
{

  class Ladder : public Object
  {
    protected:

      void onUpdate();

    public:

      static const char *NAME;
      static const int TYPE = LADDER;

      Ladder( const Vec3 &p, const Vec3 &dim );
  };

}

#endif // _Ladder_h_
