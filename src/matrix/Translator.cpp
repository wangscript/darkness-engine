/*
 *  Translator.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Translator.h"

namespace Dark
{

  Translator translator;

  const char * const Translator::textures[] =
  {
    "tex/particle.png",
    "tex/crate1.jpg",
    "tex/crate2.jpg",
    "tex/roof1.jpg",
    "tex/stone1.jpg",
    "tex/stone2.jpg",
    "tex/stone3.jpg",
    "tex/wood1.jpg",
    "tex/wood2.jpg",
    null
  };

  const char * const Translator::sounds[] =
  {
    "snd/friction_soft1.wav",
    "snd/friction_hard1.wav",
    "snd/hit_soft1.wav",
    "snd/hit_hard1.wav",
    "snd/splash_soft1.wav",
    "snd/splash_hard1.wav",
    "snd/land1.wav",
    "snd/jump1.wav",
    null
  };

  Translator::Translator()
  {
    for( nTextures = 0; textures[nTextures] != null; nTextures++ ) {
      textureIndices.add( textures[nTextures], nTextures );
    }
  }

  int Translator::getTexture( const char *name )
  {
    if( textureIndices.contains( name ) ) {
      return textureIndices.cachedValue();
    }
    else {
      return -1;
    }
  }

  Translator::~Translator()
  {
    textureIndices.free();
    textureIndices.deallocate();
  }

}
