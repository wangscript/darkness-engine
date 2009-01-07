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

#pragma once

namespace Dark
{

  /**
   * Double-linked list
   *
   * It can only be applied on classes that have <code>next[]</code> and <code>prev[]</code>
   * members.
   * Example:
   * <pre>class C
   * {
   *   C prev[2];
   *   C next[2];
   *   int value;
   * };
   * ...
   * DList&lt;C, 0&gt; list1;
   * DList&lt;C, 1&gt; list2;</pre>
   * That way the objects of the same class can be in two separate lists at once.
   * <code>prev[0]</code> and <code>next[0]</code> point to previous and next element respectively
   * in <code>list1</code> and
   * <code>prev[1]</code> and <code>next[1]</code> point to previous and next element respectively
   * in <code>list2</code>.
   *
   * <code>prev[INDEX]</code> and <code>next[INDEX]</code> pointers are not cleared when element is
   * removed from the list, they may still point to elements in the list or to invalid locations!
   *
   * <code>DList</code> class doesn't take care of memory management except for the
   * <code>free()</code> method.
   *
   * In general all operations are O(1) except <code>contains()</code>, <code>length()</code> and
   * <code>free()</code> are O(n).
   */
  template <class Type, int INDEX>
  class DList
  {
    private:

      // First element in list.
      Type *firstElem;
      // Last element in list.
      Type *lastElem;

      // No copying.
      DList( const DList& );

    public:

      /**
       * DList iterator.
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
					 * Returns true if iterator is on specified element.
					 * @param e
					 * @return
					 */
					bool operator == ( const Type *e )
					{
						return elem == e;
					}

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
          void operator ++ ( int )
          {
            assert( elem != null );

            elem = elem->next[INDEX];
          }

          /**
           * @return pointer to current element in the list
           */
          Type *get()
          {
            return elem;
          }

          /**
           * @return constant pointer to current element in the list
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
       * @return pointer to first element in the list
       */
      Type *first()
      {
        return firstElem;
      }

      /**
       * @return constant pointer to first element in the list
       */
      const Type *first() const
      {
        return firstElem;
      }

      /**
       * @return pointer to last element in the list
       */
      Type *last()
      {
        return lastElem;
      }

      /**
       * @return constant pointer to last element in the list
       */
      const Type *last() const
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
       * Pop last element from the list.
       * @param e pointer to the last element
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
          Type *next = p->next[INDEX];

          next->prev[INDEX] = e;
          e->next[INDEX] = next;
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
          Type *prev = p->prev[INDEX];

          prev->next[INDEX] = e;
          e->prev[INDEX] = prev;
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
      void clear()
      {
        firstElem = null;
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
