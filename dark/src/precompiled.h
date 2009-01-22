/*
 *  precompiled.h
 *
 *  Precompiled header.
 *  It should be included in all ".cpp" source files in the project. Do not include it via another
 *  header, it will not work in GCC (and many other compilers).
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

// defining NDEBUG disables assert macro
// #define NDEBUG

#define DARK_USE_REUSER

#include "base/base.h"

// include SDL, OpenGL and OpenAL since they are commonly used
#ifdef WIN32

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_opengl.h>
# include <al.h>
# include <alc.h>
# include <AL/alut.h>

#else

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_opengl.h>
# include <AL/al.h>
# include <AL/alc.h>
# include <AL/alut.h>

#endif
