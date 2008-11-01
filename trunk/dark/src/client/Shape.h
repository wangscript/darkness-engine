/*
 *  Shape.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Shape_h_
#define _Client_Shape_h_

#include "matrix/bv.h"
#include "Context.h"

namespace Dark
{
namespace Client
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

#endif // _Client_Shape_h_
