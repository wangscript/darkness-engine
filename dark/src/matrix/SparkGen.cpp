/*
 *  SparkGen.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "SparkGen.h"

namespace Dark
{

  SparkGen::SparkGen( const Vec3 &p_, int number_,
                      const Vec3 &velocity_, float velocitySpread_,
                      const Vec3 &color_, const Vec3 &colorSpread_,
                      const Vec3 &gravity_, float lifeTime_ ) :
    p( p_ ), index( -1 ), sector( null ),
    number( number_ ),
    velocity( velocity_ ), velocitySpread( velocitySpread_ ),
    color( color_ ), colorSpread( colorSpread_ ),
    gravity( gravity_ ), lifeTime( lifeTime_ )
  {}

}
