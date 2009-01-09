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
 * typedef signed   char  byte;
 * typedef unsigned char  ubyte;
 * typedef unsigned short ushort;
 * typedef unsigned int   uint;
 * typedef unsigned long  ulong;</pre>
 *
 * Be careful about use of char, byte and ubyte; char may be either signed or unsigned depending
 * on the platform.
 *
 * You may add <code>null</code> and those types to your ~/.kde/share/apps/katepart/syntax/cpp.xml
 * or global file $KDEDIR/share/apps/katepart/syntax/cpp.xml to look like reserved words in
 * Kate/KWrite/KDevelop.
 */

namespace Dark
{

# define null 0

  typedef signed   char  byte;
  typedef unsigned char  ubyte;
  typedef unsigned short ushort;
  typedef unsigned int   uint;
  typedef unsigned long  ulong;

  /*
   * MISCELLANEOUS TEMPLATES
   */

  /**
   * Swap values of a and b.
   * @param a reference to first variable
   * @param b reference to second variable
   */
  template <class ValueA, class ValueB>
  inline void swap( ValueA &a, ValueB &b )
  {
    ValueA temp = a;

    a = b;
    b = temp;
  }

  /**
   * Absolute value.
   * @param a
   * @return absolute value
   */
  template <class Value>
  inline Value abs( const Value &a )
  {
    return a < 0 ? -a : a;
  }

  /**
   * Minimum.
   * @param a
   * @param b
   * @return minimum of a and b
   */
  template <class Value, class ValueB>
  inline const Value &min( const Value &a, const ValueB &b )
  {
    return a < b ? a : b;
  }

  /**
   * Maximum.
   * @param a
   * @param b
   * @return maximum of a and b
   */
  template <class Value, class ValueB>
  inline const Value &max( const Value &a, const ValueB &b )
  {
    return a > b ? a : b;
  }

  /**
   * c bounded between a and b. Equals to max( min( c, b ), a ).
   * @param c
   * @param a
   * @param b
   * @return clamped value of c
   */
  template <class ValueC, class ValueA, class ValueB>
  inline const ValueC &bound( const ValueC &c, const ValueA &a, const ValueB &b )
  {
    assert( a < b );

    if( a > c ) {
      return a;
    }
    else {
      return b < c ? b : c;
    }
  }

  /**
   * Pointer iterator
   */
  template <class Type>
  class Iterator
  {
    protected:

      Type *elem;
      const Type *past;

      /**
       * @param start first element
       */
      Iterator( Type *start ) : elem( start )
      {}

    public:

      /**
       * @param start first element for forward iterator or successor of last element for backward
       * iterator
       * @param past_ successor of last element for forward iterator or first element for backward
       * iterator
       */
      Iterator( Type *start, const Type *past_ ) : elem( start ), past( past_ )
      {}

      /**
       * Returns true if iterator is on specified element.
       * @param e
       * @return
       */
      bool operator == ( const Type *e ) const
      {
        return elem == e;
      }

      /**
       * Returns true if iterator is not on specified element.
       * @param e
       * @return
       */
      bool operator != ( const Type *e ) const
      {
        return elem != e;
      }

      /**
       * When iterator advances beyond last element, it becomes passed. It points to an invalid
       * location.
       * @return true if iterator is passed
       */
      bool isPassed() const
      {
        return elem == past;
      }

      /**
       * Advance to next element.
       */
      void operator ++ ( int )
      {
        assert( elem != past );

        elem++;
      }

      /**
       * Advance to previous element.
       */
      void operator -- ( int )
      {
        assert( elem != past );

        elem--;
      }

      /**
       * @return reference to current element in the list
       */
      Type &operator * ()
      {
        return *elem;
      }

      /**
       * @return constant reference to current element in the list
       */
      const Type &operator * () const
      {
        return *elem;
      }

  };

  /*
   * ITERABLE CONTAINER UTILITY TEMPLATES
   */

  /**
   * Compare all elements. (Like STL equal)
   * @param iA
   * @param iB
   * @return true if all elements are equal
   */
  template <class IteratorA, class IteratorB>
  inline bool iEquals( IteratorA iA, IteratorB iB )
  {
    while( !iA.isPassed() ) {
      if( *iA != *iB ) {
        return false;
      }
      iA++;
      iB++;
    }
    return true;
  }

  /**
   * Set all elements. (Like STL fill)
   * @param i
   * @param value
   */
  template <class Iterator, class Value>
  inline void iSet( Iterator i, Value value )
  {
    while( !i.isPassed() ) {
      *i = value;
      i++;
    }
  }

  /**
   * Copy elements from first to last. (Like STL copy)
   * @param iA
   * @param iB
   */
  template <class IteratorA, class IteratorB>
  inline void iCopy( IteratorA iA, IteratorB iB )
  {
    while( !iA.isPassed() ) {
      *iB = *iA;
      iA++;
      iB++;
    }
  }

  /**
   * Copy elements from first to last. (Like STL copy)
   * @param iA
   * @param iB
   */
  template <class BackwardIteratorA, class BackwardIteratorB>
  inline void iReverseCopy( BackwardIteratorA iA, BackwardIteratorB iB )
  {
    while( !iA.isPassed() ) {
      iA--;
      iB--;
      *iB = *iA;
    }
  }

  /**
   * Find first occurence of given element. (Like STL find)
   * @param begin
   * @param value
   * @return iterator at the elements found, passed iterator if not found
   */
  template <class Iterator, class Value>
  inline Iterator iIndex( Iterator i, Value value )
  {
    while( !i.isPassed() ) {
      if( *i == value ) {
        break;
      }
      i++;
    }
    return i;
  }

  /**
   * Find last occurence of given element.
   * @param begin
   * @param value
   * @return iterator at the elements found, passed iterator if not found
   */
  template <class BackwardIterator, class Value>
  inline BackwardIterator iLastIndex( BackwardIterator i, Value value )
  {
    while( !i.isPassed() ) {
      i--;
      if( *i == value ) {
        break;
      }
    }
    return i;
  }

  /**
   * Delete elements that have been previously allocated with new operator.
   */
  template <class Iterator, class Type>
  inline void iFree( Iterator i )
  {
    while( !i.isPassed() ) {
      Type *p = *i;
      i++;
      delete p;
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
  template <class Type, class Value>
  inline void aSet( Type *dest, const Value &value, int count )
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
  inline void aReverseCopy( Type *dest, const Type *src, int count )
  {
    for( int i = count - 1; i >= 0; i-- ) {
      dest[i] = src[i];
    }
  }

  /**
   * Find the first occurence of an element.
   * @param array pointer to the first element in the array
   * @param count number of elements to be looked upon
   * @param value value we look for
   * @return index of the first occurence, -1 if not found
   */
  template <class Type, class Value>
  inline int aIndex( const Type *array, int count, const Value &value )
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
  template <class Type, class Value>
  inline int aLastIndex( const Type *array, int count, const Value &value )
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
   * Utility function for aSort. It could also be called directly. Type must have operator &lt;
   * defined.
   * @param first pointer to first element in the array to be sorted
   * @param last pointer to last element in the array
   */
  template <class Type>
  static void aQuicksort( Type *first, Type *last )
  {
    // 8-14 seem as optimal tresholds for switching to selection sort
    if( last - first > 10 ) {
      // quicksort
      Type *top = first;
      Type *bottom = last - 1;

      do {
        while( top <= bottom && !( *last < *top ) ) {
          top++;
        }
        while( top < bottom && *last < *bottom ) {
          bottom--;
        }
        if( top >= bottom ) {
          break;
        }
        swap( *top, *bottom );
      }
      while( true );

      swap( *top, *last );

      aQuicksort( first, top - 1 );
      aQuicksort( top + 1, last );
    }
    else {
      // selection sort
      for( Type *i = first; i < last; ) {
        Type *pivot = i;
        Type *min = i;
        i++;

        for( Type *j = i; j <= last; j++ ) {
          if( *j < *min ) {
            min = j;
          }
        }
        swap( *pivot, *min );
      }
    }
  }

  /**
   * Perform quicksort on the array. Recursive quicksort algorithm is used which takes first
   * element in partition as a pivot so sorting a sorted or nearly sorted array will take O(n^2)
   * time instead of O(n log n) as in general case. Type must have operator &lt; defined.
   * @param array pointer to the first element in the array
   * @param count number of elements to be sorted
   */
  template <class Type>
  inline void aSort( Type *array, int count )
  {
    assert( count > 1 );

    aQuicksort( array, array + count - 1 );
  }

}
