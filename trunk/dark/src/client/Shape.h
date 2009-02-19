/*
 *  Shape.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "matrix/bv.h"
#include "Context.h"

namespace Dark
{
namespace Client
{

  struct Shape
  {
    uint spark;

    uint genRandomTetrahedicParticle( uint list, float size );
    uint genRandomCubicParticle( uint list, float size );
    uint genBox( uint list, const AABB &bb, uint texture );
    void drawBox( const AABB &bb );

    void init( int contextId );
    void free();
  };

  extern Shape shape;

}
}
