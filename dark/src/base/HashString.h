/*
 *  HashString.h
 *
 *  Chaining hashtable implementation with String key type
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_HashString_h_
#define _Dark_HashString_h_

namespace Dark
{

  template <class Type, int SIZE>
  class HashString
  {
    protected:

      struct Elem : Reuser<HashString>
      {
        String key;
        Type   value;
        Elem   *next;

        Elem( const String &key_, const Type &value_, Elem *next_ ) :
            key( key_ ), value( value_ ), next( next_ )
        {}
      };

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

      // Bernstein's hash function
      int hash( const String &s ) const
      {
        int hash = 5381;

        for( int i = 0; i < s.length(); i++ ) {
          hash = hash * 33 + s[i];
        }
        return abs( hash );
      }

      Elem *data[SIZE];
      Elem *cached;

    public:

      class Iterator
      {
        protected:

          Elem **data;
          Elem *elem;
          int  index;

        public:

          explicit Iterator( HashString &t ) : data( t.data ), elem( data[0] ), index( 0 )
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

          String *key() const
          {
            return &elem->key;
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

      HashString()
      {
        for( int i = 0; i < SIZE; i++ ) {
          data[i] = null;
        }
      }

      HashString( const HashString &t )
      {
        for( int i = 0; i < SIZE; i++ ) {
          data[i] = copyChain( t.data[i] );
        }
      }

      ~HashString()
      {
        free();
      }

      HashString &operator = ( const HashString &t )
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            delete data[i];
          }
          data[i] = copyChain( t.data[i] );
        }
      }

      bool operator == ( const HashString &t ) const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( !areChainsEqual( data[i], t.data[i] ) ) {
            return false;
          }
        }
        return true;
      }

      bool operator != ( const HashString &t ) const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( !areChainsEqual( data[i], t.data[i] ) ) {
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
      bool contains( const String &key )
      {
        int   i = hash( key ) % SIZE;
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

      Type &operator [] ( const String &key )
      {
        int   i = hash( key ) % SIZE;
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

      Type get( const String &key )
      {
        return operator [] ( key );
      }

      String &cachedKey() const
      {
        return cached->key;
      }

      Type &cachedValue() const
      {
        return cached->value;
      }

      void set( const String &key, const Type &value )
      {
        int   i = hash( key ) % SIZE;
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

      void add( const String &key, const Type &value )
      {
        assert( !contains( key ) );

        int i = hash( key ) % SIZE;

        data[i] = new Elem( key, value, data[i] );
      }

      void remove( const String &key )
      {
        int i = hash( key ) % SIZE;
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

#endif // _Dark_HashString_h_
