/*
 *  M_Walker.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "Mind.h"

namespace oz
{

  class M_Walker : public Mind
  {
    protected:

      void onUpdate();

    public:

      M_Walker( Bot *body );
  };

}
