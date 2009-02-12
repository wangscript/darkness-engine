/*
 *  PoolAlloc.h
 *
 *  Pool allocator
 *  Base class for allocation of memory for same-size elements. All classes which inherit from
 *  PoolAlloc will have overloaded new and delete (BUT NOT new[] and delete[]) operators. Before
 *  you use it, you should create Pool<Type> for each class.
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{
  template<class Type>
  class PoolAlloc;

  template <class Type>
  class Pool
  {
    private:

      // Pointer to data array
      Type *data;
      // Size of data array
      int  size;
      // Number of used slots in the pool
      int  count;
      // List of free slots (by indices in data array, not by pointers)
      Type *freeSlot;

      Pool( const Pool& );
      Pool &operator = ( const Pool& );

    public:

      /**
       * Create empty pool with initial capacity 8.
       * @param initSize
       */
      explicit Pool() : data( new Type[8] ), size( 8 ), count( 0 ), freeSlot( &data[0] )
      {
        int last = size - 1;
        for( int i = 1; i < last; i++ ) {
          data[i].PoolAlloc<Type>::next = &data[i + 1];
        }
        data[last].PoolAlloc<Type>::next = null;
      }

      /**
       * Create empty pool with given initial capacity.
       * @param initSize
       */
      explicit Pool( int initSize ) : data( new Type[initSize] ), size( initSize ),
          count( 0 ), freeSlot( &data[0] )
      {
        int last = size - 1;
        for( int i = 1; i < last; i++ ) {
          data[i].PoolAlloc<Type>::next = &data[i + 1];
        }
        data[last].PoolAlloc<Type>::next = null;
      }

      /**
       * Destructor.
       */
      ~Pool()
      {
        assert( count == 0 );

        delete[] data;
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
       * Allocate a new element.
       * We need to save pointer to this Pool to next field so we know from which Pool to remove
       * when we call delete operator.
       * Pool when calling delete operator.
       * @param e
       */
      void *alloc()
      {
        assert( freeSlot != null );

        Type *slot = freeSlot;
        freeSlot = slot->PoolAlloc<Type>::next;
        slot->PoolAlloc<Type>::next = (Type*) this;
        count++;
        return slot;
      }

      /**
       * Free given element.
       * @param index
       */
      void free( Type *elem )
      {
        assert( count != 0 );

        elem->PoolAlloc<Type>::next = freeSlot;
        count--;
      }

  };

  template <class Type>
  class PoolAlloc
  {
    friend class Pool<Type>;

    private:

      static Pool<Type> *pool;

      Type *next;

    public:

      PoolAlloc()
      {}

      /**
       * Set default pool for Type.
       * @param pool_
       */
      static void setPool( Pool<Type> *pool_ )
      {
        assert( pool == null );

        pool = pool_;
      }

      /**
       * Get an empty slot from default pool for Type.
       * @param
       * @return
       */
      void *operator new ( uint )
      {
        assert( pool != null );

        return pool->alloc();
      }

      /**
       * Get an empty slot from specified pool.
       * @param
       * @param pool
       * @return
       */
      void *operator new ( uint, Pool<Type> *pool )
      {
        assert( pool != null );

        return pool->alloc();
      }

      /**
       * Delete object
       * @param object
       */
      void operator delete ( void *object )
      {
        Type *slot = (Type*) object;
        Pool<Type> *pool = (Pool<Type>*) slot->PoolAlloc<Type>::next;

        pool->free( slot );
      }
  };

  template <class Type>
  Pool<Type> *PoolAlloc<Type>::pool = null;

}
