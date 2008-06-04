/*
 *  List.h
 *
 *  Linked list
 *  The Type should provide the "next[INDEX]" pointer
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: List.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Dark_List_h_
#define _Dark_List_h_

namespace Dark
{

  template <class Type, int INDEX>
  class List
  {
    protected:

      Type *firstElem;

      List( const List& );

    public:

      class Iterator
      {
        protected:

          Type *elem;

        public:

          explicit Iterator( List &l ) : elem( l.firstElem )
          {}

          bool isPassed() const
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

      List() : firstElem( null )
      {}

      explicit List( const Type *e ) : firstElem( e )
      {
        e->next[INDEX] = null;
      }

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

      bool isEmpty() const
      {
        return firstElem == null;
      }

      bool contains( const Type *e ) const
      {
        assert( e != null );

        Type *p = firstElem;

        while( p != null && p != e ) {
          p = p->next[INDEX];
        }
        return p == e;
      }

      Type *first() const
      {
        return firstElem;
      }

      // add to the beginning
      void operator << ( Type *e )
      {
        pushFirst( e );
      }

      // add to the beginning
      void add( Type *e )
      {
        pushFirst( e );
      }

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
