/*
 *  Nirvana.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Nirvana.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Nirvana_h_
#define _Nirvana_h_

#include "Soul.h"
#include "Mind.h"

#include "Matrix.h"

#include "M_Walker.h"

namespace Dark
{

  class Nirvana
  {
    protected:

      static const int SOULS_MAX = 32;

      Soul souls[SOULS_MAX];
      DList<Mind, 0> minds;

      void think();
      void synchronize();
      void run();

      static int runThread( void *data );

    public:

      volatile bool isAlive;
      volatile bool requestSuspend;
      SDL_semaphore *semaphore;
      SDL_Thread    *thread;

      void add( Mind *mind );

      void load();
      void start();
      void stop();
      void free();
  };

  extern Nirvana nirvana;

}

#endif // _Nirvana_h_
