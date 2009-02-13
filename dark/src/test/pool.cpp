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

using namespace Dark;

class A : public PoolAlloc<A>
{
  public:

    int value;
};

int main()
{
  Pool<A> pool( 100 );
  A::setPool( &pool );

  A *a = new A();
  a->value = 10;
  delete a;

  printf( "%d\n", a->value );

  return 0;
}
