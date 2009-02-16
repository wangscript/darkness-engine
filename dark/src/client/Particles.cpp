/*
 *  Particles.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Particles.h"

#include "Context.h"

namespace Dark
{
namespace Client
{

  Particles particles;

  void Particles::init( int contextId )
  {
    uint first = context.genList( contextId );
  }

  void Particles::free()
  {
  }

}
}
