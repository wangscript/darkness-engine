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

using namespace Dark;

int main( int, char *[] )
{
  int *a = new int[2];
  delete &a[0];

  return 0;
}
