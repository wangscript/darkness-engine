/*
 *  Client.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_h_
#define _Client_h_

namespace Dark
{

  struct Settings
  {
    float mouseXSens;
    float mouseYSens;

    float keyXSens;
    float keyYSens;

    float moveStep;
    float runStep;
  };

  struct Input
  {
    uchar *currKeys;
    uchar keys[SDLK_LAST];

    struct Mouse
    {
      int  x;
      int  y;
      char b;
    }
    mouse;
  };

  class Client
  {
    protected:

      Settings settings;

    public:

      void init();
      void start();

      bool update( int time );

      void stop();
      void free();
  };

  extern Input input;
  extern Client client;

}

#endif // _Client_h_
