/*
 *  Sound.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Sound.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Sound_h_
#define _Sound_h_

#include "base.h"

namespace Dark
{

  struct Sound /*: Reuser<Sound>*/
  {
    Sound *next[1];
    int   sample;

    explicit Sound( int sample_ ) : sample( sample_ )
    {}

  };

}

#endif // _Sound_h_
