/*
 *  test.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

template <class TypeA, class TypeB>
    inline void swap( TypeA &a, TypeB &b )
{
  TypeA temp = a;

  a = b;
  b = temp;
}

template <class Type, int STACK_SIZE>
inline void aSort( Type *array, int count )
{
  Type *stack[STACK_SIZE];
  Type **sp = stack;
  Type *first = array;
  Type *last = array + count - 1;

  *( sp++ ) = first;
  *( sp++ ) = last;

  do {
    last = *( --sp );
    first = *( --sp );

    if( first < last ) {
      if( last - first > 1 ) {
        int pivotValue = *last;
        Type *top = first;
        Type *bottom = last - 1;

        do {
          while( top <= bottom && *top <= pivotValue ) {
            top++;
          }
          while( top < bottom && *bottom > pivotValue ) {
            bottom--;
          }
          if( top >= bottom ) {
            break;
          }
          swap( *top, *bottom );
        }
        while( true );

        swap( *top, *last );

        *( sp++ ) = first;
        *( sp++ ) = top - 1;
        *( sp++ ) = top + 1;
        *( sp++ ) = last;
      }
      else if( *first > *last ) {
        swap( *first, *last );
      }
    }
  }
  while( sp != stack );
}

template <class Type>
inline void arSort( Type *first, Type *last )
{
  if( first < last ) {
    if( last - first > 1 ) {
      int pivotValue = *last;
      Type *top = first;
      Type *bottom = last - 1;

      do {
        while( top <= bottom && *top <= pivotValue ) {
          top++;
        }
        while( top < bottom && *bottom > pivotValue ) {
          bottom--;
        }
        if( top >= bottom ) {
          break;
        }
        swap( *top, *bottom );
      }
      while( true );

      swap( *top, *last );

      arSort( first, top - 1 );
      arSort( top + 1, last );
    }
    else if( *first > *last ) {
      swap( *first, *last );
    }
  }
}

#define MAX 2000
#define TESTS 10000

int main( int, char *[] )
{
  int array[MAX];

  srand( 32 );

  long t0 = clock();
  for( int i = 0; i < TESTS; i++ ) {
    for( int j = 0; j < MAX; j++ ) {
      array[j] = rand() % 1000;
    }
    arSort( array, array + MAX - 1 );
    //aSort<int, 4*MAX>( array, MAX );
  }
  printf( "%d\n", (int)( clock() - t0 ) / 1000 );
//   for( int i = 0; i < MAX; i++ ) {
//     printf( "%d ", array[i] );
//   }
  return 0;
}
