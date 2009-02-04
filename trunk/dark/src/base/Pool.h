/*
 *  Pool.h
 *
 *  Pool of same-sized elements
 *
 *  Vector-like structure for allocation of same-size elements.
 *  It doesn't allow shifting of elements so inserting in the middle is not allowed and when an
 *  element is removed a free slot remains there. When adding an element it first tries to occupy
 *  all the free slots and when there's no any, it adds the element to the end.
 *  Type should provide int nextSlot field to hold index of the next free slot.
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{
  template<class Type>
  class Pool;

  template <class Type>
  class PoolAlloc
  {
    friend class Pool<Type>;

    public:

      void *next;

    public:

      PoolAlloc()
      {}

      void *operator new ( uint, Pool<Type> &pool )
      {
        return pool.alloc();
      }

      void operator delete ( void *object )
      {
        Type *elem = (Type*) object;
        Pool<Type> *pool = (Pool<Type>*) elem->PoolAlloc<Type>::next;

        pool->free( elem );
      }
  };

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
       * Create empty pool with given initial capacity.
       * @param initSize
       */
      explicit Pool( int initSize ) : size( initSize ), count( 0 ), freeSlot( 0 )
      {
        data = new Type[size];

        for( int i = 0, j = 1; j < size; i++, j++ ) {
          data[i].PoolAlloc<Type>::next = &data[j];
        }
        freeSlot = &data[0];
        data[size - 1].PoolAlloc<Type>::next = null;
      }

      /**
       * Destructor.
       */
      ~Pool()
      {
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
       * @param e
       */
      void *alloc()
      {
        assert( freeSlot != null );

        Type *slot = freeSlot;
        freeSlot = (Type*) slot->PoolAlloc<Type>::next;
        slot->PoolAlloc<Type>::next = this;
        count++;
        return slot;
      }

      /**
       * Free given element.
       * @param index
       */
      void free( Type *elem )
      {
        elem->PoolAlloc<Type>::next = freeSlot;
        freeSlot = elem;
        count--;
      }

  };

}
