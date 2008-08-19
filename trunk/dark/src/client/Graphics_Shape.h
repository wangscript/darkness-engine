/*
 *  Graphics_Shape.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_Shape_h_
#define _Graphics_Shape_h_

#include "bv.h"
#include "Graphics_Context.h"

#include <SDL/SDL_opengl.h>

namespace Dark
{
namespace Graphics
{

  class Shape
  {
    public:

      uint genRandomTetrahedicParticle( float size );
      uint genRandomCubicParticle( float size );

      uint genBox( const AABB &bb, uint texture );

      void drawBox( const AABB &bb );
  };

  extern Shape shape;

}
}

#endif // _Graphics_Shape_h_
