/*
 *  DList.h
 *
 *  Double linked list
 *  The Type should provide the "next[INDEX]" and "prev[INDEX]" pointers
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_DList_h_
#define _Dark_DList_h_

namespace Dark
{

  template <class Type, int INDEX>
  class DList
  {
    protected:

      Type *firstElem;
      Type *lastElem;

      DList( const DList& );

    public:

      class Iterator
      {
        protected:

          Type *elem;

        public:

          explicit Iterator( const DList &l ) : elem( l.firstElem )
          {}

          bool isPassed()
          {
            return elem == null;
          }

          Type *get() const
          {
            return elem;
          }

          Type &operator * () const
          {
            return *elem;
          }

          void next()
          {
            assert( elem != null );

            elem = elem->next[INDEX];
          }

      };

      DList() : firstElem( null ), lastElem( null )
      {}

      explicit DList( const Type *e ) : firstElem( e ), lastElem( e )
      {}

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

      bool isEmpty() const
      {
        assert( ( firstElem == null ) == ( lastElem == null ) );

        return firstElem == null;
      }

      bool contains( const Type *e ) const
      {
        assert( e != null );

        const Type *p = firstElem;

        while( p != e && p != lastElem ) {
          p = p->next[INDEX];
        }
        return p == e;
      }

      Type *first() const
      {
        return firstElem;
      }

      Type *last() const
      {
        return lastElem;
      }

      // add to the end
      void operator << ( Type *e )
      {
        pushLast( e );
      }

      // add to the end
      void add( Type *e )
      {
        pushLast( e );
      }

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

      void operator >> ( Type *&e )
      {
        e = popFirst();
      }

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

  };

}

#endif // _Dark_DList_h_
