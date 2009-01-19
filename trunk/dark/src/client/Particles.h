/*
 *  Particles.h
 *
 *  Loads and/or generates GL lists for common particles.
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  struct Particles
  {
    uint spark;

    void init();
    void free();
  };

  extern Particles particles;

}
