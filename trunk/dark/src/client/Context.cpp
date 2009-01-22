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

namespace Dark
{

  Context context;

  Context::~Context()
  {
    free();
  }

  void Context::init()
  {
    logFile.println( "Context created" );
  }

  uint Context::buildTexture( const ubyte *data, int width, int height, int bytesPerPixel,
                              bool wrap, int magFilter, int minFilter )
  {
    assert( glGetError() == GL_NO_ERROR );

    GLenum format = bytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    uint texNum;
    glGenTextures( 1, &texNum );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glBindTexture( GL_TEXTURE_2D, texNum );

    if( minFilter >= GL_NEAREST_MIPMAP_NEAREST ) {
      gluBuild2DMipmaps( GL_TEXTURE_2D, bytesPerPixel, width, height, format,
                         GL_UNSIGNED_BYTE, data );
    }
    else {
      glTexImage2D( GL_TEXTURE_2D, 0, bytesPerPixel, width, height, 0, format,
                    GL_UNSIGNED_BYTE, data );
    }

    if( !wrap ) {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    if( glGetError() != GL_NO_ERROR ) {
      glDeleteTextures( 1, &texNum );
      texNum = 0;

      do {
      }
      while( glGetError() != GL_NO_ERROR );
    }
    return texNum;
  }

  uint Context::buildNormalmap( ubyte *data, const Vec3 &lightNormal, int width, int height,
                                int bytesPerPixel, bool wrap, int magFilter, int minFilter )
  {
    assert( glGetError() == GL_NO_ERROR );

    ubyte *dataEnd = data + width * height * bytesPerPixel;

    for( ubyte *p = data; p < dataEnd; p += bytesPerPixel ) {
      float x = ( (float) p[0] - 128.0f ) / 128.0f;
      float y = ( (float) p[1] - 128.0f ) / 128.0f;
      float z = ( (float) p[2] - 128.0f ) / 128.0f;

      float dot = x * lightNormal.x + y * lightNormal.y + z * lightNormal.z;
      ubyte color = (ubyte) bound( dot * 256.0f, 0.0f, 255.0f );

      p[0] = color;
      p[1] = color;
      p[2] = color;
    }

    GLenum format = bytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    uint texNum;
    glGenTextures( 1, &texNum );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glBindTexture( GL_TEXTURE_2D, texNum );

    if( minFilter >= GL_NEAREST_MIPMAP_NEAREST ) {
      gluBuild2DMipmaps( GL_TEXTURE_2D, bytesPerPixel, width, height, format,
                         GL_UNSIGNED_BYTE, data );
    }
    else {
      glTexImage2D( GL_TEXTURE_2D, 0, bytesPerPixel, width, height, 0, format,
                    GL_UNSIGNED_BYTE, data );
    }

    if( !wrap ) {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    if( glGetError() != GL_NO_ERROR ) {
      glDeleteTextures( 1, &texNum );
      texNum = 0;

      do {
      }
      while( glGetError() != GL_NO_ERROR );
    }
    return texNum;
  }

  uint Context::createTexture( int contextId, const ubyte *data, int width, int height,
                               int bytesPerPixel, bool wrap, int magFilter, int minFilter )
  {
    assert( contextId < entries.length() &&
        !freeEntries.contains( entries.dataPtr() + contextId ) );

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
    assert( contextId < entries.length() &&
        !freeEntries.contains( entries.dataPtr() + contextId ) );

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
    assert( contextId < entries.length() &&
        !freeEntries.contains( &entries[contextId] ) );

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
    assert( contextId < entries.length() &&
        !freeEntries.contains( &entries[contextId] ) );

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

  uint Context::genLists( int count )
  {
    ContextList list;

    list.base = glGenLists( count );
    list.count = count;

    lists << list;

    return list.base;
  }

  void Context::free()
  {
  }

}
