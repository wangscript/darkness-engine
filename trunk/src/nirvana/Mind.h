/*
 *  Mind.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Mind.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Mind_h_
#define _Mind_h_

#include "Bot.h"

namespace Dark
{

  class Mind
  {
    protected:

      virtual void onUpdate();

    public:

      Mind *prev[1];
      Mind *next[1];

      bool isUpdated;
      Bot  *body;

      Mind() : isUpdated( true )
      {}

      void update()
      {
        isUpdated = true;
        onUpdate();
      }
  };

}

#endif // _Mind_h_
