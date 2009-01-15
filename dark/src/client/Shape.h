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
  struct Shape
  {
    uint spark;

    void genRandomTetrahedicParticle( uint list, float size );
    void genRandomCubicParticle( uint list, float size );
    void genBox( uint list, const AABB &bb, uint texture );
    void drawBox( const AABB &bb );

    void init();
    void free();
  };

  extern Shape shape;

}
