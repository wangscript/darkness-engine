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

#ifndef _Dark_Vector_h_
#define _Dark_Vector_h_

namespace Dark
{

  template <class Type>
  class Vector
  {
    private:

      Type *data;
      int  size;
      int  count;

    private:

      void ensureCapacity()
      {
        if( size == count ) {
          size *= 2;
          assert( size <= 1024*1024*10 );
          data = aRealloc( data, count, size );
        }
      }

    public:

      class Iterator
      {
        protected:

          Type *data;
          int  count;
          int  index;

        public:

          explicit Iterator( Vector &v ) : data( v.data ), count( v.count ), index( 0 )
          {}

          bool isPassed()
          {
            return index >= count;
          }

          Type *get() const
          {
            return &data[index];
          }

          Type &operator * () const
          {
            return data[index];
          }

          void next()
          {
            assert( index < count );

            index++;
          }

      };

      Vector() : data( new Type[8] ), size( 8 ), count( 0 )
      {}

      Vector( const Vector &v ) : data( new Type[8] ), size( v.size ), count( v.count )
      {
        aCopy( data, v.data, count );
      }

      explicit Vector( int initSize ) : size( initSize ), count( 0 )
      {
        data = new Type[size];
      }

      ~Vector()
      {
        delete[] data;
      }

      Vector &operator = ( const Vector &v )
      {
        if( size < v.count ) {
          delete[] data;
          data = new Type[v.size];
        }
        count = v.count;
        aCopy( data, v.data, count );
        return *this;
      }

      bool operator == ( const Vector &v ) const
      {
        return count == v.count && aEqual( data, v.data, count );
      }

      bool operator != ( const Vector &v ) const
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
        return size;
      }

      bool isEmpty() const
      {
        return count == 0;
      }

      // trim vector, leave at most "left" space
      void trim( int left )
      {
        int newCapacity = count + left;

        if( newCapacity < size ) {
          size = newCapacity;
          data = aRealloc( data, count, size );
        }
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

      // first element
      Type first() const
      {
        assert( count != 0 );

        return data[0];
      }

      // last element
      Type last() const
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

      void addAll( const Vector &v )
      {
        addAll( v.data, v.count );
      }

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

      // insert to given position
      void insert( const Type &e, int index )
      {
        assert( 0 <= index && index < count );

        ensureCapacity();
        aRCopy( data + index + 1, data + index, count - index );
        data[index] = e;
        count++;
      }

      // add element to the end, if it doesn't exist yet
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

      int includeAll( const Vector &v )
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
        ensureCapacity();
        data[count] = e;
        count++;
      }

      Vector operator -- ( int )
      {
        assert( count != 0 );

        count--;
        return *this;
      }

      // remove element by index
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

      // sort elements with quicksort algorithm
      void sort()
      {
        aSort( data, 0, count - 1 );
      }

      // remove all elements
      void clear()
      {
        count = 0;
      }

      // remove and delete all elements ( for vector of pointers )
      void free()
      {
        for( int i = 0; i < count; i++ ) {
          delete data[i];
        }
        count = 0;
      }

  };

}

#endif // _Dark_Vector_h_
