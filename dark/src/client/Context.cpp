/*
 *  Context.cpp
 *
 *  Evidenca nalaganja tekstur in listov ter nalagalnik tekstur
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Context.h"

#include "ResourceManager.h"

namespace oz
{
namespace Client
{

  Context context;

  Context::~Context()
  {}

  uint Context::createTexture( const ubyte *data, int width, int height, int bytesPerPixel,
                               bool wrap, int magFilter, int minFilter )
  {
    assert( entries.hasIndex( contextId ) );

    logFile.print( "Creating texture from buffer ..." );

    int texNum = buildTexture( data, width, height, bytesPerPixel, wrap, magFilter, minFilter );

    if( texNum == 0 ) {
      logFile.printRaw( " Error\n" );
    }
    else {
      entries[contextId].textures << new Texture( texNum, 0 );
      logFile.printRaw( " OK" );
    }
    return texNum;
  }

  uint Context::createNormalmap( int contextId, ubyte *data, const Vec3 &lightNormal,
                                 int width, int height, int bytesPerPixel,
                                 bool wrap, int magFilter, int minFilter )
  {
    assert( entries.hasIndex( contextId ) );

    logFile.print( "Creating normalmap texture from buffer ..." );

    int texNum = buildNormalmap( data, lightNormal, width, height, bytesPerPixel, wrap,
                                 magFilter, minFilter );

    if( texNum == 0 ) {
      logFile.printRaw( " Error\n" );
    }
    else {
      entries[contextId].textures << new Texture( texNum, 0 );
      logFile.printRaw( " OK" );
    }
    return texNum;
  }

  uint Context::loadTexture( int contextId, const char *fileName,
                             bool wrap, int magFilter, int minFilter )
  {
    assert( entries.hasIndex( contextId ) );

    logFile.print( "Loading texture from file '%s' ...", fileName );

    if( textures.contains( fileName ) ) {
      logFile.printRaw( " Already loaded\n" );
      return textures.cachedValue().id;
    }

    SDL_Surface *image = IMG_Load( fileName );
    if( image == null ) {
      logFile.printRaw( " No such file\n" );
      return 0;
    }
    if( image->w != image->h ) {
      logFile.printRaw( " Dimensions are not equal" );
    }
    logFile.printRaw( " OK\n" );

    assert( image->w == image->h );

    int bytesPerPixel = image->format->BitsPerPixel / 8;
    int texNum = createTexture( contextId, (const ubyte*) image->pixels, image->w, image->h,
                                bytesPerPixel, wrap, magFilter, minFilter );

    SDL_FreeSurface( image );

    textures[fileName] = Texture( texNum, 1 );
    entries[contextId].textures << &textures.cachedValue();
    return texNum;
  }

  uint Context::loadNormalmap( int contextId, const char *fileName, const Vec3 &lightNormal,
                               bool wrap, int magFilter, int minFilter )
  {
    assert( entries.hasIndex( contextId ) );

    logFile.print( "Loading normalmap texture from file '%s' ...", fileName );

    if( textures.contains( fileName ) ) {
      logFile.printRaw( " Already loaded\n" );
      return textures.cachedValue().id;
    }

    SDL_Surface *image = IMG_Load( fileName );
    if( image == null ) {
      logFile.printRaw( " No such file\n" );
      return 0;
    }
    if( image->w != image->h ) {
      logFile.printRaw( " Dimensions are not equal" );
    }
    logFile.printRaw( " OK\n" );

    assert( image->w == image->h );

    int bytesPerPixel = image->format->BitsPerPixel / 8;
    int texNum = createNormalmap( contextId, (ubyte*) image->pixels, lightNormal,
                                  image->w, image->h, bytesPerPixel, wrap, magFilter, minFilter );

    SDL_FreeSurface( image );

    entries[contextId].textures << new Texture( texNum, 0 );
    return texNum;
  }

  uint Context::genList( int contextId )
  {
    entries[contextId].lists << Lists( glGenLists( 1 ), 1 );
    return entries[contextId].lists.last().base;
  }

  uint Context::genLists( int contextId, int count )
  {
    entries[contextId].lists << Lists( glGenLists( count ), count );
    return entries[contextId].lists.last().base;
  }

  int Context::createContext()
  {
  }

  void Context::freeContext( int context )
  {
    // TODO freeContext
  }

}
}
