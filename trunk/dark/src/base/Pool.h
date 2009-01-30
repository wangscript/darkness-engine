/*
 *  Pool.h
 *
 *  Pool of same-sized elements
 *
 *  Vector-like structure for allocation of same-sized elements.
 *  It doesn't allow shifting of elements so inserting in the middle is not allowed and when an
 *  element is removed a free slot remains there. When adding an element it first tries to occupy
 *  all the free slots and when there's no any, it adds the element to the end.
 *  Type should provide int nextSlot field to hold index of next free slot.
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  template <class Type, int INDEX>
  class Pool
  {
    public:

      /**
       * Pool iterator.
       */
      class Iterator : public Dark::Iterator<Type>
      {
        private:

          // base class
          typedef Dark::Iterator<Type> B;

        public:

          /**
           * Make iterator for given pool. After creation it points to first element.
           * @param v
           */
          explicit Iterator( Pool &v ) : B( v.data, v.data + v.count )
          {}

          /**
           * Advance to next element.
           */
          void operator ++ ( int )
          {
            assert( B::elem != B::past );

            do {
              B::elem++;
            }
            while( B::elem != B::past && B::elem->nextSlot != -1 );
          }

      };

    private:

      // Pointer to data array
      Type *data;
      // Size of data array
      int  size;
      // Number of used slots in the pool
      int  count;
      // List of free slots (by indices in data array, not by pointers)
      int  freeSlot;

      Pool( const Pool& );
      Pool &operator = ( const Pool& );

      /**
       * Enlarge capacity by two times if there's not enough space to add another element.
       */
      void ensureCapacity()
      {
        if( freeSlot == -1 ) {
          size *= 2;
          assert( size <= 1024*1024*10 );
          data = aRealloc( data, count, size );
        }
      }

    public:

      /**
       * Create empty pool with initial capacity 8.
       */
      Pool() : data( new Type[8] ), size( 8 ), count( 0 ), freeSlot( 0 )
      {
        for( int i = 0; i < size; ) {
          data[i].nextSlot = ++i;
        }
      }

      /**
       * Create empty pool with given initial capacity.
       * @param initSize
       */
      explicit Pool( int initSize ) : size( initSize ), count( 0 ), freeSlot( 0 )
      {
        data = new Type[size];

        for( int i = 0; i < size; ) {
          data[i].nextSlot = ++i;
        }
      }

      /**
       * Destructor.
       */
      ~Pool()
      {
        delete[] data;
      }

      /**
       * @return iterator for this pool
       */
      Iterator iterator()
      {
        return Iterator( *this );
      }

      /**
       * @return number of used slots in the pool
       */
      int length() const
      {
        return count;
      }

      /**
       * @return capacity of the pool
       */
      int capacity() const
      {
        return size;
      }

      /**
       * @return true if pool has no used slots
       */
      bool isEmpty() const
      {
        return count == 0;
      }

      /**
       * @param e
       * @return true if the element is found in the pool
       */
      bool contains( const Type &e )
      {
        for( int i = 0; i < count; i++ ) {
          if( data[i].next[INDEX] == null && data[i] == e ) {
            return true;
          }
        }
        return false;
      }

      bool isFree( int i ) const
      {
        return data[i] != null;
      }

      /**
       * @param i
       * @return reference i-th element
       */
      Type &operator [] ( int i )
      {
        assert( 0 <= i && i < count );

        return data[i];
      }

      /**
       * @param i
       * @return constant reference i-th element
       */
      const Type &operator [] ( int i ) const
      {
        assert( 0 <= i && i < count );

        return data[i];
      }

      /**
       * Find the first occurence of an element.
       * @param e
       * @return index of first occurence, -1 if not found
       */
      int index( const Type &e ) const
      {
        return aIndex( data, count, e );
      }

      /**
       * Find the last occurence of an element.
       * @param e
       * @return index of last occurence, -1 if not found
       */
      int lastIndex( const Type &e ) const
      {
        return aLastIndex( data, count, e );
      }

      /**
       * Add an element to the end.
       * @param e
       */
      void operator << ( const Type &e )
      {
        pushLast( e );
      }

      /**
       * Add an element to the end.
       * @param e
       */
      void add( const Type &e )
      {
        pushLast( e );
      }

      /**
       * Add an element to the end.
       * @param e
       */
      void pushLast( const Type &e )
      {
        ensureCapacity();
        data[count] = e;
        count++;
      }

      /**
       * Add all elements from a vector to the end.
       * @param v
       */
      void addAll( const Vector<Type> &v )
      {
        addAll( v.data, v.count );
      }

      /**
       * Add all elements from an array to the end.
       * @param array
       * @param arrayCount
       */
      void addAll( const Type *array, int arrayCount )
      {
        int newCount = count + arrayCount;

        if( size < newCount ) {
          size = max( size * 2, newCount );
          data = aRealloc( data, count, size );
        }
        for( int i = 0; i < arrayCount; i++ ) {
          data[count + i] = array[i];
        }
        count = newCount;
      }

      /**
       * Add an element to the end, but only if there's no any equal element in the vector.
       * This function is useful if you plan to use vector as a set.
       * @param e
       * @return true if element has been added
       */
      bool include( const Type &e )
      {
        if( aIndex( data, count, e ) == -1 ) {
          ensureCapacity();

          data[count] = e;
          count++;
          return true;
        }
        else {
          return false;
        }
      }

      /**
       * Add all elements from given vector which are not yet included in this vector.
       * @param v
       * @return number of elements that have been added
       */
      int includeAll( const Vector<Type> &v )
      {
        return includeAll( v.data, v.count );
      }

      /**
       * Add all elements from given array which are not yet included in this vector.
       * @param array
       * @param count
       * @return number of elements that have been added
       */
      int includeAll( const Type *array, int count )
      {
        int n = 0;
        for( int i = 0; i < count; i++ ) {
          n += include( array[i] );
        }
        return n;
      }

      /**
       * Remove last element.
       * @param
       * @return
       */
      Pool &operator -- ( int )
      {
        assert( count != 0 );

        count--;
        return *this;
      }

      /**
       * Remove the element at given position. All later element are shifted to fill the gap.
       * @param index
       */
      void remove( int index )
      {
        assert( 0 <= index && index < count );

        count--;
        aCopy( data + index, data + index + 1, count - index );
      }

      /**
       * Find and remove the given element.
       * @param e
       * @return
       */
      bool exclude( const Type &e )
      {
        int index = aIndex( data, count, e );

        if( index != -1 ) {
          remove( index );

          return true;
        }
        else {
          return false;
        }
      }

      /**
       * Remove intersection of vectors from this vector.
       * @param v
       * @return
       */
      int excludeAll( const Vector<Type> &v )
      {
        return excludeAll( v.data, v.count );
      }

      /**
       * Remove intersection of this vector and given array from this vector.
       * @param v
       * @return
       */
      int excludeAll( const Type *array, int count )
      {
        int n = 0;
        for( int i = 0; i < count; i++ ) {
          n += exclude( array[i] );
        }
        return n;
      }

      /**
       * Remove first element
       * @return value of removed element
       */
      Type popFirst()
      {
        Type e = data[0];

        count--;
        aCopy( data, data + 1, count );

        return e;
      }

      /**
       * Remove last element
       * @param e reference to variable to be overwritten with value of removed element
       */
      void operator >> ( Type &e )
      {
        e = popLast();
      }

      /**
       * Remove last element
       * @return value of removed element
       */
      Type popLast()
      {
        assert( count != 0 );

        count--;

        return data[count];
      }

      /**
       * Sort elements with quicksort algorithm (last element as pivot).
       */
      void sort()
      {
        aSort( data, count );
      }

      /**
       * Empty the vector but don't delete the elements.
       */
      void clear()
      {
        count = 0;
      }

      /**
       * Empty the list and delete all elements - take care of memory managment. Use this function
       * only with vector of pointer that you want to be deleted.
       */
      void free()
      {
        for( int i = 0; i < count; i++ ) {
          delete data[i];
        }
        count = 0;
      }

  };

}
