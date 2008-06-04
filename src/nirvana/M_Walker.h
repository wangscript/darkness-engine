/*
 *  M_Walker.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _M_Walker_h_
#define _M_Walker_h_

#include "Mind.h"

namespace Dark
{

  class M_Walker : public Mind
  {
    protected:

      void onUpdate();

    public:

      M_Walker( Bot *body );
  };

}

#endif // _M_Walker_h_
