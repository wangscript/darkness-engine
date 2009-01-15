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

  uint Context::createTexture( int context, const ubyte *data, int width, int height,
                               int bytesPerPixel, bool wrap, int magFilter, int minFilter )
  {
    assert( context < entries.length() && entries.contains( );

    logFile.print( "Creating texture from buffer ..." );

    int texNum = buildTexture( data, width, height, bpp, wrap, magFilter, minFilter );

    if( texNum == 0 ) {
      logFile.printRaw( " Error\n" );
    }
    else {
      entries[context].textures << new Texture( texNum, 0 );
      logFile.printRaw( " OK" );
    }
    return texNum;
  }

  uint Context::createNormalmap( int context, ubyte *data, int width, int height,
                                 const Vec3 &lightNormal, int bytesPerPixel,
                                 bool wrap, int magFilter, int minFilter )
  {
    assert( entries.contains( context ) );

    logFile.print( "Creating normalmap texture from buffer ..." );

    int texNum = buildTexture( data, width, height, bpp, lightNormal, wrap, magFilter, minFilter );

    if( texNum == 0 ) {
      logFile.printRaw( " Error\n" );
    }
    else {
      entries[context].textures << new Texture( texNum, 0 );
      logFile.printRaw( " OK" );
    }
    return texNum;
  }

  uint Context::loadTexture( int context, const char *fileName,
                             bool wrap, int magFilter, int minFilter )
  {
    assert( entries.contains( context ) );

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
    if( image->w != image->h ) {
      logFileprintRaw( " Dimensions are not equal" );
    }

    logFile.printRaw( " OK\n" );

    int bytesPerPixel = image->format->BitsPerPixel / 8;

    int texNum = createTexture( (ubyte*) image->pixels, image->w, image->h, bytesPerPixel,
                                wrap, magFilter, minFilter );

    SDL_FreeSurface( image );

    if( textureIndex >= 0 ) {
      loadedTextures[textureIndex] = texNum;
    }

    return texNum;
  }

  uint Context::loadNormalmap( int context, const char *fileName, const Vec3 &lightNormal,
                               bool wrap, int magFilter, int minFilter )
  {
    logFile.print( "Reading texture from file '%s' ...", fileName );

    SDL_Surface *image = IMG_Load( fileName );
    if( image == null ) {
      logFile.printRaw( " No such file\n" );
      return 0;
    }

    logFile.printRaw( " OK\n" );

    int bytesPerPixel = image->format->BitsPerPixel / 8;

    assert( image->w == image->h );

    int texNum = createNormalmap( (ubyte*) image->pixels, image->w, image->h, bytesPerPixel,
                                  lightNormal, wrap, magFilter, minFilter );

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
