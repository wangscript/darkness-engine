/*
 *  Translator.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Translator.cpp 78 2009-03-03 14:16:07Z Davorin.Ucakar $
 */

#include "precompiled.h"

#include "Translator.h"

#include <dirent.h>
#include <sys/types.h>

namespace oz
{

  Translator translator;

  bool Translator::init()
  {
    DIR *dir;
    struct dirent *file;

    dir = opendir( "tex" );
    if( dir == null ) {
      logFile.print( "Cannot open tex/" );
      return false;
    }
    while( ( file = readdir( dir ) ) != null ) {
      textureIndices.add( file->d_name, textures.length() );
      textures << file->d_name;
    }
    closedir( dir );

    dir = opendir( "snd" );
    if( dir == null ) {
      logFile.print( "Cannot open snd/" );
      return false;
    }
    while( ( file = readdir( dir ) ) != null ) {
      soundIndices.add( file->d_name, sounds.length() );
      sounds << file->d_name;
    }
    closedir( dir );

    dir = opendir( "mdl" );
    if( dir == null ) {
      logFile.print( "Cannot open mdl/" );
      return false;
    }
    while( ( file = readdir( dir ) ) != null ) {
      modelIndices.add( file->d_name, models.length() );
      models << file->d_name;
    }
    closedir( dir );

    return true;
  }

  int Translator::getTexture( const char *name )
  {
    if( textureIndices.contains( name ) ) {
      return textureIndices.cachedValue();
    }
    else {
      assert( false );

      return -1;
    }
  }

  int Translator::getSound( const char *name )
  {
    if( soundIndices.contains( name ) ) {
      return soundIndices.cachedValue();
    }
    else {
      assert( false );

      return -1;
    }
  }

  int Translator::getModel( const char *name )
  {
    if( modelIndices.contains( name ) ) {
      return modelIndices.cachedValue();
    }
    else {
      assert( false );

      return -1;
    }
  }

  void Translator::free()
  {
    textureIndices.clear();
    soundIndices.clear();
  }

}
