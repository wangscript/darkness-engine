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

#include "matrix/Translator.h"

namespace Dark
{
namespace Client
{

  Context context;

  Context::~Context()
  {
    free();
  }

  void Context::init()
  {
    logFile.println( "Context created" );

    loadedTextures = new uint[translator.nTextures];
    aSet( loadedTextures, 0, translator.nTextures );
  }

  uint Context::createTexture( char *data, int width, int height, int bpp,
                               int magFilter, int minFilter, bool wrap )
  {
    logFile.print( "Loading texture into context ..." );

    GLenum format;
    if( bpp == 3 ) {
      format = GL_RGB;
    }
    else if( bpp == 4 ) {
      format = GL_RGBA;
    }
    else {
      logFile.printRaw( " Invalid bpp\n" );
      return 0;
    }

    uint texNum;
    glGenTextures( 1, &texNum );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glBindTexture( GL_TEXTURE_2D, texNum );

    if( minFilter >= GL_NEAREST_MIPMAP_NEAREST ) {
      gluBuild2DMipmaps( GL_TEXTURE_2D, bpp, width, height, format, GL_UNSIGNED_BYTE, data );
    }
    else {
      glTexImage2D( GL_TEXTURE_2D, 0, bpp, width, height, 0, format, GL_UNSIGNED_BYTE, data );
    }

    if( !wrap ) {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    textures << texNum;

    logFile.printRaw( " OK\n" );
    return texNum;
  }

  uint Context::createNormalmap( char *data, int width, int height, int bpp,
                                 int magFilter, int minFilter, bool wrap,
                                 const Vec3 &lightNormal )
  {
    logFile.print( "Loading texture into context ..." );

    uchar *dataEnd = (uchar*) data + width * height * bpp;
    for( uchar *p = (uchar*) data; p < dataEnd; p += bpp ) {
      float x = ( (float) p[0] - 128.0f ) / 128.0f;
      float y = ( (float) p[1] - 128.0f ) / 128.0f;
      float z = ( (float) p[2] - 128.0f ) / 128.0f;

      float dot = x * lightNormal.x + y * lightNormal.y + z * lightNormal.z;
      uchar color = (uchar) bound( dot * 256.0f, 0.0f, 255.0f );

      p[0] = color;
      p[1] = color;
      p[2] = color;
    }

    GLenum format;
    if( bpp == 3 ) {
      format = GL_RGB;
    }
    else if( bpp == 4 ) {
      format = GL_RGBA;
    }
    else {
      logFile.printRaw( " Invalid bpp\n" );
      return 0;
    }

    uint texNum;
    glGenTextures( 1, &texNum );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glBindTexture( GL_TEXTURE_2D, texNum );

    if( minFilter >= GL_NEAREST_MIPMAP_NEAREST ) {
      gluBuild2DMipmaps( GL_TEXTURE_2D, bpp, width, height, format, GL_UNSIGNED_BYTE, data );
    }
    else {
      glTexImage2D( GL_TEXTURE_2D, 0, bpp, width, height, 0, format, GL_UNSIGNED_BYTE, data );
    }

    if( !wrap ) {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    textures << texNum;

    logFile.printRaw( " OK\n" );
    return texNum;
  }

  uint Context::loadTexture( const char *fileName, int magFilter, int minFilter, bool wrap )
  {
    logFile.print( "Reading texture from file '%s' ...", fileName );

    int textureIndex = translator.getTexture( fileName );

    if( textureIndex >= 0 && loadedTextures[textureIndex] != 0 ) {
      logFile.printRaw( " Already loaded\n" );
      return loadedTextures[textureIndex];
    }

    SDL_Surface *image = IMG_Load( fileName );
    if( image == null ) {
      logFile.printRaw( " No such file\n" );
      return 0;
    }

    logFile.printRaw( " OK\n" );

    int bpp = image->format->BitsPerPixel >> 3;   // bytes per pixel

    int texNum = createTexture( (char*) image->pixels, image->w, image->h, bpp,
                                 magFilter, minFilter, wrap );

    SDL_FreeSurface( image );

    if( textureIndex >= 0 ) {
      loadedTextures[textureIndex] = texNum;
    }

    return texNum;
  }

  uint Context::loadNormalmap( const char *fileName, int magFilter, int minFilter, bool wrap,
                               const Vec3 &lightNormal )
  {
    logFile.print( "Reading texture from file '%s' ...", fileName );

    SDL_Surface *image = IMG_Load( fileName );
    if( image == null ) {
      logFile.printRaw( " No such file\n" );
      return 0;
    }

    logFile.printRaw( " OK\n" );

    int bpp = image->format->BitsPerPixel >> 3;   // bytes per pixel

    assert( image->w == image->h );

    int texNum = createNormalmap( (char*) image->pixels, image->w, image->h, bpp,
                                  magFilter, minFilter, wrap, lightNormal );

    SDL_FreeSurface( image );

    return texNum;
  }

  void Context::freeTextures()
  {
    if( !textures.isEmpty() ) {
      glDeleteTextures( textures.length(), textures.dataPtr() );
    }
    textures.clear();

    if( loadedTextures != null ) {
      delete[] loadedTextures;
      loadedTextures = null;
    }
  }

  uint Context::genList()
  {
    ContextList list;

    list.base = glGenLists( 1 );
    list.count = 1;

    lists << list;

    return list.base;
  }

  uint Context::genLists( int count )
  {
    ContextList list;

    list.base = glGenLists( count );
    list.count = count;

    lists << list;

    return list.base;
  }

  void Context::freeLists()
  {
    for( int i = 0; i < lists.length(); i++ ) {
      glDeleteLists( lists[i].base, lists[i].count );
    }
    lists.clear();
  }

  void Context::free()
  {
    freeLists();
    freeTextures();
  }

}
}
