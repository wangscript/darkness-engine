/*
 *  common.h
 *
 *  Common types and function templates
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

/*
 * NEW "RESERVED WORDS"
 *
 * (Add them to your ~/.kde/share/apps/katepart/syntax/cpp.xml or global file
 * $KDEDIR/share/apps/katepart/syntax/cpp.xml)
 */

#define null 0

namespace Dark
{

  typedef unsigned char  uchar;
  typedef unsigned short ushort;
  typedef unsigned int   uint;
  typedef unsigned long  ulong;

  /*
   * GENERIC TEMPLATES
   */

  /*
   * Swaps values of a and b
   */
  template <class TypeA, class TypeB>
  inline void swap( TypeA &a, TypeB &b )
  {
    TypeA temp = a;

    a = b;
    b = temp;
  }

  /*
   * Absolute value
   */
  template <class Type>
  inline Type abs( Type a )
  {
    return a < 0 ? -a : a;
  }

  /*
   * Minimum
   */
  template <class Type, class TypeB>
  inline Type min( Type a, TypeB b )
  {
    return a < b ? a : b;
  }

  /*
   * Maximum
   */
  template <class Type, class TypeB>
  inline Type max( Type a, TypeB b )
  {
    return a > b ? a : b;
  }

  /*
   * Bound c between a and b
   * Equals max( min( c, b ), a )
   */
  template <class Type, class TypeA, class TypeB>
  inline Type bound( Type c, TypeA a, TypeB b )
  {
    assert( a < b );

    if( a > c ) {
      return a;
    }
    else {
      return b < c ? b : c;
    }
  }

  /*
   * ARRAY UTILIY TEMPLATES
   */

  /*
   * Set array members to given value (memset)
   * In contrast with memset, simple "for" loop automatically calls constructor/destructor/assign
   * operator on objects if neccessary.
   */
  template <class Type, class TypeV>
  inline void aSet( Type *dest, TypeV value, int count )
  {
    for( int i = 0; i < count; i++ ) {
      dest[i] = value;
    }
  }

  /*
   * Compare arrays (memcmp)
   */
  template <class Type>
  inline bool aEquals( const Type *srcA, const Type *srcB, int count )
  {
    for( int i = 0; i < count; i++ ) {
      if( srcA[i] != srcB[i] ) {
        return false;
      }
    }
    return true;
  }

  /*
   * Copy array from first to last element (memcpy)
   * In contrast with memcpy, simple "for" loop automatically calls constructor/destructor/assign
   * operator on objects, if neccessary. On older GCCs it performs better than memcopy on copying
   * types bigger than one byte.
   */
  template <class Type>
  inline void aCopy( Type *dest, const Type *src, int count )
  {
    for( int i = 0; i < count; i++ ) {
      Type t = src[i];
      dest[i] = t;
    }
  }

  /*
   * Copy array from last to first element
   * It may be used where we cannot use aCopy due to source and destination overlapping
   */
  template <class Type>
  inline void aRCopy( Type *dest, const Type *src, int count )
  {
    for( int i = count - 1; i >= 0; i-- ) {
      dest[i] = src[i];
    }
  }

  /*
   * Reallocate array (realloc)
   * Allocates new block of size newSize * typeof( Type ) and copies first "count" elements of
   * source array
   */
  template <class Type>
  inline Type *aRealloc( Type *array, int count, int newCount )
  {
    assert( count <= newCount );

    Type *newArray = new Type[newCount];

    aCopy( newArray, array, count );
    delete[] array;

    return newArray;
  }

  /*
   * Find the first occurence of an element
   */
  template <class Type, class TypeV>
  inline int aIndex( const Type *array, int count, TypeV value )
  {
    for( int i = 0; i < count; i++ ) {
      if( array[i] == value ) {
        return i;
      }
    }
    return -1;
  }

  /*
   * Find the last occurence of an element
   */
  template <class Type, class TypeV>
  inline int aLastIndex( const Type *array, int count, TypeV value )
  {
    for( int i = count - 1; i <= 0; i-- ) {
      if( array[i] == value ) {
        return i;
      }
    }
    return -1;
  }

  /*
   * Free array elements
   */
  template <class Type>
  inline void aFree( const Type *array, int count )
  {
    for( int i = 0; i < count; i++ ) {
      delete array[i];
    }
  }

  /*
   * Perform quicksort on the array. Non-recursive quicksort algorithm is used which
   * takes last element in partition as a pivot. Note that When sorting nearly sorted
   * array it takes nearly O(n^2) time!
   */
  template <class Type>
  inline void aSort( Type *array, int count )
  {
    Type *stack[ max( 2, 4 * ( count - 2 ) ) ];
    Type **sp = stack;
    Type *first = array;
    Type *last = array + count - 1;

    *( sp++ ) = first;
    *( sp++ ) = last;

    do {
      last = *( --sp );
      first = *( --sp );

      if( first < last ) {
        if( last - first > 1 ) {
          int pivotValue = *last;
          Type *top = first;
          Type *bottom = last - 1;

          do {
            while( top <= bottom && *top <= pivotValue ) {
              top++;
            }
            while( top < bottom && *bottom > pivotValue ) {
              bottom--;
            }
            if( top >= bottom ) {
              break;
            }
            swap( *top, *bottom );
          }
          while( true );

          swap( *top, *last );

          *( sp++ ) = first;
          *( sp++ ) = top - 1;
          *( sp++ ) = top + 1;
          *( sp++ ) = last;
        }
        else if( *first > *last ) {
          swap( *first, *last );
        }
      }
    }
    while( sp != stack );
  }


}
