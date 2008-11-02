/*
 *  DList.h
 *
 *  Double-linked list
 *  The Type should provide the "prev[INDEX]" and "next[INDEX]" pointers
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_DList_h_
#define _Dark_DList_h_

namespace Dark
{

  /**
   * Double-linked list
   *
   * It can only be applied on classes that have next[] and prev[] members.
   * Example:
   * <pre>
   * class C
   * {
   *   C prev[2];
   *   C next[2];
   *   int value;
   * };
   * ...
   * DList&lt;C, 0&gt; list1;
   * DList&lt;C, 1&gt; list2;</pre>
   * That way the objects of the same class can be in two separate lists at once.
   * prev[0] and next[0] point to previous and next element respectively in list1 and
   * prev[1] and next[1] point to previous and next element respectively in list2.
   *
   * prev[INDEX] and next[INDEX] pointers are not cleared when element is removed from the list,
   * they may still point to elements in the list or to invalid locations!
   *
   * DList class doesn't take care of memory management except for the free() method.
   *
   * In general all operations are O(1) except contains(), length(), disjoin() and free() are O(n).
   */
  template <class Type, int INDEX>
  class DList
  {
    private:

      // First element in list.
      Type *firstElem;
      // Last element in list.
      Type *lastElem;

      // No copying
      DList( const DList& );

    public:

      /**
       * DList iterator
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
          explicit Iterator( const DList &l ) : elem( l.firstElem )
          {}

          /**
           * When iterator advances beyond last element, it's become passed. It points to null.
           * @return true if iterator is passed
           */
          bool isPassed()
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
      DList() : firstElem( null ), lastElem( null )
      {}

      /**
       * Create a list with only one element.
       * @param e the element
       */
      explicit DList( const Type *e ) : firstElem( e ), lastElem( e )
      {
        e->prev[INDEX] = null;
        e->next[INDEX] = null;
      }

      /**
       * Count the elements in the list.
       * @return size of the list
       */
      int length() const
      {
        int i = 1;
        Type *p = firstElem;

        while( p != lastElem ) {
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
        assert( ( firstElem == null ) == ( lastElem == null ) );

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
       * @return last element in the list
       */
      Type *last() const
      {
        return lastElem;
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

        e->prev[INDEX] = null;
        e->next[INDEX] = firstElem;

        if( firstElem == null ) {
          firstElem = e;
          lastElem = e;
        }
        else {
          firstElem->prev[INDEX] = e;
          firstElem = e;
        }
      }

      /**
       * Add element to the end of the list.
       * @param e element to be added
       */
      void pushLast( Type *e )
      {
        assert( e != null );

        e->prev[INDEX] = lastElem;
        e->next[INDEX] = null;

        if( lastElem == null ) {
          firstElem = e;
          lastElem = e;
        }
        else {
          lastElem->next[INDEX] = e;
          lastElem = e;
        }
      }

      /**
       * Pop first element from the list.
       * @param e reference to pointer where the pointer to the first element is to be saved
       */
      void operator >> ( Type *&e )
      {
        e = popFirst();
      }

      /**
       * Pop first element from the list.
       * @param e pointer to the first element
       */
      Type *popFirst()
      {
        assert( firstElem != null );

        Type *p = firstElem;

        firstElem = p->next[INDEX];

        if( firstElem == null ) {
          lastElem = null;
        }
        else {
          firstElem->prev[INDEX] = null;
        }
        return p;
      }

      /**
       * Pop first element from the list.
       * @param e pointer to the first element
       */
      Type *popLast()
      {
        assert( lastElem != null );

        Type *p = lastElem;

        lastElem = p->prev[INDEX];

        if( lastElem == null ) {
          firstElem = null;
        }
        else {
          lastElem->next[INDEX] = null;
        }
        return p;
      }

      /**
       * Insert an element after an element in the list.
       * @param e element to be inserted
       * @param p pointer to element after which we want to insert
       */
      void insertAfter( Type *e, Type *p )
      {
        assert( e != null );
        assert( p != null );

        e->prev[INDEX] = p;

        if( p == lastElem ) {
          e->next[INDEX] = null;
          p->next[INDEX] = e;
          lastElem = e;
        }
        else {
          e->next[INDEX] = p->next[INDEX];
          p->next[INDEX]->prev[INDEX] = e;
          p->next[INDEX] = e;
        }
      }

      /**
       * Insert an element before an element in the list.
       * @param e element to be inserted
       * @param p pointer to element before which we want to insert
       */
      void insertBefore( Type *e, Type *p )
      {
        assert( e != null );
        assert( p != null );

        e->next[INDEX] = p;

        if( p == firstElem ) {
          e->prev[INDEX] = null;
          p->prev[INDEX] = e;
          firstElem = e;
        }
        else {
          e->prev[INDEX] = p->prev[INDEX];
          p->prev[INDEX]->next[INDEX] = e;
          p->prev[INDEX] = e;
        }
      }

      /**
       * Remove an element from the list.
       * @param e element to be removed
       */
      void remove( Type *e )
      {
        if( e == firstElem ) {
          firstElem = e->next[INDEX];
        }
        else {
          e->prev[INDEX]->next[INDEX] = e->next[INDEX];
        }
        if( e == lastElem ) {
          lastElem = e->prev[INDEX];
        }
        else {
          e->next[INDEX]->prev[INDEX] = e->prev[INDEX];
        }
      }

      /**
       * Empty the list but don't delete the elements.
       */
      void disjoin()
      {
        Type *p = firstElem;

        while( p != null ) {
          Type *next = p->next[INDEX];

          p->next[INDEX] = null;
          p->prev[INDEX] = null;

          p = next;
        }

        firstElem =  null;
        lastElem = null;
      }

      /**
       * Empty the list and delete all elements - take care of memory managment.
       */
      void free()
      {
        Type *p = firstElem;

        while( p != null ) {
          Type *next = p->next[INDEX];

          delete p;
          p = next;
        }

        firstElem = null;
        lastElem = null;
      }

  };

}

#endif // _Dark_DList_h_
