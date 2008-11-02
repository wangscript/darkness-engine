/*
 *  B_Spirit.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _B_Spirit_h_
#define _B_Spirit_h_

#include "Bot.h"

namespace Dark
{

  class B_Spirit : public Bot
  {
    protected:

      static const Vec3  CAM_POS;
      static const float BOB_INC;
      static const float BOB_AMPLITUDE;
      static const float WALK_VELOCITY;
      static const float RUN_VELOCITY;
      static const float GRAB_DIST;

      Vec3 origin;

      void onUpdate();

    public:

      static const char *NAME;
      static const int TYPE;

      explicit B_Spirit( const Vec3 &p, float h = 0.0f, float v = 0.0f, Mind *mind = null );

      void load( FILE *stream );
      void save( FILE *stream );

  };

}

#endif // _B_Spirit_h_
