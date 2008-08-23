/*
 *  Mind.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
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
