/*
 *  Bitset.h
 *
 *  Bitset
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  /**
   * Bitset data type.
   *
   * unit = long
   */
  class Bitset
  {
    private:

      // Number of bits per unit.
      static const int LONG_BITSIZE = (int) sizeof( long ) * 8;

      // 0xfff...f
      static const long LONG_ALLBITS = -1;

      // Pointer to unit[] that holds the data.
      long *data;

      // Size of data array (in units, not in bits).
      int  size;

    public:

      /**
       * Create a new bitset without allocating any space.
       */
      Bitset() : data( null ), size( 0 )
      {}

      /**
       * Copy construstor.
       * @param b the original Bitset
       */
      Bitset( const Bitset &b ) : data( new long[size] ), size( b.size )
      {
        aCopy( data, b.data, size );
      }

      /**
       * Allocate a new bitset that holds at least <code>nBits</code> bits. The size of
       * <code>data</code> array is adjusted to least multiplier of unit size that can hold the
       * requested number of bits.
       * @param nBits the number of bits the bitset should hold
       */
      explicit Bitset( int nBits )
      {
        size = ( nBits - 1 ) / LONG_BITSIZE + 1;
        data = new long[size];
      }

      /**
       * Destructor.
       */
      ~Bitset()
      {
        if( data != null ) {
          delete[] data;
        }
      }

      /**
       * Copy operator.
       * @param b the original Bitset
       * @return copy
       */
      Bitset &operator = ( const Bitset &b )
      {
        if( size != b.size ) {
          setUnitSize( b.size );
        }
        aCopy( data, b.data, size );
        return *this;
      }

      /**
       * Get pointer to data array. Use with caution, since you can easily make buffer overflows
       * if you don't check the size of data array.
       * @return non-constant pointer to data array
       */
      long *dataPtr()
      {
        return data;
      }

      /**
       * Get pointer to data array. Use with caution, since you can easily make buffer overflows
       * if you don't check the size of data array.
       * @return constant pointer to data array
       */
      const long *dataPtr() const
      {
        return data;
      }

      /**
       * Resize the data array. New size if specified in units.
       * @param nUnits
       */
      void setUnitSize( int nUnits )
      {
        if( data != null ) {
          delete[] data;
        }
        size = nUnits;
        data = new long[size];
      }

      /**
       * Resize the data array. New size if specified in bits.
       * @param nBits
       */
      void setSize( int nBits )
      {
        setUnitSize( ( nBits - 1 ) / LONG_BITSIZE + 1 );
      }

      /**
       * Size of bitset in bits.
       * @return number of bits the bitset can hold
       */
      int length() const
      {
        return size * LONG_BITSIZE;
      }

      /**
       * Get i-th bit.
       * @param i bit index
       * @return bit
       */
      bool get( int i ) const
      {
        assert( 0 <= i && i < ( size * LONG_BITSIZE ) );

        return ( data[i / LONG_BITSIZE] & ( 1 << ( i % LONG_BITSIZE ) ) ) != 0;
      }

      /**
       * Set i-th bit to true.
       * @param i bit index
       */
      void set( int i )
      {
        assert( 0 <= i && i < ( size * LONG_BITSIZE ) );

        data[i / LONG_BITSIZE] |= 1 << ( i % LONG_BITSIZE );
      }

      /**
       * Set i-th bit to false.
       * @param i bit index
       */
      void clear( int i )
      {
        assert( 0 <= i && i < ( size * LONG_BITSIZE ) );

        data[i / LONG_BITSIZE] &= ~( 1 << ( i % LONG_BITSIZE ) );
      }

      /**
       * @return true, if all bits are true
       */
      bool isAllSet() const
      {
        for( int i = 0; i < size; i++ ) {
          if( data[i] != LONG_ALLBITS ) {
            return false;
          }
        }
        return true;
      }

      /**
       * @return true if all bits are false
       */
      bool isAllClear() const
      {
        for( int i = 0; i < size; i++ ) {
          if( data[i] != 0 ) {
            return false;
          }
        }
        return true;
      }

      /**
       * Set bits from inclusevly start to non-inclusevly end to true.
       * @param start start index
       * @param end end index
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

      /**
       * Set bits from inclusevly start to non-inclusevly end to false.
       * @param start start index
       * @param end end index
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

      /**
       * Set all bits to true.
       */
      void setAll()
      {
        aSet( data, LONG_ALLBITS, size );
      }

      /**
       * Set all bits to false.
       */
      void clearAll()
      {
        aSet( data, 0, size );
      }

      /**
       * Return bitset that has all bits inverted.
       * @return inverted bitset
       */
      Bitset operator ~ () const
      {
        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = ~data[i];
        }
        return r;
      }

      /**
       * Return AND of two bitsets. Bitsets must be the same size.
       * @param b the other bitset
       * @return AND of bitsets
       */
      Bitset operator & ( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = data[i] & b.data[i];
        }
        return r;
      }

      /**
       * Return OR of two bitsets. Bitsets must be the same size.
       * @param b the other bitset
       * @return OR of bitsets
       */
      Bitset operator | ( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = data[i] | b.data[i];
        }
        return r;
      }

      /**
       * Return XOR of two bitsets. Bitsets must be the same size.
       * @param b the other bitset
       * @return XOR of bitsets
       */
      Bitset operator ^ ( const Bitset &b ) const
      {
        assert( size == b.size );

        Bitset r( size );

        for( int i = 0; i < size; i++ ) {
          r.data[i] = data[i] ^ b.data[i];
        }
        return r;
      }

      /**
       * Let say two bitsets are characteristic vectors of two sets. Return true if first set is a
       * subset of the second one. Other explanation: the result is true iff the following statement
       * is true: if first bitset has true on i-th position then the second bitset also has true on
       * i-th position.
       * Bitsets must be the same size.
       *
       * @param b the other bitset
       * @return implication of bitsets
       */
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
