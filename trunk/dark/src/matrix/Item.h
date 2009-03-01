/*
 *  Item.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "DynObject.h"

namespace oz
{

  class Item : public DynObject
  {
    protected:

      virtual void onConsume() = 0;

    public:

  };

}
