/*
 *  String.h
 *
 *  Advanced string data type
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_String_h_
#define _Dark_String_h_

namespace Dark
{

  class String
  {
    protected:

      char *buffer;
      int  count;

      String( char *buffer_, int count_ ) : buffer( buffer_ ), count( count_ )
      {}

    public:

      String() : count( 0 )
      {
        buffer = new char[1];
        buffer[0] = '\0';
      }

      String( const String &s ) : count( s.count )
      {
        buffer = new char[count + 1];
        aCopy( buffer, s.buffer, count + 1 );
      }

      String( const char *s )
      {
        if( s == null ) {
          count = 0;
          buffer = new char[1];
          buffer[0] = '\0';
        }
        else {
          count = length( s );
          buffer = new char[count + 1];
          aCopy( buffer, s, count + 1 );
        }
      }

      explicit String( int n )
      {
        if( n == 0 ) {
          count = 1;
          buffer = new char[2];
          buffer[0] = '0';
          buffer[1] = '\0';
        }
        else {
          // determine number of digits
          int nn = n;
          for( count = 0; nn != 0; count++ ) {
            nn /= 10;
          }

          int i;
          if( n < 0 ) {
            buffer = new char[count + 2];
            buffer[0] = '-';
            buffer[count + 1] = '\0';

            n = -n;
            i = count;
          }
          else {
            buffer = new char[count + 1];
            buffer[count] = '\0';

            i = count - 1;
          }

          while( n != 0 ) {
            buffer[i] = '0' + ( n % 10 );
            n /= 10;
            i--;
          }
        }
      }

      ~String()
      {
        delete[] buffer;
      }

      operator const char* () const
      {
        return (const char*) buffer;
      }

      const char *cstr() const
      {
        return (const char*) buffer;
      }

      String &operator = ( const char *s )
      {
        count = length( s );

        char *rBuffer = new char[count + 1];
        aCopy( rBuffer, s, count + 1 );

        delete[] buffer;
        buffer = rBuffer;

        return *this;
      }

      String &operator = ( const String &s )
      {
        count = s.count;

        char *rBuffer = new char[count + 1];
        aCopy( rBuffer, s.buffer, count + 1 );

        delete[] buffer;
        buffer = rBuffer;

        return *this;
      }

      bool operator == ( const char *s ) const
      {
        assert( s != null );

        for( int i = 0; buffer[i] == s[i]; i++ ) {
          if( buffer[i] == '\0' ) {
            return true;
          }
        }
        return false;
      }

      bool operator != ( const char *s ) const
      {
        assert( s != null );

        for( int i = 0; buffer[i] == s[i]; i++ ) {
          if( buffer[i] == '\0' ) {
            return false;
          }
        }
        return true;
      }

      bool operator == ( const String &s ) const
      {
        return this->operator == ( s.buffer );
      }

      bool operator != ( const String &s ) const
      {
        return this->operator != ( s.buffer );
      }

      friend bool operator == ( const char *a, const String &b )
      {
        return b.operator == ( a );
      }

      friend bool operator != ( const char *a, const String &b )
      {
        return b.operator != ( a );
      }

      static bool areEqual( const char *a, const char *b )
      {
        assert( a != null && b != null );

        for( int i = 0; a[i] == b[i]; i++ ) {
          if( a[i] == '\0' ) {
            return true;
          }
        }
        return false;
      }

      const char &operator [] ( int i ) const
      {
        assert( 0 <= i && i < count );

        return buffer[i];
      }

      char &operator [] ( int i )
      {
        assert( 0 <= i && i < count );

        return buffer[i];
      }

      char charAt( int i ) const
      {
        assert( 0 <= i && i < count );

        return buffer[i];
      }

      static int length( const char *s )
      {
        int i = 0;

        while( s[i] != '\0' ) {
          i++;
        }
        return i;
      }

      int length() const
      {
        return count;
      }

      static int compare( const char *a, const char *b )
      {
        assert( a != null && b != null );

        int diff;

        for( int i = 0; ( diff = a[i] - b[i] ) == 0; i++ ) {
          if( a[i] == '\0' ) {
            return 0;
          }
        }
        return diff;
      }

      int compare( const char *s ) const
      {
        return compare( buffer, s );
      }

      int compare( const String &s ) const
      {
        return compare( buffer, s.buffer );
      }

      int index( char ch, int start = 0 ) const
      {
        int i = start;

        while( buffer[i] != ch && i < count ) {
          i++;
        }
        return i == count ? -1 : i;
      }

      int lastIndex( char ch ) const
      {
        int i = count - 1;

        while( buffer[i] != ch && i >= 0 ) {
          i--;
        }
        return i;
      }

      int lastIndex( char ch, int end ) const
      {
        int i = end;

        while( buffer[i] != ch && i >= 0 ) {
          i--;
        }
        return i;
      }

      String operator + ( const char *s ) const
      {
        assert( s != null );

        int sLength = length( s );

        int  rCount   = count + sLength;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, buffer, count );
        aCopy( rBuffer + count, s, sLength + 1 );

        return String( rBuffer, rCount );
      }

      String operator + ( const String &s ) const
      {
        int  rCount   = count + s.count;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, buffer, count );
        aCopy( rBuffer + count, s.buffer, s.count + 1 );

        return String( rBuffer, rCount );
      }

      friend String operator + ( const char *s, const String &t )
      {
        assert( s != null );

        int sLength = String::length( s );

        int  rCount   = t.count + sLength;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, s, sLength );
        aCopy( rBuffer + sLength, t.buffer, t.count + 1 );

        return String( rBuffer, rCount );
      }

      String &operator += ( const char *s )
      {
        assert( s != null );

        int sLength = length( s );

        int  rCount   = count + sLength;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, buffer, count );
        aCopy( rBuffer + count, s, sLength + 1 );

        delete[] buffer;
        buffer = rBuffer;
        count  = rCount;

        return *this;
      }

      String &operator += ( const String &s )
      {
        int  rCount   = count + s.count;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, buffer, count );
        aCopy( rBuffer + count, s.buffer, s.count + 1 );

        delete[] buffer;
        buffer = rBuffer;
        count  = rCount;

        return *this;
      }

      String substring( int start ) const
      {
        assert( 0 <= start && start <= count );

        int  rCount   = count - start;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, buffer + start, rCount + 1 );

        return String( rBuffer, rCount );
      }

      String substring( int start, int end ) const
      {
        assert( 0 <= start && start <= count && start <= end && end <= count );

        int  rCount   = end - start;
        char *rBuffer = new char[rCount + 1];

        aCopy( rBuffer, buffer + start, rCount );
        rBuffer[rCount] = '\0';

        return String( rBuffer, rCount );
      }

      Vector<String> split( char ch ) const
      {
        Vector<String> v;

        int p0 = 0;
        int p1 = index( ch );

        while( p1 >= 0 ) {
          v << substring( p0, p1 );
          p0 = p1 + 1;
          p1 = index( ch, p0 );
        }
        v << substring( p0 );
        return v;
      }

  };

}

#endif // _Dark_String_h_
