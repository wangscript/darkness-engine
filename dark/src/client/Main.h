/*
 *  Main.h
 *
 *  Game initialization and main loop
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#define DARK_APP_NAME            "Darkness"
#define DARK_WM_TITLE            DARK_APP_NAME
#define DARK_RC_DIR              ".dark"
#define DARK_LOG_FILE            "client.log"
#define DARK_CONFIG_FILE         "client.xml"

namespace oz
{
namespace Client
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
}

int main( int argc, char *argv[] );
