/*
 *  Reuser.h
 *
 *  Base class for memory reusing. All classes which inherit from Reuser must have "next" member
 *  and will have overloaded new and delete (BUT NOT new[] and delete[]) operators. The new operator
 *  will try to reuse memory from deleted objects form that class. At least the end of the program
 *  you should call Class::deallocate() for all Reuser-derived classes. Performance can increase up
 *  to 100%.
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  template <class Type>
  class Reuser
  {
    private:

      static Reuser *freeList;

      Reuser *next;

      void free()
      {
        if( next != null ) {
          next->free();
        }
        ::delete this;
      }

    public:

#ifdef DARK_USE_REUSER
      Reuser() : next( null )
      {}

      // If the list of freed blocks isn't empty, reuse the last freed block (at the beginning of
      // the list), otherwise allocate new block. (Constructor is called automatically.)
      void *operator new ( uint size )
      {
        if( freeList != null ) {
          Reuser *p = freeList;
          freeList = freeList->next;

          return p;
        }
        return ::new char[size];
      }

      // Do not really free memory, add it at the beginning of the list of freed blocks.
      // (Destructor is called automatically.)
      void operator delete ( void *ptr )
      {
        Reuser *p = (Reuser*) ptr;

        // note that space for destroyed object is still allocated
        p->next = freeList;
        freeList = p;
      }
#endif

      // It's good idea to call that function from time to time and at the end of the program to
      // free some memory and to prevent memory leaks.
      static void deallocate()
      {
#ifdef DARK_USE_REUSER
        if( freeList != null ) {
          freeList->free();
          freeList = null;
        }
#endif
      }

  };

  template <class Type>
  Reuser<Type> *Reuser<Type>::freeList = null;

}
