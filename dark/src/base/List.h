/*
 *  List.h
 *
 *  Linked list
 *  The Type should provide the "next[INDEX]" pointer
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_List_h_
#define _Dark_List_h_

namespace Dark
{

  /**
   * Linked list
   *
   * It can only be applied on classes that have next[] member.
   * Example:
   * <pre>
   * class C
   * {
   *   C next[2];
   *   int value;
   * };
   * ...
   * List&lt;C, 0&gt; list1;
   * List&lt;C, 1&gt; list2;</pre>
   * That way the objects of the same class can be in two separate lists at once.
   * next[0] points to next element in list1 and
   * next[1] points to next element in list2.
   *
   * next[INDEX] pointer is not cleared when element is removed from the list,
   * it may still point to elements in the list or to invalid locations!
   *
   * List class doesn't take care of memory management except for the free() method.
   *
   * In general all operations are O(1) except contains(), length(), disjoin() and free() are O(n).
   */
  template <class Type, int INDEX>
  class List
  {
    private:

      // First element in list.
      Type *firstElem;

      // No copying
      List( const List& );

    public:

      /**
       * List iterator
       */
      class Iterator
      {
        protected:

          Type *elem;

        public:

          /**
           * Make iterator for given list. After creation it points to first element.
           * @param l
           */
          explicit Iterator( List &l ) : elem( l.firstElem )
          {}

          /**
           * When iterator advances beyond last element, it's become passed. It points to null.
           * @return true if iterator is passed
           */
          bool isPassed() const
          {
            return elem == null;
          }

          /**
           * Advance to next element.
           */
          void next()
          {
            assert( elem != null );

            elem = elem->next[INDEX];
          }

          /**
           * @return pointer current element in the list
           */
          Type *get()
          {
            return elem;
          }

          /**
           * @return constant pointer current element in the list
           */
          const Type *get() const
          {
            return elem;
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

      /**
       * Create an empty list.
       */
      List() : firstElem( null )
      {}

      /**
       * Create a list with only one element.
       * @param e the element
       */
      explicit List( const Type *e ) : firstElem( e )
      {
        e->next[INDEX] = null;
      }

      /**
       * Count the elements in the list.
       * @return size of the list
       */
      int length() const
      {
        int i = 0;
        Type *p = firstElem;

        while( p != null ) {
          p = p->next[INDEX];
          i++;
        }
        return i;
      }

      /**
       * @return true if the list has no elements
       */
      bool isEmpty() const
      {
        return firstElem == null;
      }

      /**
       * @param e requested element
       * @return true if some element in the list points to the requested element
       */
      bool contains( const Type *e ) const
      {
        assert( e != null );

        Type *p = firstElem;

        while( p != null ) {
          if( p == e ) {
            return true;
          }
          p = p->next[INDEX];
        }
        return false;
      }

      /**
       * @return first element in the list
       */
      Type *first() const
      {
        return firstElem;
      }

      /**
       * Add element to the beginning of the list.
       * @param e element to be added
       */
      void operator << ( Type *e )
      {
        pushFirst( e );
      }

      /**
       * Add element to the beginning of the list.
       * @param e element to be added
       */
      void add( Type *e )
      {
        pushFirst( e );
      }

      /**
       * Add element to the beginning of the list.
       * @param e element to be added
       */
      void pushFirst( Type *e )
      {
        assert( e != null );

        e->next[INDEX] = firstElem;
        firstElem = e;
      }

      void operator >> ( Type *&e )
      {
        e = popFirst();
      }

      /**
       * Pop first element from the list.
       * @param e reference to pointer where the pointer to the first element is to be saved
       */
      Type *popFirst()
      {
        assert( firstElem != null );

        Type *p = firstElem;

        firstElem = p->next[INDEX];
        p->next[INDEX] = null;
        return p;
      }

      void insertAfter( Type *e, Type *p )
      {
        assert( e != null );
        assert( p != null );

        e->next[INDEX] = p->next[INDEX];
        p->next[INDEX] = e;
      }

      // UNSAFE !!!
      void remove( Type *e, Type *prev )
      {
        assert( prev == null || prev->next[INDEX] == e );

        if( prev == null ) {
          firstElem = e->next[INDEX];
        }
        else {
          prev->next[INDEX] = e->next[INDEX];
        }
        e->next[INDEX] = null;
      }

      void free()
      {
        Type *p = firstElem;

        while( p != null ) {
          Type *next = p->next[INDEX];

          delete p;
          p = next;
        }
        firstElem = null;
      }

      void disjoin()
      {
        Type *p = firstElem;

        while( p != null ) {
          Type *next = p->next[INDEX];

          p->next[INDEX] = null;
          p = next;
        }
        firstElem = null;
      }

  };

}

#endif // _Dark_List_h_
