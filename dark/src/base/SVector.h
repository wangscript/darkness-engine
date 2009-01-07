/*
 *  SVector.h
 *
 *  Static size vector
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  template <class Type, int SIZE>
  class SVector
  {
    public:

      static const int CAPACITY = SIZE;

    private:

			// Pointer to data array
      Type data[SIZE];
			// Number of elements in vector
      int count;

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
          explicit Iterator( SVector &v ) : data( v.data ), count( v.count ), index( 0 )
          {}

          /**
					 * Returns true if iterator is on specified index.
					 * @param e
					 * @return
					 */
					bool operator == ( int index_ )
					{
						return index == index_;
					}

          /**
           * When iterator advances beyond last element, it's become passed. It points to an invalid
           * location.
           * @return true if iterator is passed
           */
          bool isPassed() const
          {
            return index >= count;
          }

					/**
           * Advance to next element.
           */
          void operator ++ ( int )
          {
            assert( index < count );

            index++;
          }

          /**
           * @return pointer to current element in the vector
           */
          Type *get()
          {
            return &data[index];
          }

          /**
           * @return constant pointer to current element in the vector
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

      SVector() : count( 0 )
      {}

      bool operator == ( const SVector &v ) const
      {
        return count == v.count && aEqual( data, v.data, count );
      }

      bool operator != ( const SVector &v ) const
      {
        return count != v.count || !aEqual( data, v.data, count );
      }

      Type *dataPtr()
      {
        return data;
      }

      const Type *dataPtr() const
      {
        return data;
      }

      int length() const
      {
        return count;
      }

      int capacity() const
      {
        return SIZE;
      }

      bool isEmpty() const
      {
        return count == 0;
      }

      bool contains( const Type &e )
      {
        for( int i = 0; i < count; i++ ) {
          if( data[i] == e ) {
            return true;
          }
        }
        return false;
      }

      Type &operator [] ( int i )
      {
        assert( 0 <= i && i < count );

        return data[i];
      }

      const Type &operator [] ( int i ) const
      {
        assert( 0 <= i && i < count );

        return data[i];
      }

      int index( const Type &e ) const
      {
        return aIndex( data, count, e );
      }

      int lastIndex( const Type &e ) const
      {
        return aLastIndex( data, count, e );
      }

      /**
       * @return reference to first element
       */
      Type &first()
      {
        assert( count != 0 );

        return data[0];
      }

      /**
       * @return constant reference to first element
       */
      const Type &first() const
      {
        assert( count != 0 );

        return data[0];
      }

      /**
       * @return reference to last element
       */
      Type &last()
      {
        assert( count != 0 );

        return data[count - 1];
      }

      /**
       * @return constant reference to last element
       */
      const Type &last() const
      {
        assert( count != 0 );

        return data[count - 1];
      }

      // add to the end
      void operator << ( const Type &e )
      {
        pushLast( e );
      }

      // add to the end
      void add( const Type &e )
      {
        pushLast( e );
      }

      void addAll( const SVector &v )
      {
        addAll( v.data, v.count );
      }

      void addAll( const Type *array, int arrayCount )
      {
        int newCount = count + arrayCount;

        assert( SIZE >= newCount );

        for( int i = 0; i < arrayCount; i++ ) {
          data[count + i] = array[i];
        }
        count = newCount;
      }

      // insert to given position
      void insert( int index, const Type &e )
      {
        assert( 0 <= index && index <= count );
        assert( count < SIZE );

        aRCopy( data + index + 1, data + index, count - index );
        data[index] = e;
        count++;
      }

      // add element to the end, if it doesn't exist yet
      bool include( const Type &e )
      {
        if( aIndex( data, count, e ) == -1 ) {
          assert( count < SIZE );

          data[count] = e;
          count++;
          return true;
        }
        else {
          return false;
        }
      }

      int includeAll( const SVector &v )
      {
        return includeAll( v.data, v.count );
      }

      int includeAll( const Type *array, int count )
      {
        int n = 0;
        for( int i = 0; i < count; i++ ) {
          n += include( array[i] );
        }
        return n;
      }

      void pushFirst( const Type &e )
      {
        return insert( e, 0 );
      }

      void pushLast( const Type &e )
      {
        assert( count < SIZE );

        data[count] = e;
        count++;
      }

      SVector operator -- ( int )
      {
        assert( count != 0 );

        count--;
        return *this;
      }

      // remove element by index
      void remove( int index )
      {
        assert( 0 <= index && index < count );

        count--;
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

      int excludeAll( const SVector &v )
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
        aSort( data, count );
      }

      /**
       * Sort elements with quicksort algorithm (middle element as pivot).
       */
      void sort2()
      {
        aSort2( data, count );
      }

      // remove all elements
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
