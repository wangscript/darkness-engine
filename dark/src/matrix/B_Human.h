/*
 *  B_Human.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _B_Human_h_
#define _B_Human_h_

#include "Bot.h"
#include "B_Spirit.h"

namespace Dark
{

  class B_Human : public Bot
  {
    protected:

      static const char *NAME;

      static const Vec3  CAM_POS;
      static const Vec3  CAM_POS_CROUCH;
      static const Vec3  DIM;
      static const Vec3  DIM_CROUCH;

      static const float BOB_INC;
      static const float BOB_AMPLITUDE;

      static const float WALK_VELOCITY;
      static const float RUN_VELOCITY;
      static const float JUMP_VELOCITY;

      static const float CROUCH_VELOCITY;
      static const float AIR_CONTROL;
      static const float GRAB_DIST;

      static const float STEP_INC;
      static const float STEP_MAX;

      void onUpdate();
      void onHit( const Hit *hit );
      void onDestroy();

    public:

      explicit B_Human( const Vec3 &p, float h = 0.0, float v = 0.0, Mind *mind = null );
  };

}

#endif // _B_Human_h_