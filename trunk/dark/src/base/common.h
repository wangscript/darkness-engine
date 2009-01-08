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
  inline Value abs( Value a )
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
  inline Value min( Value a, ValueB b )
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
  inline Value max( Value a, ValueB b )
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
	 * ITERABLE CONTAINER UTILITY TEMPLATES
	 */

	/**
	 * Compare all elements. (Like STL equal)
	 */
	template <class IteratorA, class IteratorB>
	inline bool iEquals( IteratorA beginA, IteratorA endA, IteratorB beginB )
	{
		while( beginA != endA ) {
			if( *beginA != *beginB ) {
				return false;
			}
			beginA++;
			beginB++;
		}
		return true;
	}

	/**
	 * Set all elements. (Like STL fill)
	 */
	template <class Iterator, class Value>
	inline void iSet( Iterator begin, Iterator end, Value value )
	{
		while( begin != end ) {
			*begin = value;
			begin++;
		}
	}

	/**
	 * Copy elements from first to last. (Like STL copy)
	 */
	template <class IteratorA, class IteratorB>
	inline void iCopy( IteratorA beginA, IteratorA endA, IteratorB beginB )
	{
		while( beginA != endA ) {
			*beginB = *beginA;
			beginA++;
			beginB++;
		}
	}

	/**
	 * Copy elements from last to first. (Like STL copy_backward)
	 */
	template <class IteratorA, class IteratorB>
	inline void iRCopy( IteratorA beginA, IteratorA endA, IteratorB endB )
	{
		while( endA != beginA ) {
			endA--;
			endB--;
			*endB = *endA;
		}
	}

	/**
	 * Find first occurence of given element. (Like STL find)
	 */
	template <class Iterator, class Value>
	inline Iterator iIndex( Iterator begin, Iterator end, Value value )
	{
		while( begin != end ) {
			if( *begin == value ) {
				return begin;
			}
			begin++;
		}
		return end;
	}

	/**
	 * Find last occurence of given element.
	 */
	template <class Iterator, class Value>
	inline Iterator iLastIndex( Iterator begin, Iterator end, Value value )
	{
		Iterator i = end;

		while( i != begin ) {
			i--;
			if( *i == value ) {
				return i;
			}
		}
		return end;
	}

	/**
	 * Delete elements that have been previously allocated with new operator.
	 */
	template <class Iterator>
	inline void iFree( Iterator begin, Iterator end )
	{
		while( begin != end ) {
			delete *begin;
			begin++;
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
   * Perform quicksort on the array. Non-recursive quicksort algorithm is used which takes first
   * element in partition as a pivot so sorting a sorted or nearly sorted array will take O(n^2)
   * time instead of O(n log n) as in general case.
   * @param array pointer to the first element in the array
   * @param count number of elements to be sorted
   */
  template <class Type>
	static void aSort( Type *array, int count )
	{
		Type *first = array;
		Type *last = array + count - 1;

		Type *stack[2048];
		Type **sp = stack;

		*( sp++ ) = first;
		*( sp++ ) = last;

		do {
			last = *( --sp );
			first = *( --sp );

			if( last <= first ) {
				continue;
			}

			// 8-14 seem as optimal tresholds for switching to selection sort
			if( last - first <= 10 ) {
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
			else {
				// quicksort
				Type *top = first;
				Type *bottom = last - 1;

				do {
					while( top <= bottom && *top <= *last ) {
						top++;
					}
					while( top < bottom && *bottom > *last ) {
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
		}
		while( sp != stack );
	}

}
