/*
 *  Water_Dual.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Water.h 30 2008-11-01 16:58:09Z Davorin.Ucakar $
 */

#pragma once

#include "matrix/Object.h"

namespace Dark
{

  class Water_Dual
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

  extern Water_Dual water_dual;

}
