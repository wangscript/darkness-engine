/*
 *  Water.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Water_h_
#define _Client_Water_h_

#include "matrix/Object.h"

namespace oz
{
namespace Client
{

  class Water
  {
    protected:

      static const float TEX_STRETCH;
      static const float TEX_BIAS;

      static const float ALPHA;

      uint texture;
      float phi;
      float ratio;

      float alpha1;
      float alpha2;

    public:

      static const float COLOR[];
      static const float VISIBILITY;

      void init();

      void update();
      void draw( const Object *obj, bool isInside );
  };

  extern Water water;

}
}

#endif // _Client_Water_h_
