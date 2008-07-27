/*
 *  Bitset.h
 *
 *  Bitset
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Bitset.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Dark_Bitset_h_
#define _Dark_Bitset_h_

namespace Dark
{

  class Bitset
  {
    protected:

      static const int ULONG_BITSIZE = (int) sizeof( long ) * 8;
      static const long ULONG_ALLBITS = -1;

      int   size;

    public:

      long *data;

      Bitset() : size( 0 ), data( null )
      {}

      Bitset( const Bitset &b ) : size( b.size )
      {
        data = new long[size];
        aCopy( data, b.data, size );
      }

      explicit Bitset( int nBits )
      {
        size = ( nBits - 1 ) / ULONG_BITSIZE + 1;
        data = new long[size];
      }

      ~Bitset()
      {
        if( data != null ) {
          delete[] data;
        }
      }

      Bitset &operator = ( const Bitset &b )
      {
        if( size != b.size ) {
          setUnitSize( b.size );
        }
        aCopy( data, b.data, size );
        return *this;
      }

      void setUnitSize( int nUnits )
      {
        if( data != null ) {
          delete[] data;
        }
        size = nUnits;
        data = new long[size];
      }

      void setSize( int nBits )
      {
        setUnitSize( ( nBits - 1 ) / ULONG_BITSIZE + 1 );
      }

      int length() const
      {
        return size * ULONG_BITSIZE;
      }

      bool get( int i ) const
      {
        assert( 0 <= i && i < ( size * ULONG_BITSIZE ) );

        return ( data[i / ULONG_BITSIZE] & ( 1 << ( i % ULONG_BITSIZE ) ) ) != 0;
      }

      void set( int i )
      {
        assert( 0 <= i && i < ( size * ULONG_BITSIZE ) );

        data[i / ULONG_BITSIZE] |= 1 << ( i % ULONG_BITSIZE );
      }

      void clear( int i )
      {
        assert( 0 <= i && i < ( size * ULONG_BITSIZE ) );

        data[i / ULONG_BITSIZE] &= ~( 1 << ( i % ULONG_BITSIZE ) );
      }

      bool isAllSet() const
      {
        for( int i = 0; i < size; i++ ) {
          if( data[i] != ULONG_ALLBITS ) {
            return false;
          }
        }
        return true;
      }

      bool isAllClear() const
      {
        for( int i = 0; i < size; i++ ) {
          if( data[i] != 0 ) {
            return false;
          }
        }
        return true;
      }

      /*
       * Set bits from inclusively "start" to non-inclusively "end" to 1
       */
      void set( int start, int end )
      {
        assert( 0 <= start && start <= end && end <= ( size * ULONG_BITSIZE ) );

        int startUnit   = start / ULONG_BITSIZE;
        int startOffset = start % ULONG_BITSIZE;

        int endUnit     = end / ULONG_BITSIZE;
        int endOffset   = end % ULONG_BITSIZE;

        long startMask = ULONG_ALLBITS << startOffset;
        long endMask   = ~( ULONG_ALLBITS << endOffset );

        if( startUnit == endUnit ) {
          data[startUnit] |= startMask & endMask;
        }
        else {
          data[startUnit] |= startMask;
          data[endUnit]   |= endMask;

          for( int i = startUnit + 1; i < endUnit; i++ ) {
            data[i] = ULONG_ALLBITS;
          }
        }
      }

      /*
       * Set bits from inclusevly "start" to non-inclusevly "end" to 0
       */
      void clear( int start, int end )
      {
        assert( 0 <= start && start <= end && end <= ( size * ULONG_BITSIZE ) );

        int startUnit   = start / ULONG_BITSIZE;
        int startOffset = start % ULONG_BITSIZE;

        int endUnit     = end / ULONG_BITSIZE;
        int endOffset   = end % ULONG_BITSIZE;

        long startMask = ~( ULONG_ALLBITS << startOffset );
        long endMask   = ULONG_ALLBITS << endOffset;

        if( startUnit == endUnit ) {
          data[startUnit] &= startMask | endMask;
        }
        else {
          data[startUnit] &= startMask;
          data[endUnit]   &= endMask;

          for( int i = startUnit + 1; i < endUnit; i++ ) {
            data[i] = 0;
          }
        }
      }

      void setAll()
      {
        aSet( data, ULONG_ALLBITS, size );
      }

      void clearAll()
      {
        aSet( data, 0, size );
      }

      Bitset operator ~ () const
      {
        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = ~data[i];
        }
        return r;
      }

      Bitset operator & ( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = data[i] & b.data[i];
        }
        return r;
      }

      Bitset operator | ( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = data[i] | b.data[i];
        }
        return r;
      }

      Bitset operator ^ ( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = data[i] ^ b.data[i];
        }
        return r;
      }

      bool isSubset( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          if( ( data[i] & ~b.data[i] ) != 0 ) {
            return false;
          }
        }
        return true;
      }

  };

}

#endif // _Dark_Bitset_h_
