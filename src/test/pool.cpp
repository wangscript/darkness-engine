/*
 *  pool.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

using namespace oz;

struct A : PoolAlloc<A, 0>
{
  int value;
  A   *next[1];
};

int main()
{
  int max = 1000000;

  A *array[max];
  for( int i = 0; i < max; i++ ) {
    array[i] = new A();
    array[i]->value = 10;
  }
  printf( "pool length: %d\n", PoolAlloc<A, 0>::pool.length() );
  printf( "pool capacity: %d\n", PoolAlloc<A, 0>::pool.capacity() );

  for( int i = 0; i < max; i++ ) {
    delete array[i];
  }
  printf( "pool length: %d\n", PoolAlloc<A, 0>::pool.length() );
  printf( "pool capacity: %d\n", PoolAlloc<A, 0>::pool.capacity() );

  for( int i = 0; i < max; i++ ) {
    array[i] = new A();
    array[i]->value = 10;
  }
  printf( "pool length: %d\n", PoolAlloc<A, 0>::pool.length() );
  printf( "pool capacity: %d\n", PoolAlloc<A, 0>::pool.capacity() );

  for( int i = 0; i < max; i++ ) {
    delete array[i];
  }
  printf( "pool length: %d\n", PoolAlloc<A, 0>::pool.length() );
  printf( "pool capacity: %d\n", PoolAlloc<A, 0>::pool.capacity() );

  return 0;
}
