/*
 *  precompiled.h
 *
 *  Precompiled header.
 *  Should be included in all ".cpp" source files in project. Do not include it via another header,
 *  it will not work in GCC. Additionaly, precompiled header does not work with "-g3" option.
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

// defining NDEBUG disables assert macro
// #define NDEBUG

#define DARK_FLOAT_SCALAR
#define DARK_USE_REUSER

#include "base.h"

// include essential SDL since it is commonly used
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
