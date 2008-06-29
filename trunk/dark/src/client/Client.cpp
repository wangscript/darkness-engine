/*
 *  Client.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Game.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "base.h"

#include "Client.h"

#include "Timer.h"
#include "Bot.h"
#include "Matrix.h"
#include "Nirvana.h"

#include "Camera.h"

#include <stdio.h>

namespace Dark
{

  Input input;
  Client client;

  void Client::init()
  {
    logFile.println( "Setting game variables" );
    sscanf( config["input.mouse.xSens"], "%f", &settings.mouseXSens );
    sscanf( config["input.mouse.ySens"], "%f", &settings.mouseYSens );
    sscanf( config["input.keys.xSens"], "%f", &settings.keyXSens );
    sscanf( config["input.keys.ySens"], "%f", &settings.keyYSens );

    logFile.println( "Loading Matrix {" );
    logFile.indent();

    matrix.load();

    logFile.unindent();
    logFile.println( "}" );

    logFile.println( "Loading Nirvana {" );
    logFile.indent();

    nirvana.load();

    logFile.unindent();
    logFile.println( "}" );
  }

  void Client::start()
  {
    logFile.print( "Starting Nirvana thread ..." );
    nirvana.start();
    logFile.printRaw( " OK\n" );
  }

  bool Client::update( int time )
  {
    nirvana.requestSuspend = true;

    camera.player = (Bot*) world.objects[0];

    camera.player->h -= input.mouse.x * settings.mouseXSens;
    camera.player->v -= input.mouse.y * settings.mouseYSens;

    if( input.keys[SDLK_UP] ) {
      camera.player->v += settings.keyXSens * time;
    }
    if( input.keys[SDLK_DOWN] ) {
      camera.player->v -= settings.keyXSens * time;
    }
    if( input.keys[SDLK_RIGHT] ) {
      camera.player->h -= settings.keyYSens * time;
    }
    if( input.keys[SDLK_LEFT] ) {
      camera.player->h += settings.keyYSens * time;
    }

    if( input.keys[SDLK_w] ) {
      camera.player->keys |= Bot::KEY_FORWARD;
    }
    if( input.keys[SDLK_s] ) {
      camera.player->keys |= Bot::KEY_BACKWARD;
    }
    if( input.keys[SDLK_d] ) {
      camera.player->keys |= Bot::KEY_RIGHT;
    }
    if( input.keys[SDLK_a] ) {
      camera.player->keys |= Bot::KEY_LEFT;
    }

    if( input.keys[SDLK_SPACE] ) {
      camera.player->keys |= Bot::KEY_JUMP;
    }
    if( input.keys[SDLK_LCTRL] ) {
      camera.player->keys |= Bot::KEY_CROUCH;
    }
    if( input.keys[SDLK_LALT] ) {
      camera.player->keys |= Bot::KEY_RUN;
    }

    if( input.keys[SDLK_l] ) {
      camera.player->keys |= Bot::KEY_NOCLIP;
    }

    if( input.keys[SDLK_g] ) {
      camera.player->keys |= Bot::KEY_GESTURE0;
    }
    if( input.keys[SDLK_h] ) {
      camera.player->keys |= Bot::KEY_GESTURE1;
    }
    if( input.keys[SDLK_p] ) {
      camera.player->keys |= Bot::KEY_STEP;
    }

    if( ( input.mouse.b == SDL_BUTTON_LEFT ) ) {
      camera.player->keys |= Bot::KEY_FIRE;
    }
    if( input.keys[SDLK_f] || ( input.mouse.b == SDL_BUTTON_RIGHT ) ) {
      camera.player->keys |= Bot::KEY_USE;
    }

    SDL_SemWait( matrix.semaphore );

    timer.update( time );
    matrix.update();

    SDL_SemPost( nirvana.semaphore );

    camera.update();

    return !input.keys[SDLK_ESCAPE];
  }

  void Client::stop()
  {
    logFile.print( "Stopping Nirvana thread ..." );
    nirvana.stop();
    logFile.printRaw( " OK\n" );
  }

  void Client::free()
  {
    logFile.print( "Shutting down Nirvana ..." );
    logFile.indent();

    nirvana.free();

    logFile.unindent();
    logFile.printRaw( " OK\n" );

    logFile.print( "Shutting down Matrix ..." );
    logFile.indent();

    matrix.free();

    logFile.unindent();
    logFile.printRaw( " OK\n" );
  }

}
