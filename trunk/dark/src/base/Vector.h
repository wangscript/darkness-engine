/*
 *  Vector.h
 *
 *  Vector
 *  It can be also used as stack or small set
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  template <class Type>
  class Vector
  {
    private:

      // Pointer to data array
      Type *data;
      // Size of data array
      int  size;
      // Number of elements in vector
      int  count;

    private:

      /**
       * Enlarge capacity by two times if there's not enough space to add another element.
       */
      void ensureCapacity()
      {
        if( size == count ) {
          size *= 2;
          assert( size <= 1024*1024*10 );
          data = aRealloc( data, count, size );
        }
      }

    public:

      /**
       * Vector iterator.
       */
      class Iterator
      {
        protected:

          Type *data;
          int  count;
          int  index;

        public:

          /**
           * Make iterator for given vector. After creation it points to first element.
           * @param v
           */
          explicit Iterator( Vector &v ) : data( v.data ), count( v.count ), index( 0 )
          {}

          /**
           * When iterator advances beyond last element, it's become passed. It points to an invalid
           * location.
           * @return true if iterator is passed
           */
          bool isPassed()
          {
            return index >= count;
          }

          /**
           * Advance to next element.
           */
          void next()
          {
            assert( index < count );

            index++;
          }

          /**
           * @return pointer current element in the vector
           */
          Type *get()
          {
            return &data[index];
          }

          /**
           * @return constant pointer current element in the vector
           */
          const Type *get() const
          {
            return &data[index];
          }

          /**
           * @return reference to current element in the vector
           */
          Type &operator * ()
          {
            return data[index];
          }

          /**
           * @return constant reference to current element in the vector
           */
          const Type &operator * () const
          {
            return data[index];
          }

      };

      /**
       * Create empty vector with initial capacity 8.
       */
      Vector() : data( new Type[8] ), size( 8 ), count( 0 )
      {}

      /**
       * Copy constructor.
       * @param v original vector
       */
      Vector( const Vector &v ) : data( new Type[8] ), size( v.size ), count( v.count )
      {
        aCopy( data, v.data, count );
      }

      /**
       * Create empty vector with given initial capacity.
       * @param initSize initial capacity
       */
      explicit Vector( int initSize ) : size( initSize ), count( 0 )
      {
        data = new Type[size];
      }

      /**
       * Destructor.
       */
      ~Vector()
      {
        delete[] data;
      }

      /**
       * Copy operator.
       * @param v
       * @return
       */
      Vector &operator = ( const Vector &v )
      {
        // create new data array of the new data doesn't fit, keep the old one otherwise
        if( size < v.count ) {
          delete[] data;
          data = new Type[v.size];
        }
        count = v.count;
        aCopy( data, v.data, count );
        return *this;
      }

      /**
       * Euality operator. Capacity of vectors doesn't matter.
       * @param v
       * @return true if all elements in both vectors are equal
       */
      bool operator == ( const Vector &v ) const
      {
        return count == v.count && aEqual( data, v.data, count );
      }

      /**
       * Ineuality operator. Capacity of vectors doesn't matter.
       * @param v
       * @return false if all elements in both vectors are equal
       */
      bool operator != ( const Vector &v ) const
      {
        return count != v.count || !aEqual( data, v.data, count );
      }

      /**
       * Get pointer to <code>data</code> array. Use with caution, since you can easily make buffer
       * overflows if you don't check the size of <code>data</code> array.
       * @return non-constant pointer to data array
       */
      Type *dataPtr()
      {
        return data;
      }

      /**
       * Get pointer to <code>data</code> array. Use with caution, since you can easily make buffer
       * overflows if you don't check the size of <code>data</code> array.
       * @return constant pointer to data array
       */
      const Type *dataPtr() const
      {
        return data;
      }

      /**
       * @return number of elements in the vector
       */
      int length() const
      {
        return count;
      }

      /**
       * @return capacity of the vector
       */
      int capacity() const
      {
        return size;
      }

      /**
       * @return true if vector has no elements
       */
      bool isEmpty() const
      {
        return count == 0;
      }

      /**
       * Trim vector, leave at most <code>left</code> elements/capacity.
       * @param left
       */
      void trim( int left )
      {
        int newCapacity = count + left;

        if( newCapacity < size ) {
          size = newCapacity;
          data = aRealloc( data, count, size );
        }
      }

      /**
       * @param e element to be looked for
       * @return true if the element is found in the vector
       */
      bool contains( const Type &e )
      {
        for( int i = 0; i < count; i++ ) {
          if( data[i] == e ) {
            return true;
          }
        }
        return false;
      }

      /**
       * @param i index
       * @return reference i-th element
       */
      Type &operator [] ( int i )
      {
        assert( 0 <= i && i < count );

        return data[i];
      }

      /**
       * @param i index
       * @return constant reference i-th element
       */
      const Type &operator [] ( int i ) const
      {
        assert( 0 <= i && i < count );

        return data[i];
      }

      /**
       * Find the first occurence of an element.
       * @param e element to be looked for
       * @return index of first occurence, -1 if not found
       */
      int index( const Type &e ) const
      {
        return aIndex( data, count, e );
      }

      /**
       * Find the last occurence of an element.
       * @param e element to be looked for
       * @return index of last occurence, -1 if not found
       */
      int lastIndex( const Type &e ) const
      {
        return aLastIndex( data, count, e );
      }

      /**
       * @return first element
       */
      Type first() const
      {
        assert( count != 0 );

        return data[0];
      }

      /**
       * @return last element
       */
      Type last() const
      {
        assert( count != 0 );

        return data[count - 1];
      }

      /**
       * Add an element to the end.
       * @param e element to be added
       */
      void operator << ( const Type &e )
      {
        pushLast( e );
      }

      /**
       * Add an element to the end.
       * @param e element to be added
       */
      void add( const Type &e )
      {
        pushLast( e );
      }

      /**
       * Add an element to the beginning.
       * @param e
       */
      void pushFirst( const Type &e )
      {
        return insert( e, 0 );
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
       * @param v vector to be added
       */
      void addAll( const Vector &v )
      {
        addAll( v.data, v.count );
      }

      /**
       * Add all elements from an array to the end.
       * @param array pointer to first element from the array
       * @param arrayCount number of elements in the array
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
       * @param e element to be included
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
       * Include all elements from a vector.
       * @param v vector to be included
       * @return number of elements that have been added
       */
      int includeAll( const Vector &v )
      {
        return includeAll( v.data, v.count );
      }

      /**
       * Include all elements from an array.
       * @param array pointer to the first element of the array
       * @param count number of elements in the array
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
       * Insert an element to the given position. All later elements are shifted to make a gap
       * for the new element.
       * @param e element to be inserted
       * @param index position
       */
      void insert( const Type &e, int index )
      {
        assert( 0 <= index && index < count );

        ensureCapacity();
        aRCopy( data + index + 1, data + index, count - index );
        data[index] = e;
        count++;
      }

      /**
       * Remove last element.
       * @param
       * @return
       */
      Vector operator -- ( int )
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

        aCopy( data + index, data + index + 1, count - index );
      }

      // find and remove given element
      bool exclude( const Type &e )
      {
        int i = aIndex( data, count, e );

        if( i != -1 ) {
          count--;
          aCopy( data + i, data + i + 1, count - i );

          return true;
        }
        else {
          return false;
        }
      }

      int excludeAll( const Vector &v )
      {
        return excludeAll( v.data, v.count );
      }

      int excludeAll( const Type *array, int count )
      {
        int n = 0;
        for( int i = 0; i < count; i++ ) {
          n += exclude( array[i] );
        }
        return n;
      }

      Type popFirst()
      {
        Type e = data[0];

        count--;
        aCopy( data, data + 1, count );

        return e;
      }

      // pop
      void operator >> ( Type &e )
      {
        e = popLast();
      }

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
        aSort( data, 0, count - 1 );
      }

      /**
       * Sort elements with quicksort algorithm (middle element as pivot).
       */
      void sort2()
      {
        aSort2( data, 0, count - 1 );
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
