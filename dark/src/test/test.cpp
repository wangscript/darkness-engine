/*
 *  test.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include <typeinfo>

#include "matrix/Water.h"

using namespace Dark;

int main( int, char *[] )
{
  printf( "%s\n", typeid( Dark::Water ) );

  return 0;
}
