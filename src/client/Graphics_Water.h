/*
 *  Graphics_Water.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_Water.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Graphics_Water_h_
#define _Graphics_Water_h_

#include "Object.h"

namespace Dark
{
namespace Graphics
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

#endif // _Graphics_Water_h_
