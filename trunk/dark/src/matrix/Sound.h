/*
 *  Sound.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

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
