/*
 *  Bot.h
 *
 *  Bot class
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Bot.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Bot_h_
#define _Bot_h_

#include "DynObject.h"
#include "Weapon.h"

#define BOT_GRAB_DIST         1.0

namespace Dark
{

  class Mind;

  class Bot : public DynObject
  {
    public:

      static const int KEY_FORWARD     = 0x00000001;
      static const int KEY_BACKWARD    = 0x00000002;
      static const int KEY_LEFT        = 0x00000004;
      static const int KEY_RIGHT       = 0x00000008;
      static const int KEY_JUMP        = 0x00000010;
      static const int KEY_CROUCH      = 0x00000020;
      static const int KEY_RUN         = 0x00000040;
      static const int KEY_FIRE        = 0x00000080;
      static const int KEY_NOCLIP      = 0x00000100;
      static const int KEY_SUICIDE     = 0x00000200;
      static const int KEY_GESTURE0    = 0x00000400;
      static const int KEY_GESTURE1    = 0x00000800;
      static const int KEY_USE         = 0x00001000;
      static const int KEY_STEP        = 0x00002000;

      static const int GROUNDED_BIT    = 0x00000001;
      static const int RUNNING_BIT     = 0x00000002;
      static const int CROUCHING_BIT   = 0x00000004;
      static const int MOVING_BIT      = 0x00000008;
      static const int SHOOTING_BIT    = 0x00000010;
      static const int GESTURE0_BIT    = 0x00000020;
      static const int GESTURE1_BIT    = 0x00000040;
      static const int STEPPING_BIT    = 0x00000080;
      static const int DEATH_BIT       = 0x00000100;

      Mind    *mind;

      int     state;

      int     keys, oldKeys;

      float   h, v;
      float   bob;
      Vec3    camPos;

      float   deathTime;
      Weapon  *weapon;

      Vector<Object*> items;

      void commonUpdate( float *hvsc );

      virtual void onUpdate() = 0;
  };

}

#endif // _Bot_h_
