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

namespace oz
{
namespace Client
{

  Particles particles;

  void Particles::init()
  {
    uint first = context.genList();
  }

  void Particles::free()
  {
  }

}
}
