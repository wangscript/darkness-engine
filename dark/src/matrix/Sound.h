/*
 *  Sound.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Sound_h_
#define _Sound_h_

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
