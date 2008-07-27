/*
 *  Main.cpp
 *
 *  Game initialization and main loop
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: main.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "Main.h"

#include "Client.h"
#include "SoundManager.h"
#include "Graphics_Render.h"

#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <SDL/SDL.h>

namespace Dark
{

  Main main;

  void Main::defaultConfig()
  {
    const SDL_VideoInfo *screen = SDL_GetVideoInfo();

    config.add( "data",                               "/usr/share/dark/data" );
    config.add( "tick",                               "20" );

    config.add( "screen.width",                       String( screen->current_w ).cstr() );
    config.add( "screen.height",                      String( screen->current_h ).cstr() );
    config.add( "screen.bpp",                         String( screen->vfmt->BitsPerPixel ).cstr() );
    config.add( "screen.vsync",                       "1" );
    config.add( "screen.full",                        "0" );

    config.add( "sound.volume.effects",               "1.0" );
    config.add( "sound.volume.music",                 "1.0" );

    // SDL_mixer
#ifdef __WIN32__
    config.add( "sound.sdl.device",                   "waveout" );
#else
    config.add( "sound.sdl.device",                   "alsa" );
#endif
    config.add( "sound.sdl.frequency",                "44100" );
    config.add( "sound.sdl.channels",                 "2" );
    config.add( "sound.sdl.chunkSize",                "512" );

    config.add( "input.mouse.xSens",                  "0.2" );
    config.add( "input.mouse.ySens",                  "0.2" );
    config.add( "input.keys.xSens",                   "0.2" );
    config.add( "input.keys.ySens",                   "0.2" );

    config.add( "render.perspective.angle",           "80.0" );
    config.add( "render.perspective.aspect",          "0.0" );
    config.add( "render.perspective.min",             "0.1" );
    config.add( "render.perspective.max",             "300.0" );

    config.add( "render.camera.smoothCoef",           "0.3" );

    config.add( "render.particleRadius",              "0.5" );
    config.add( "render.drawAABBs",                   "0" );
    config.add( "render.showAim",                     "0" );
    config.add( "render.blendHeaven",                 "1" );
  }

  void Main::shutdown()
  {
    if( initFlags & INIT_CLIENT_START ) {
      logFile.println( "Stopping Game {" );
      logFile.indent();
      client.stop();
      logFile.unindent();
      logFile.println( "}" );
    }
    if( initFlags & INIT_RENDER_INIT ) {
      logFile.println( "Shutting down Graphics {" );
      logFile.indent();
      Graphics::render.free();
      logFile.unindent();
      logFile.println( "}" );
    }
    if( initFlags & INIT_SOUND ) {
      logFile.println( "Shutting down Sound {" );
      logFile.indent();
      soundManager.free();
      logFile.unindent();
      logFile.println( "}" );
    }
    if( initFlags & INIT_CLIENT_INIT ) {
      logFile.println( "Shutting down Game {" );
      logFile.indent();
      client.free();
      logFile.unindent();
      logFile.println( "}" );
    }
    if( initFlags & INIT_SDL ) {
      logFile.print( "Shutting down SDL ..." );
      SDL_Quit();
      logFile.printRaw( " OK" );
    }
    logFile.printlnETD( "%s finished on", DARK_APP_NAME );
    exit( 0 );
  }

  void Main::main()
  {
    Math::init();

    const char *homeVar = getenv( "HOME" );
    String home( homeVar == null ? "./" DARK_RC_DIR : homeVar + String( "/" DARK_RC_DIR ) );

    struct stat homeDirStat;
    if( stat( home.cstr(), &homeDirStat ) ) {
      printf( "No resource dir found, creating '%s' ...", home.cstr() );

      if( mkdir( home.cstr(), S_IRUSR | S_IWUSR | S_IXUSR ) ) {
        printf( " Failed\n" );
        shutdown();
      }
      printf( " OK\n" );
    }

#ifdef DARK_LOG_FILE
    String logPath = home + DARK_LOG_FILE;

    if( !logFile.init( logPath, true, "  " ) ) {
      printf( "Can't create/open log file '%s' for writing\n", logPath.cstr() );
      shutdown();
    }
    logFile.println( "Log file '%s'", logPath.cstr() );
    printf( "Log file '%s'\n", logPath.cstr() );
#else
    logFile.init( null, true, "  " );
    logFile.println( "Log stream stdout ... OK" );
#endif

    logFile.printlnETD( "%s started on", DARK_APP_NAME );

    logFile.print( "Initializing SDL ..." );
    if( SDL_Init( SDL_INIT_VIDEO ) ) {
      logFile.printRaw( " Failed\n" );
      shutdown();
    }
    input.currKeys = SDL_GetKeyState( null );
    logFile.printRaw( " OK\n" );

    initFlags |= INIT_SDL;

    logFile.print( "Loading default config ..." );
    defaultConfig();
    logFile.printRaw( " OK\n" );

    String configPath = home + DARK_CONFIG_FILE;

    if( !config.load( configPath ) ) {
      logFile.println( "Config not found, creating default {", configPath.cstr() );
      logFile.indent();

      printf( "Config not found, creating default '%s' ...", configPath.cstr() );

      if( !config.save( configPath ) ) {
        printf( " Failed\n" );
        shutdown();
      }
      printf( " OK\n" );

      logFile.unindent();
      logFile.println( "}" );
    }

    String data = config["data"];

    logFile.print( "Going to working directory '%s' ...", (const char*) data );

    if( chdir( data ) != 0 ) {
      logFile.printRaw(" Failed\n");
      shutdown();
    }
    else {
      logFile.printRaw(" OK\n");
    }

    int screenX    = atoi( config["screen.width"] );
    int screenY    = atoi( config["screen.height"] );
    int screenBpp  = atoi( config["screen.bpp"] );
    int screenFull = config["screen.full"] == "1" ? SDL_FULLSCREEN : 0;

    logFile.print( "Setting OpenGL surface %dx%d %dbpp %s ...",
                   screenX, screenY, screenBpp, screenFull ? "fullscreen" : "windowed" );

    if( config["screen.vsync"] == "1" ) {
      putenv( (char*) "__GL_SYNC_TO_VBLANK=1" );
    }
    SDL_WM_SetCaption( DARK_WM_TITLE, null );
    SDL_ShowCursor( false );

    if( SDL_SetVideoMode( screenX, screenY, screenBpp, SDL_OPENGL | screenFull ) == null ) {
      logFile.printRaw( " Failed\n" );
      shutdown();
    }
    logFile.printRaw( " OK\n" );
    initFlags |= INIT_SDL_VIDEO;

    logFile.println( "Initializing Graphics {" );
    logFile.indent();
    Graphics::render.init();
    logFile.unindent();
    logFile.println( "}" );

    initFlags |= INIT_RENDER_INIT;

    logFile.println( "Initializing Sound {" );
    logFile.indent();

    if( !soundManager.init() ) {
      shutdown();
    }
//     soundManager.loadMusic( "music/music.ogg" );

    logFile.unindent();
    logFile.println( "}" );
    initFlags |= INIT_SOUND;

    logFile.println( "Initializing Game {" );
    logFile.indent();
    client.init();
    logFile.unindent();
    logFile.println( "}" );
    initFlags |= INIT_CLIENT_INIT;

    logFile.println( "Loading Graphics {" );
    logFile.indent();
    Graphics::render.load();
    logFile.unindent();
    logFile.println( "}" );
    initFlags |= INIT_RENDER_LOAD;

    logFile.println( "Starting Game {" );
    logFile.indent();
    client.start();
    logFile.unindent();
    logFile.println( "}" );
    initFlags |= INIT_CLIENT_START;

    logFile.println( "MAIN LOOP {" );
    logFile.indent();

    SDL_Event event;

    bool isAlive = true;
    int  nFrames = 0;

    Uint32 tick     = atoi( config["tick"] );
    Uint32 time;
    Uint32 timeZero = SDL_GetTicks();
    Uint32 timeLast = timeZero;

    // THE MAGNIFICANT MAIN LOOP
    do {
      // read input & events
      aCopy( input.keys, input.currKeys, SDLK_LAST );
      input.mouse.b = SDL_GetRelativeMouseState( &input.mouse.x, &input.mouse.y );

      while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
          case SDL_KEYDOWN: {
            input.keys[event.key.keysym.sym] |= SDL_PRESSED;
            break;
          }
          case SDL_MOUSEBUTTONDOWN: {
            input.mouse.b |= event.button.button;
            printf( "%d\n", event.button.button );
            break;
          }
          case SDL_QUIT: {
            isAlive = false;
            break;
          }
        }
      }
      // update world
      isAlive &= client.update( tick );
      soundManager.update();

      // render graphics, if we have enough time left
      time = SDL_GetTicks() - timeLast;

      if( time < tick ) {
        // render
        Graphics::render.draw();
        nFrames++;

        // if there's still some time left, waste it
        time = SDL_GetTicks() - timeLast;

        if( time < tick ) {
          SDL_Delay( max( tick - time, 1u ) );
        }
      }
      else if( time > 10 * tick ) {
        timeLast += time - tick;
      }
      timeLast += tick;
    }
    while( isAlive );

    logFile.unindent();
    logFile.println( "}" );

    logFile.println( "Average framerate: %g",
                     (float) nFrames / (float) ( timeLast - timeZero ) * 1000.0 );
    shutdown();
  }

}

int main( int argc, char *argv[] )
{
  // shut up. compiler!
  argc = (int) argv;

  Dark::main.main();
  return 0;
}
