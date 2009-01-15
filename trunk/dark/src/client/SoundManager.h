/*
 *  SoundManager.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "matrix/World.h"
#include "matrix/Sound.h"

#ifdef WIN32
#  include <al.h>
#  include <alc.h>
#  include <AL/alut.h>
#  include <vorbis/vorbisfile.h>
#else
#  include <AL/al.h>
#  include <AL/alc.h>
#  include <AL/alut.h>
#  include <vorbis/vorbisfile.h>
#endif

namespace Dark
{
namespace Client
{

  class SoundManager
  {
    protected:

      // only play sounds within 100 m range
      static const float DMAX;
      static const float DMAX_SQ;
      // release continous sound if not used for 60 s
      static const int RELEASE_COUNT = 3000;

      struct Source : Reuser<Source>
      {
        Source *prev[1];
        Source *next[1];

        ALuint source;
      };

      struct ContSource : Reuser<ContSource>
      {
        enum State
        {
          NOT_UPDATED,
          UPDATED
        };

        State  state;
        ALuint source;
      };

      // size of hashtable for continous sources
      static const int HASHTABLE_SIZE = 256;
      static const int MUSIC_BUFFER_SIZE = 64 * 1024;
      // clear stopped sources each second
      static const int CLEAR_INTERVAL = 1000;

      static const int MAX_BUFFERS = SND_MAX;

      /*
       * Sound effects
       */
      ALCdevice  *device;
      ALCcontext *context;

      DList<Source, 0>                      sources;
      HashIndex<ContSource, HASHTABLE_SIZE> contSources;

      int          clearCount;

      bool         load( int sample, const char *file );
      void         playSector( int sectorX, int sectorY );

      /*
       * Music
       */
      OggVorbis_File oggStream;
      vorbis_info    *vorbisInfo;

      bool           isMusicPlaying;
      bool           isMusicLoaded;

      ALuint         musicBuffers[2];
      ALuint         musicSource;
      ALenum         musicFormat;

      void updateMusic();
      void freeMusic();

    public:

      bool init();
      void free();

      bool loadMusic( const char *file );
      void update();

      void setVolume( float volume );
      void setMusicVolume( float volume );

  };

  extern SoundManager soundManager;

}
}
