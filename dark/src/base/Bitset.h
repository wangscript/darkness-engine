/*
 *  Bitset.h
 *
 *  Bitset
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_Bitset_h_
#define _Dark_Bitset_h_

namespace Dark
{

  class Bitset
  {
    private:

      static const int LONG_BITSIZE = (int) sizeof( long ) * 8;
      static const long LONG_ALLBITS = -1;

      long *data;
      int  size;

    public:

      Bitset() : data( null ), size( 0 )
      {}

      Bitset( const Bitset &b ) : data( new long[size] ), size( b.size )
      {
        aCopy( data, b.data, size );
      }

      explicit Bitset( int nBits )
      {
        size = ( nBits - 1 ) / LONG_BITSIZE + 1;
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

      long *dataPtr()
      {
        return data;
      }

      const long *dataPtr() const
      {
        return data;
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
        setUnitSize( ( nBits - 1 ) / LONG_BITSIZE + 1 );
      }

      int length() const
      {
        return size * LONG_BITSIZE;
      }

      bool get( int i ) const
      {
        assert( 0 <= i && i < ( size * LONG_BITSIZE ) );

        return ( data[i / LONG_BITSIZE] & ( 1 << ( i % LONG_BITSIZE ) ) ) != 0;
      }

      void set( int i )
      {
        assert( 0 <= i && i < ( size * LONG_BITSIZE ) );

        data[i / LONG_BITSIZE] |= 1 << ( i % LONG_BITSIZE );
      }

      void clear( int i )
      {
        assert( 0 <= i && i < ( size * LONG_BITSIZE ) );

        data[i / LONG_BITSIZE] &= ~( 1 << ( i % LONG_BITSIZE ) );
      }

      bool isAllSet() const
      {
        for( int i = 0; i < size; i++ ) {
          if( data[i] != LONG_ALLBITS ) {
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
        assert( 0 <= start && start <= end && end <= ( size * LONG_BITSIZE ) );

        int startUnit   = start / LONG_BITSIZE;
        int startOffset = start % LONG_BITSIZE;

        int endUnit     = end / LONG_BITSIZE;
        int endOffset   = end % LONG_BITSIZE;

        long startMask = LONG_ALLBITS << startOffset;
        long endMask   = ~( LONG_ALLBITS << endOffset );

        if( startUnit == endUnit ) {
          data[startUnit] |= startMask & endMask;
        }
        else {
          data[startUnit] |= startMask;
          data[endUnit]   |= endMask;

          for( int i = startUnit + 1; i < endUnit; i++ ) {
            data[i] = LONG_ALLBITS;
          }
        }
      }

      /*
       * Set bits from inclusevly "start" to non-inclusevly "end" to 0
       */
      void clear( int start, int end )
      {
        assert( 0 <= start && start <= end && end <= ( size * LONG_BITSIZE ) );

        int startUnit   = start / LONG_BITSIZE;
        int startOffset = start % LONG_BITSIZE;

        int endUnit     = end / LONG_BITSIZE;
        int endOffset   = end % LONG_BITSIZE;

        long startMask = ~( LONG_ALLBITS << startOffset );
        long endMask   = LONG_ALLBITS << endOffset;

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
        aSet( data, LONG_ALLBITS, size );
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
