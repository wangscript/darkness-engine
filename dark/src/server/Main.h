/*
 *  Main.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Main_h_
#define _Main_h_

#define DARK_APP_NAME            "Darkness server"
#define DARK_RC_DIR              ".dark/"
#define DARK_LOG_FILE            "server.log"
#define DARK_CONFIG_FILE         "server.conf"

namespace Dark
{
namespace Server
{

  class Main
  {
    protected:

      static const int INIT_SDL = 0x01;

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

#endif // _Main_h_
