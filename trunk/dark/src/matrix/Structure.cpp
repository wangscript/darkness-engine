/*
 *  Structure.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Structure.h"

namespace Dark
{

  Structure::Structure() {
  }

  Structure::Structure( const Vec3 &p_, int bsp_ ) : p( p_ ), bsp( bsp_ )
  {}

}
