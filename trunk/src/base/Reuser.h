/*
 *  Reuser.h
 *
 *  Base class for memory reusing. All classes which interihate from Reuser must have "next" member
 *  and will have overloaded new and delete (BUT NOT new[] and delete[]) operators. The new operator
 *  will try to reuse memory from deleted objects form that class. At least the end of the program
 *  you should call Class::deallocate() for all Reuser-derived classes. Performance can increase up
 *  to 100%.
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Reuser.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Reuser_h_
#define _Reuser_h_

namespace Dark
{

  template <class Type>
  class Reuser
  {
    private:

      static Reuser *freeList;

    public:

      Reuser *next;

      void free()
      {
        if( next != null ) {
          next->free();
        }
        ::delete this;
      }

    public:

      Reuser() : next( null )
      {}

      // If the list of freed blocks isn't empty, reuse the last freed block (at the beginning of
      // the list), otherwise allocate new block. (Constructor is called automatically.)
      void *operator new ( size_t size )
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

      // It's good idea to call that function from time to time and at the end of the program to
      // free some memory and to prevent memory leaks.
      static void deallocate()
      {
        if( freeList != null ) {
          freeList->free();
          freeList = null;
        }
      }
  };

  template <class Type>
  Reuser<Type>* Reuser<Type>::freeList = null;

}

#endif // _Dark_Reuser_h_
