/*
 *  Config.h
 *
 *  List that reads configuration file
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_Config_h_
#define _Dark_Config_h_

namespace Dark
{

  class Config
  {
    protected:

      static const int SIZE = 1024;
      // size of buffer, used when loading from file (maximum key/value length)
      static const int BUFFER_SIZE = 1024;

      HashString<String, SIZE> vars;

    public:

      ~Config();

      void add( const String &key, const String &value );
      void remove( const String &key );

      bool contains( const String &key );

      String get( const String &key );
      String &operator [] ( const String &key );

      bool load( const char *file );
      bool save( const char *file );
      String toString();

      void free();
  };

  extern Config config;

}

#endif // _Dark_Config_h_
