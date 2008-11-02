/*
 *  ObjectFactory.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _ObjectFactory_h_
#define _ObjectFactory_h_

#include "Object.h"

namespace Dark
{

  class ObjectFactory
  {
    private:

      ObjectFactory();
      ObjectFactory( const ObjectFactory &objectFactory );

      static ObjectFactory objectFactory;

    public:

      static Object *create( const char *className );

  };

}

#endif // _ObjectFactory_h_
