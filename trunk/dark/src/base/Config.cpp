/*
 *  Config.cpp
 *
 *  List that reads configuration file
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "base.h"

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

namespace Dark
{

  Config config;

  Config::Config()
  {}

  Config::~Config()
  {
    free();
    vars.deallocate();
  }

  void Config::add( const String &key, const String &value )
  {
    if( vars.contains( key ) ) {
      vars.cachedValue() = value;
    }
    else {
      vars.add( key, value );
    }
  }

  void Config::remove( const String &key )
  {
    vars.remove( key );
  }

  bool Config::contains( const String &key )
  {
    return vars.contains( key );
  }

  String Config::get( const String &key )
  {
    return vars.get( key );
  }

  String &Config::operator [] ( const String &key )
  {
    return vars[key];
  }

  bool Config::load( const char *file )
  {
    logFile.print( "Reading configuration from '%s' ...", file );

    xmlTextReader *reader = xmlReaderForFile( file, null, 0 );

    if( reader == null ) {
      xmlCleanupParser();
      logFile.printRaw( " Cannot open file\n" );
      return false;
    }

    int error = xmlTextReaderRead( reader );
    while( error == 1 ) {
      const char *name = (const char*) xmlTextReaderConstName( reader );

      // only check "var" nodes, ignore others
      if( name != null && String::compare( name, "var" ) == 0 ) {
        void *pKey = xmlTextReaderGetAttribute( reader, BAD_CAST "name" );
        void *pValue = xmlTextReaderGetAttribute( reader, BAD_CAST "value" );

        // error if "var" tag doesn't has "name" and "value" attributes
        if( pKey == null || pValue == null ) {
          error = -1;
          break;
        }
        String key = (const char*) pKey;
        String value = (const char*) pValue;

				// msvc has problems with this WTF???
#ifndef WIN32
        ::free( pKey );
        ::free( pValue );
#endif

        add( key, value );
      }
      error = xmlTextReaderRead( reader );
    }
    xmlFreeTextReader( reader );

    if( error != 0 ) {
      xmlCleanupParser();
      logFile.printRaw( " Parse error\n" );
      return false;
    }

    xmlCleanupParser();
    logFile.printRaw( " OK\n" );
    return true;
  }

  bool Config::save( const char *file )
  {
    logFile.print( "Writing configuration to '%s' ...", file );

    xmlTextWriter *writer = xmlNewTextWriterFilename( file, 0 );

    if( writer == null ) {
      xmlCleanupParser();
      logFile.printRaw( " Cannot open file\n" );
      return false;
    }

    if( xmlTextWriterStartDocument( writer, null, "UTF-8", null ) < 0 ||
        xmlTextWriterStartElement( writer, BAD_CAST "config" ) < 0 )
    {
      xmlFreeTextWriter( writer );
      xmlCleanupParser();
      logFile.printRaw( " Write error\n" );
      return false;
    }
    // Write the vars in the same order they are in HastString. I know, it's a mess.
    for( HashString<String, SIZE>::Iterator i( vars ); !i.isPassed(); i.next() ) {
      if( xmlTextWriterWriteString( writer, BAD_CAST "\n  " ) < 0 ||
          xmlTextWriterStartElement( writer, BAD_CAST "var" ) < 0 ||
          xmlTextWriterWriteAttribute( writer, BAD_CAST "name", BAD_CAST i.key()->cstr() ) < 0 ||
          xmlTextWriterWriteAttribute( writer, BAD_CAST "value", BAD_CAST i.value()->cstr() ) < 0 ||
          xmlTextWriterEndElement( writer ) < 0 )
      {
        xmlFreeTextWriter( writer );
        xmlCleanupParser();
        logFile.printRaw( " Write error\n" );
        return false;
      }
    }
    if( xmlTextWriterWriteString( writer, BAD_CAST "\n" ) < 0 ||
        xmlTextWriterEndElement( writer ) < 0 ||
        xmlTextWriterEndDocument( writer ) < 0 )
    {
      xmlFreeTextWriter( writer );
      xmlCleanupParser();
      logFile.printRaw( " Write error\n" );
      return false;
    }
    xmlFreeTextWriter( writer );
    xmlCleanupParser();
    logFile.printRaw( " OK\n" );
    return true;
  }

  String Config::toString()
  {
    String s = "";

    for( HashString<String, SIZE>::Iterator i( vars ); i.get() != null; i.next() ) {
      s = s + *i.key() + " = \"" + *i.get() + "\"\n";
    }
    return s;
  }

  void Config::free()
  {
    vars.free();
  }

}
