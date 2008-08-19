/*
 *  Main.h
 *
 *  Game initialization and main loop
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Main_h_
#define _Main_h_

#define DARK_APP_NAME            "Darkness"
#define DARK_WM_TITLE            DARK_APP_NAME
#define DARK_RC_DIR              ".dark/"
//#define DARK_LOG_FILE            "log"
#define DARK_CONFIG_FILE         "config.xml"

namespace Dark
{

  class Main
  {
    private:

      static const int INIT_SDL = 0x01;
      static const int INIT_SDL_VIDEO = 0x02;
      static const int INIT_RENDER_INIT = 0x04;
      static const int INIT_SOUND = 0x08;
      static const int INIT_CLIENT_INIT = 0x10;
      static const int INIT_RENDER_LOAD = 0x20;
      static const int INIT_CLIENT_START = 0x40;

      int initFlags;

      void defaultConfig();
      void shutdown();

    public:

      void main();
  };

  extern Main main;

}

int main( int argc, char *argv[] );

#endif // _Main_h_
