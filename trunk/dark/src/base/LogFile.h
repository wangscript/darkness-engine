/*
 *  LogFile.h
 *
 *  Utility for writing a log file
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: LogFile.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Dark_LogFile_h_
#define _Dark_LogFile_h_

namespace Dark
{

  class LogFile
  {
    protected:

      String logFile;                            // name of log file
      String indentStr;                          // indent string
      int    tabs;                               // amount of indent ( one indent is 3 spaces )
      bool   isStdout;

    public:
      /*
       * first parameter is file name (if NULL, it writes to stdout), the other tells us
       * if we want to clear its content if the file already exists
       */
      bool init( const char *fileName, bool clearFile = true, const char *indentStr = "  " );

      // indents and prints the text
      void print( const char *s, ... ) const;

      // do not indent
      void printRaw( const char *s, ... ) const;

      // indents, prints the text and terminates the line
      void println( const char *s, ... ) const;

      // adds the current time at the beginning of a line
      void printlnBT( const char *s, ... ) const;

      // adds the current time at the end of a line
      void printlnET( const char *s, ... ) const;

      // adds the current time and date at the end
      void printlnETD( const char *s, ... ) const;

      // write a blank line
      void println() const;

      // increases ident
      void indent();

      // decreases ident
      void unindent();

      // clears content of a file
      void clear() const;
  };

  extern LogFile logFile;

}

#endif // _Dark_LogFile_h_
