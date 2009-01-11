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

        Elem( uint key_, Elem *next_ ) :
            key( key_ ), next( next_ )
        {}
      };

      Elem *data[SIZE];
      // we cache found element since we often want its value after a search
      Elem *cached;

      /**
       * @param chainA
       * @param chainB
       * @return true if chains are equal length and all elements are equal
       */
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

      /**
       * Allocate space and make a copy of a given chain.
       * @param chain
       * @return pointer to first element of newly allocated chain
       */
      Elem *copyChain( const Elem *chain ) const
      {
        if( chain != null ) {
          return new Elem( chain->key, chain->value, copyChain( chain->next ) );
        }
        else {
          return null;
        }
      }

      /**
       * Delete all elements in given chain.
       * @param chain
       */
      void freeChain( const Elem *chain ) const
      {
        if( chain->next != null ) {
          freeChain( chain->next );
        }
        delete chain;
      }

      /**
       * Delete all elements and their values in given chain.
       * @param chain
       */
      void freeChainAndValues( const Elem *chain ) const
      {
        if( chain->next != null ) {
          freeChain( chain->next );
        }
        delete chain->value;
        delete chain;
      }

    public:

      /**
       * HashIndex iterator.
       */
      class Iterator : public Dark::Iterator<Elem>
      {
        private:

          typedef Dark::Iterator<Elem> IT;

          Elem **data;
          int  index;

          void operator -- ( int );

        public:

          /**
           * Make iterator for given HastIndex. After creation it points to first element.
           * @param t
           */
          explicit Iterator( HashIndex &t ) : IT( t.data[0] ), data( t.data ), index( 0 )
          {
            while( IT::elem == null && index < SIZE - 1 ) {
              index++;
              IT::elem = data[index];
            }
          }

          /**
           * When iterator advances beyond last element, it becomes passed. It points to an invalid
           * location.
           * @return true if iterator is passed
           */
          bool isPassed()
          {
            return IT::elem == null;
          }

          /**
           * Advance to the next element.
           * @param
           */
          void operator ++ ( int )
          {
            assert( IT::elem != null );

            if( IT::elem->next != null ) {
              IT::elem = IT::elem->next;
            }
            else if( index < SIZE - 1 ) {
              do {
                index++;
                IT::elem = data[index];
              }
              while( IT::elem == null && index < SIZE - 1 );
            }
            else {
              IT::elem = null;
            }
          }

          /**
           * @return current element's key
           */
          uint key() const
          {
            return IT::elem->key;
          }

          /**
           * @return pointer to current element's value
           */
          Type *value()
          {
            return &IT::elem->value;
          }

          /**
           * @return constant pointer to current element's value
           */
          const Type *value() const
          {
            return value();
          }

          /**
           * @return reference to current element's value
           */
          Type &operator * ()
          {
            return IT::elem->value;
          }

          /**
           * @return constant reference to current element's value
           */
          const Type &operator * () const
          {
            return IT::elem->value;
          }

      };

      /**
       * Constructor.
       */
      HashIndex()
      {
        for( int i = 0; i < SIZE; i++ ) {
          data[i] = null;
        }
      }

      /**
       * Copy constructor.
       * @param t
       */
      HashIndex( const HashIndex &t )
      {
        for( int i = 0; i < SIZE; i++ ) {
          data[i] = copyChain( t.data[i] );
        }
      }

      /**
       * Destructor.
       */
      ~HashIndex()
      {
        clear();
      }

      /**
       * Copy operator.
       * @param t
       * @return
       */
      HashIndex &operator = ( const HashIndex &t )
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            delete data[i];
          }
          data[i] = copyChain( t.data[i] );
        }
      }

      /**
       * Equality operator.
       * @param t
       * @return
       */
      bool operator == ( const HashIndex &t ) const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( !qEqualChain( data[i], t.data[i] ) ) {
            return false;
          }
        }
        return true;
      }

      /**
       * Inequality operator.
       * @param t
       * @return
       */
      bool operator != ( const HashIndex &t ) const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( !qEqualChain( data[i], t.data[i] ) ) {
            return true;
          }
        }
        return false;
      }

      /**
       * @return number of elements
       */
      int length() const
      {
        return SIZE;
      }

      /**
       * @return capacity
       */
      int capacity() const
      {
        return SIZE;
      }

      /**
       * @return true if HashIndex has no elements
       */
      bool isEmpty() const
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            return false;
          }
        }
        return true;
      }

      /**
       * @return cached element's key
       */
      uint &cachedKey() const
      {
        return cached->key;
      }

      /**
       * @return cached element's value
       */
      Type &cachedValue() const
      {
        return cached->value;
      }

      /**
       * Find element with given value.
       * This function caches the found element.
       * @param key
       * @return true if found
       */
      bool contains( uint key )
      {
        int  i = key % SIZE;
        Elem *p = data[i];

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

      /**
       * If given key exists, return reference to it's value, otherwise create a new element with
       * the given key and return reference to it's UNINITIALIZED value.
       * This function caches the found element.
       * @param key
       * @return reference to value associated to the given key
       */
      Type &operator [] ( uint key )
      {
        if( !contains( key ) ) {
          int i = key % SIZE;
          Elem *elem = new Elem( key, data[i] );

          data[i] = elem;
          cached = elem;
        }
        return cached->value;
      }

      /**
       * Add new element. The key must not yet exist in this HashIndex.
       * @param key
       * @param value
       */
      void add( uint key, const Type &value )
      {
        assert( !contains( key ) );

        int i = key % SIZE;
        Elem *elem = new Elem( key, value, data[i] );

        data[i] = elem;
        cached = elem;
      }

      /**
       * Remove element with given key.
       * @param key
       */
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

      /**
       * Remove all elements.
       */
      void clear()
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            freeChain( data[i] );
            data[i] = null;
          }
        }
      }

      /**
       * Remove all elements and delete their values.
       */
      void free()
      {
        for( int i = 0; i < SIZE; i++ ) {
          if( data[i] != null ) {
            freeChainAndValues( data[i] );
            data[i] = null;
          }
        }
      }

      /**
       * Deallocate memory from Reuser.
       */
      static void deallocate()
      {
        Elem::deallocate();
      }

  };

}