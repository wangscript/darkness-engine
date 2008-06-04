/*
 *  Item.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Item.h 11 2007-08-31 12:03:10Z davorin $
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
