/*
 *  ObjectFactory.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "Object.h"

namespace Dark
{

  class ObjectFactory
  {
    protected:

      ObjectFactory();
      ObjectFactory( const ObjectFactory &objectFactory );

      static ObjectFactory objectFactory;



    public:

      static Object *create( const char *className );

  };

}
