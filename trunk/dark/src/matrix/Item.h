/*
 *  Item.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Item_h_
#define _Item_h_

#include "DynObject.h"

namespace Dark
{

  class Item : public DynObject
  {
    protected:

      virtual void onConsume() = 0;

    public:

  };

}

#endif // _Item_h_
