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

/**
 * Dark namespace.
 *
 * That namespace contains everything that is part of the engine.
 *
 * It also defines null macro as
 * <pre>##define null 0</pre>
 * It is used instead of NULL macro thru the engine.
 *
 * There are also unsigned integer types defined in here:
 * <pre>
 * typedef unsigned char  uchar;
 * typedef unsigned short ushort;
 * typedef unsigned int   uint;
 * typedef unsigned long  ulong;</pre>
 *
 * You may add <code>null</code> and those types to your ~/.kde/share/apps/katepart/syntax/cpp.xml
 * or global file $KDEDIR/share/apps/katepart/syntax/cpp.xml to look like reserved words in
 * Kate/KWrite/KDevelop.
 */

namespace Dark
{

# define null 0

  typedef unsigned char  uchar;
  typedef unsigned short ushort;
  typedef unsigned int   uint;
  typedef unsigned long  ulong;

  /*
   * GENERIC TEMPLATES
   */

  /**
   * Swap values of a and b.
   * @param a reference to first variable
   * @param b reference to second variable
   */
  template <class TypeA, class TypeB>
  inline void swap( TypeA &a, TypeB &b )
  {
    TypeA temp = a;

    a = b;
    b = temp;
  }

  /**
   * Absolute value.
   * @param a
   * @return absolute value
   */
  template <class Type>
  inline Type abs( Type a )
  {
    return a < 0 ? -a : a;
  }

  /**
   * Minimum.
   * @param a
   * @param b
   * @return minimum of a and b
   */
  template <class Type, class TypeB>
  inline Type min( Type a, TypeB b )
  {
    return a < b ? a : b;
  }

  /**
   * Maximum.
   * @param a
   * @param b
   * @return maximum of a and b
   */
  template <class Type, class TypeB>
  inline Type max( Type a, TypeB b )
  {
    return a > b ? a : b;
  }

  /**
   * Bound c between a and b. Equals to max( min( c, b ), a ).
   * @param c
   * @param a
   * @param b
   * @return clamped value of c
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

  /**
   * Set array members to given value (memset).
   * In contrast with memset it calls constructor/destructor/assign operator on objects.
   * @param dest pointer to the first element
   * @param value value to be set
   * @param count number of elements to be set
   */
  template <class Type, class TypeV>
  inline void aSet( Type *dest, TypeV value, int count )
  {
    for( int i = 0; i < count; i++ ) {
      dest[i] = value;
    }
  }

  /**
   * Compare arrays (memcmp).
   * In contrast to memcmp it automagically calls != operator if comparing objects.
   * @param srcA pointer to the first element in the first array
   * @param srcB pointer to the first element in the second array
   * @param count number of elements to be compared
   * @return
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

  /**
   * Copy array from first to last element (memcpy).
   * In contrast with memcpy it calls constructor/destructor/assign when copying objects.
   * On older GCCs it performs better than memcopy on copying types bigger than one byte.
   * @param dest pointer to the first element in the destination array
   * @param src pointer to the first element in the source array
   * @param count number of elements to be copied
   */
  template <class Type>
  inline void aCopy( Type *dest, const Type *src, int count )
  {
    for( int i = 0; i < count; i++ ) {
      Type t = src[i];
      dest[i] = t;
    }
  }

  /**
   * Copy array from last to first element.
   * It may be used where you cannot use aCopy due to source and destination overlapping.
   * @param dest pointer to the first element in the destination array
   * @param src pointer to the first element in the source array
   * @param count number of elements to be copied
   */
  template <class Type>
  inline void aRCopy( Type *dest, const Type *src, int count )
  {
    for( int i = count - 1; i >= 0; i-- ) {
      dest[i] = src[i];
    }
  }

  /**
   * Reallocate array (realloc).
   * Allocates new block of size newSize * typeof( Type ) and copies first "count" elements of
   * source array. newCount should be equal to or greater than count.
   * @param array pointer to the source array
   * @param count number of elements to be copied
   * @param newCount number of elements in the new array
   * @return
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

  /**
   * Find the first occurence of an element.
   * @param array pointer to the first element in the array
   * @param count number of elements to be looked upon
   * @param value value we look for
   * @return index of the first occurence, -1 if not found
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

  /**
   * Find the last occurence of an element.
   * @param array pointer to the first element in the array
   * @param count number of elements to be looked upon
   * @param value value we look for
   * @return index of the first occurence, -1 if not found
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

  /**
   * Delete array elements.
   * @param array pointer to the first element in the array
   * @param count number of elements
   */
  template <class Type>
  inline void aFree( const Type *array, int count )
  {
    for( int i = 0; i < count; i++ ) {
      delete array[i];
    }
  }

  /**
   * Perform quicksort on the array. Non-recursive quicksort algorithm is used which takes last
   * element in partition as a pivot so sorting a sorted or nearly sorted array will take O(n^2)
   * time instead of O(n log n) as in general case.
   * @param array pointer to the first element in the array
   * @param begin index of the fist element to be sorted
   * @param end index of the last element to be sorted
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

  /**
   * Perform quicksort on the array. Non-recursive quicksort algorithm is used which takes middle
   * element in partition as a pivot so sorting a sorted or nearly sorted array performs well
   * (O(n log n) time) on nearly sorted arrays.
   * @param array pointer to the first element in the array
   * @param begin index of the fist element to be sorted
   * @param end index of the last element to be sorted
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
          Type *pivot = first + ( last - first ) / 2;
          int pivotValue = *pivot;
          Type *top = first;
          Type *bottom = last - 1;

          swap( *pivot, *last );

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
