/*
 *  Main.h
 *
 *  Game initialization and main loop
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: main.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Main_h_
#define _Main_h_

#include "base.h"

#define DARK_APP_NAME            "Darkness"
#define DARK_WM_TITLE            DARK_APP_NAME
#define DARK_RC_DIR              ".dark/"
#define DARK_LOG_FILE            "log"
#define DARK_CONFIG_FILE         "config.xml"

namespace Dark
{

  class Main
  {
    private:

      static const int INIT_SDL = 0x1;
      static const int INIT_SDLVIDEO = 0x2;
      static const int INIT_GL = 0x4;
      static const int INIT_SOUND = 0x8;
      static const int INIT_MATRIX = 0x10;
      static const int INIT_NIRVANA = 0x20;
      static const int INIT_RENDER = 0x40;

      int initFlags;

      void defaultConfig();
      void shutdown();

    public:

      int main( int argc, char *argv[] );
  };

  extern Main main;

}

int main( int argc, char *argv[] );

#endif // _Main_h_
