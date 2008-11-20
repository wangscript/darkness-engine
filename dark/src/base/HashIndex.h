/*
 *  HashIndex.h
 *
 *  Chaining hashtable implementation with uint key type
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace Dark
{

  template <class Type, int SIZE>
  class HashIndex
  {
    private:

      struct Elem : Reuser<HashIndex>
      {
        uint  key;
        Type  value;
        Elem  *next;

        Elem( uint key_, const Type &value_, Elem *next_ ) :
            key( key_ ), value( value_ ), next( next_ )
        {}
      };

      Elem *data[SIZE];
      Elem *cached;

      bool areChainsEqual( const Elem *chainA, const Elem *chainB ) const
      {
        if( chainA != null && chainB != null ) {
          return
              chainA->key == chainB->key &&
              chainA->value == chainB->value &&
              areChainsEqual( chainA->next, chainB->next );
        }
        else {
          // at least one is null, so (chainA == chainB) <=> (chainA == null && chainB == null)
          return chainA == chainB;
        }
      }

      Elem *copyChain( const Elem *chain ) const
      {
        if( chain != null ) {
          return new Elem( chain->key, chain->value, copyChain( chain->next ) );
        }
        else {
          return null;
        }
      }

      void freeChain( const Elem *chain ) const
      {
        if( chain->next != null ) {
          freeChain( chain->next );
        }
        delete chain;
      }

    public:

      class Iterator
      {
        protected:

          Elem **data;
          Elem *elem;
          int  index;

        public:

          explicit Iterator( HashIndex &t ) : data( t.data ), elem( data[0] ), index( 0 )
          {
            while( elem == null && index < SIZE - 1 ) {
              index++;
              elem = data[index];
            }
          }

          bool isPassed() const
          {
            return elem == null;
          }

          uint key() const
          {
            return elem->key;
          }

          Type *value() const
          {
            return &elem->value;
          }

          Type *get() const
          {
            return value();
          }

          Type &operator * () const
          {
            return elem->value;
          }

          void next()
          {
            assert( elem != null );

            if( elem->next != null ) {
              elem = elem->next;
            }
            else if( index < SIZE - 1 ) {
              do {
                index++;
                elem = data[index];
              }
              while( elem == null && index < SIZE - 1 );
            }
            else {
              elem = null;
            }
          }

      };

      static const int CAPACITY = SIZE;

      HashIndex()
      {
        for( int i = 0; i < SIZE; i++ ) {
          data[i] = null;
        }
      }

      HashIndex( const HashIndex &t )
      {
        for( int i = 0; i < SIZE; i++ ) {
          data[i] = copyChain( t.data[i] );
        }
      }

      ~HashIndex()
      {
        free();
      }

      HashIndex &operator = ( const HashIndex &t )
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            delete data[i];
          }
          data[i] = copyChain( t.data[i] );
        }
      }

      bool operator == ( const HashIndex &t ) const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( !qEqualChain( data[i], t.data[i] ) ) {
            return false;
          }
        }
        return true;
      }

      bool operator != ( const HashIndex &t ) const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( !qEqualChain( data[i], t.data[i] ) ) {
            return true;
          }
        }
        return false;
      }

      int length() const
      {
        return SIZE;
      }

      // caches searched element if found
      bool contains( uint key )
      {
        int   i = key % SIZE;
        Elem  *p = data[i];

        while( p != null ) {
          if( p->key == key ) {
            cached = p;
            return true;
          }
          else {
            p = p->next;
          }
        }
        return false;
      }

      bool isEmpty() const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            return false;
          }
        }
        return true;
      }

      Type &operator [] ( uint key )
      {
        int   i = key % SIZE;
        Elem  *p = data[i];

        while( p != null ) {
          if( p->key == key ) {
            cached = p;
            break;
          }
          else {
            p = p->next;
          }
        }
        assert( p != null );

        return cached->value;
      }

      Type get( uint key )
      {
        return operator [] ( key );
      }

      uint &cachedKey() const
      {
        return cached->key;
      }

      Type &cachedValue() const
      {
        return cached->value;
      }

      void set( uint key, const Type &value )
      {
        int   i = key % SIZE;
        Elem  *p = data[i];

        while( p != null ) {
          if( p->key == key ) {
            p->value = value;
            return;
          }
          else {
            p = p->next;
          }
        }
      }

      void add( uint key, const Type &value )
      {
        assert( !contains( key ) );

        int i = key % SIZE;
        Elem *elem = new Elem( key, value, data[i] );

        data[i] = elem;
        cached = elem;
      }

      void remove( uint key )
      {
        int i = key % SIZE;
        Elem *p = data[i];
        Elem **prev = &data[i];

        while( p != null ) {
          if( p->key == key ) {
            *prev = p->next;
            delete p;
            return;
          }
          else {
            prev = &p->next;
            p = p->next;
          }
        }
      }

      void free()
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            freeChain( data[i] );
            data[i] = null;
          }
        }
      }

      void clear()
      {
        free();
      }

      static void deallocate()
      {
        Elem::deallocate();
      }

  };

}
