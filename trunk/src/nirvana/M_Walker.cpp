/*
 *  M_Walker.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "M_Walker.h"

namespace Dark
{

  M_Walker::M_Walker( Bot *body_ )
  {
    body = body_;
  }

  void M_Walker::onUpdate()
  {
    body->keys |= Bot::KEY_FORWARD;

    if( Math::rand() % 101 == 0 ) {
      body->h += ( Math::frand() * 120.0 ) - 60.0;
    }
  }

}
