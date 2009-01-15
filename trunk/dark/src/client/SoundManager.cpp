/*
 *  SoundManager.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "SoundManager.h"

#include "Camera.h"

namespace Dark
{
namespace Client
{

  SoundManager soundManager;

  const float SoundManager::DMAX = 100.0f;
  const float SoundManager::DMAX_SQ = DMAX * DMAX;

#ifdef DARK_OPENAL

  /*
   * OpenAL implementation
   */

  bool SoundManager::init()
  {
    logFile.print( "Initializing OpenAL audio device ..." );

    alutInit( null, null );

    isMusicPlaying = false;

    if( alutGetError() != ALUT_ERROR_NO_ERROR ) {
      logFile.printRaw( " Failed\n" );
      return false;
    }
    else {
      logFile.printRaw( " OK\n" );
    }

    logFile.println( "OpenAL vendor: %s", alGetString( AL_VENDOR ) );
    logFile.println( "OpenAL version: %s", alGetString( AL_VERSION ) );
    logFile.println( "OpenAL renderer: %s", alGetString( AL_RENDERER ) );
    logFile.println( "OpenAL extensions: %s", alGetString( AL_EXTENSIONS ) );

    logFile.println( "FreeALUT version: %d.%d", alutGetMajorVersion(), alutGetMinorVersion() );
    logFile.println( "FreeALUT suppored formats: %s", alutGetMIMETypes( ALUT_LOADER_MEMORY ) );

    for( int i = 0; i < MAX_BUFFERS; i++ ) {
      if( !load( i, translator.sounds[i] ) ) {
        return false;
      }
    }

    alGenSources( 1, &musicSource );

    alSourcei( musicSource, AL_SOURCE_RELATIVE, AL_TRUE );
    alSourcefv( musicSource, AL_POSITION, Vec3::zero() );
    alSourcefv( musicSource, AL_DIRECTION, Vec3::zero() );

    float fVolume;
    float fMusicVolume;

    sscanf( config["sound.volume.effects"], "%f", &fVolume );
    sscanf( config["sound.volume.music"], "%f", &fMusicVolume );

    setVolume( fVolume );
    setMusicVolume( fMusicVolume );

    return true;
  }

  void SoundManager::free()
  {
    for( Source *src = sources.first(); src != null; src = src->next[0] ) {
      alSourceStop( src->source );
      alDeleteSources( 1, &src->source );
    }
    sources.free();

    for( HashIndex<ContSource, HASHTABLE_SIZE>::Iterator i( contSources );
         !i.isPassed();
         i++ )
    {
      ContSource &src = *i;

      alSourceStop( src.source );
      alDeleteSources( 1, &src.source );
    }
    contSources.clear();
    contSources.deallocate();

    alDeleteBuffers( MAX_BUFFERS, buffers );
    freeMusic();
    alutExit();
  }

  bool SoundManager::load( int sample, const char *file )
  {
    logFile.print( "Loading sound '%s' ...", file );

//     FILE *oggFile = fopen( file, "rb" );
//     OggVorbis_File oggStream;
//
//     if( oggFile == null ) {
//       logFile.printRaw( " Failed\n" );
//       return false;
//     }
//     if( ov_open( oggFile, &oggStream, null, 0 ) < 0 ) {
//       fclose( oggFile );
//       logFile.printRaw( " Failed\n" );
//       return false;
//     }
//
//     vorbis_info *vorbisInfo = ov_info( &oggStream, -1 );
//     ALenum format = ( vorbisInfo->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16 );
//     int size = oggStream.end - oggStream.offset;
//
//     logFile.println( "%d %d", size, vorbisInfo->rate );
//
//     char data[size];
//     int section;
//     ov_read( &oggStream, data, size, 0, 2, 1, &section );
//     ov_clear( &oggStream );
//
//     alBufferData( buffers[sample], format, data, size, vorbisInfo->rate );
//
//     logFile.printRaw( " OK\n" );
//     return true;

    buffers[sample] = alutCreateBufferFromFile( file );

    if( buffers[sample] == AL_NONE ) {
      logFile.printRaw( " Failed\n" );
      return false;
    }
    else {
      logFile.printRaw( " OK\n" );
      return true;
    }
  }

  void SoundManager::playSector( int sectorX, int sectorY )
  {
    Sector &sector = world.sectors[sectorX][sectorY];

    for( Object *obj = sector.objects.first(); obj != null; obj = obj->next[0] ) {
      if( ( !obj->sounds.isEmpty() || !obj->contSounds.isEmpty() ) &&
          ( camera.p - obj->p ).sqL() < DMAX_SQ )
      {
        // non-continous
        for( Sound *snd = obj->sounds.first(); snd != null; snd = snd->next[0] ) {
          Source *src = new Source();

          alGenSources( 1, &src->source );
          alSourcei( src->source, AL_BUFFER, buffers[ snd->sample ] );
          alSourcef( src->source, AL_REFERENCE_DISTANCE, 2.0f );

          // If the object moves since source starts playing and source stands still, it's usually
          // not noticable for short-time source. After all, sound source many times does't move
          // together with the object in many cases (e.g. the sound when an objects hits something).
          //
          // However, when the sound is generated by player (e.g. cries, talk) it is often annoying
          // if the sound source doesn't move with the player. That's why we position the sounds
          // generated by the player at the origin of the coordinate system relative to player.
          if( obj == camera.player ) {
            alSourcei( src->source, AL_SOURCE_RELATIVE, AL_TRUE );
            alSourcefv( src->source, AL_POSITION, Vec3::zero() );
          }
          else {
            alSourcefv( src->source, AL_POSITION, obj->p );
          }
          alSourcePlay( src->source );

          sources << src;
        }
        // continous
        for( Sound *snd = obj->contSounds.first(); snd != null; snd = snd->next[0] ) {
          if( contSources.contains( (uint) snd ) ) {
            ContSource &src = contSources.cachedValue();

            src.state = ContSource::UPDATED;

            alSourcefv( src.source, AL_POSITION, obj->p );
          }
          else {
            ContSource src;

            src.state = ContSource::UPDATED;

            alGenSources( 1, &src.source );
            alSourcei( src.source, AL_BUFFER, buffers[ snd->sample ] );
            alSourcefv( src.source, AL_POSITION, obj->p );
            alSourcei( src.source, AL_LOOPING, AL_TRUE );
            alSourcePlay( src.source );

            contSources.add( (uint) snd, src );
          }
        }
      }
    }
  }

  void SoundManager::update()
  {
    // add new sounds
    alListenerfv( AL_ORIENTATION, camera.at );
    alListenerfv( AL_POSITION, camera.p );

    world.getInters( camera.p, DMAX );

    for( int x = world.minSectX ; x <= world.maxSectX; x++ ) {
      for( int y = world.minSectY; y <= world.maxSectY; y++ ) {
        playSector( x, y );
      }
    }

    // remove continous sounds that are not played any more
    for( HashIndex<ContSource, HASHTABLE_SIZE>::Iterator i( contSources );
         !i.isPassed(); )
    {
      ContSource *src = i.value();
      uint key = i.key();

      // we should advance now, so that we don't remove the element the iterator is pointing at
      i++;

      if( src->state == ContSource::NOT_UPDATED ) {
        alSourceStop( src->source );
        alDeleteSources( 1, &src->source );
        contSources.remove( key );
      }
      else {
        src->state = ContSource::NOT_UPDATED;
      }
    }

    // remove stopped sources of non-continous sounds
    if( clearCount >= CLEAR_INTERVAL ) {
      Source *src = sources.first();

      while( src != null ) {
        Source *next = src->next[0];
        ALint value = AL_STOPPED;

        alGetSourcei( src->source, AL_SOURCE_STATE, &value );

        if( value != AL_PLAYING ) {
          alDeleteSources( 1, &src->source );

          sources.remove( src );
          delete src;
        }
        src = next;
      }
      clearCount -= CLEAR_INTERVAL;
    }
    clearCount += timer.frameMillis;

    updateMusic();
  }

  bool SoundManager::loadMusic( const char *file )
  {
    logFile.print( "Loading music '%s' ...", file );

    FILE *oggFile = fopen( file, "rb" );

    if( oggFile == null ) {
      logFile.printRaw( " Failed\n" );
      return false;
    }
    if( ov_open( oggFile, &oggStream, null, 0 ) < 0 ) {
      fclose( oggFile );
      logFile.printRaw( " Failed\n" );
      return false;
    }

    isMusicLoaded = true;

    vorbisInfo = ov_info( &oggStream, -1 );
    musicFormat = vorbisInfo->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    isMusicPlaying = true;

    alGenBuffers( 2, musicBuffers );
    alSourceQueueBuffers( musicSource, 2, musicBuffers );

    updateMusic();

    logFile.printRaw( " OK\n" );
    return true;
  }

  void SoundManager::freeMusic()
  {
    if( isMusicLoaded ) {
      alSourceStop( musicSource );
      alDeleteSources( 1, &musicSource );
      alDeleteBuffers( 2, musicBuffers );

      ov_clear( &oggStream );

      isMusicLoaded = false;
    }
  }

  void SoundManager::updateMusic()
  {
    if( !isMusicPlaying ) {
      return;
    }

    int processed;

    alGetSourcei( musicSource, AL_BUFFERS_PROCESSED, &processed );

    while( processed > 0 ) {
      ALuint buffer;

      alSourceUnqueueBuffers( musicSource, 1, &buffer );

      char data[MUSIC_BUFFER_SIZE];
      int  size = 0;

      while( size < MUSIC_BUFFER_SIZE ) {
        int section;
        int result = ov_read( &oggStream, &data[size], MUSIC_BUFFER_SIZE - size, 0, 2, 1, &section );

        if( result <= 0 ) {
          alSourceQueueBuffers( musicSource, 1, &buffer );

          isMusicPlaying = false;
          return;
        }
        size += result;
      }

      alBufferData( buffer, musicFormat, data, size, vorbisInfo->rate );
      alSourceQueueBuffers( musicSource, 1, &buffer );

      processed--;
    }

    ALint value;
    alGetSourcei( musicSource, AL_SOURCE_STATE, &value );

    if( value != AL_PLAYING ) {
      alSourcePlay( musicSource );
    }
  }

  void SoundManager::setVolume( float volume )
  {
    alListenerf( AL_GAIN, volume );
  }

  void SoundManager::setMusicVolume( float volume )
  {
    alSourcef( musicSource, AL_GAIN, volume );
  }

#else

  /*
   * SDL_mixer implementation
   */

  bool SoundManager::init()
  {
    logFile.println( "%d", MAX_BUFFERS );

    String device = config["sound.sdl.device"];
    char   buffer[32] = { 0 };

    isMusicPlaying = false;
    music = null;

    logFile.print( "Initializing SDL_mixer audio device '%s' ...", (const char*) device );
    SDL_AudioInit( (const char*) device );
    SDL_AudioDriverName( buffer, 32 );

    if( device != buffer ) {
      logFile.printRaw( " Failed\n" );
      return false;
    }
    else {
      logFile.printRaw( " OK\n" );
    }

    int freq = atoi( config["sound.sdl.frequency"] );
    int chunkSize = atoi( config["sound.sdl.chunkSize"] );
    int nChannels = atoi( config["sound.sdl.channels"] );

    logFile.println( "Opening mixer: %d channels, %d Hz, S16SYS format", nChannels, freq );
    Mix_OpenAudio( freq, AUDIO_S16SYS, nChannels, chunkSize );

    logFile.print( "Allocating channels %d ...", MAX_SOURCES );

    if( Mix_AllocateChannels( MAX_SOURCES ) != MAX_SOURCES ) {
      logFile.printRaw( " Failed" );
      return false;
    }
    else {
      logFile.printRaw( " OK\n" );
    }

    for( int i = 0; i < MAX_BUFFERS; i++ ) {
      if( !load( i, translator.sounds[i] ) ) {
        return false;
      }
    }

    float fVolume;
    float fMusicVolume;

    sscanf( config["sound.volume.effects"], "%f", &fVolume );
    sscanf( config["sound.volume.music"], "%f", &fMusicVolume );

    setVolume( fVolume );
    setMusicVolume( fMusicVolume );

    return true;
  }

  void SoundManager::free()
  {
    Mix_HaltGroup( -1 );

    for( int i = 0; i < MAX_BUFFERS; i++ ) {
      Mix_FreeChunk( chunks[i] );
    }
    ContChannel::deallocate();
    freeMusic();

    Mix_CloseAudio();
    SDL_AudioQuit();
  }

  bool SoundManager::load( int sample, const char *file )
  {
    logFile.print( "Loading sound '%s' ...", file );

    chunks[sample] = Mix_LoadWAV( file );

    if( chunks[sample] == null ) {
      logFile.printRaw( " Failed\n" );
      return false;
    }
    else {
      logFile.printRaw( " OK\n" );
      return true;
    }
  }

  void SoundManager::playSector( int sectorX, int sectorY )
  {
    Sector &sector = world.sectors[sectorX][sectorY];

    for( Object *obj = sector.objects.first(); obj != null; obj = obj->next[0] ) {
      Vec3 relPos = obj->p - camera.p;

      if( ( !obj->sounds.isEmpty() || !obj->contSounds.isEmpty() ) && relPos.sqL() < DMAX_SQ ) {
        short angle;
        ubyte distance;

        if( obj == camera.player ) {
          angle = 0;
          distance = 0;
        }
        else {
          angle = (short) Math::round( Math::deg( Math::atan2( relPos.x, relPos.y ) ) - camera.h );
          distance = (ubyte) ( Math::sqrt( Math::sqrt( relPos.sqL() / DMAX_SQ ) ) * 256.0f );
        }

        // non-continous
        for( Sound *snd = obj->sounds.first(); snd != null; snd = snd->next[0] ) {
          int channel = Mix_GroupAvailable( -1 );

          Mix_SetPosition( channel, angle, distance );
          Mix_PlayChannel( channel, chunks[ snd->sample ], 0 );
        }
        // continous
        for( Sound *snd = obj->contSounds.first(); snd != null; snd = snd->next[0] ) {
          if( contChannels.contains( (uint) snd ) ) {
            ContChannel &channel = contChannels.cachedValue();

            channel.state = ContChannel::UPDATED;

            Mix_SetPosition( channel.channel, angle, distance );
          }
          else {
            ContChannel channel;

            channel.state = ContChannel::UPDATED;
            channel.channel = Mix_GroupAvailable( -1 );

            Mix_SetPosition( channel.channel, 90, distance );
            Mix_PlayChannel( channel.channel, chunks[ snd->sample ], -1 );

            contChannels.add( (uint) snd, channel );
          }
        }
      }
    }
  }

  void SoundManager::update()
  {
    // add new sounds
    world.getInters( camera.p, DMAX );

    for( int x = world.minSectX ; x <= world.maxSectX; x++ ) {
      for( int y = world.minSectY; y <= world.maxSectY; y++ ) {
        playSector( x, y );
      }
    }
    // remove continous sounds that are not played any more
    for( HashIndex<ContChannel, HASHTABLE_SIZE>::Iterator i( contChannels ); !i.isPassed(); ) {
      ContChannel &channel = *i;
      int key = i.key();

      // we should advance now, so that we don't remove the element iterator is pointing at
      i.next();

      if( channel.state == ContChannel::NOT_UPDATED ) {
        Mix_HaltChannel( channel.channel );
        contChannels.remove( key );
      }
      else {
        channel.state = ContChannel::NOT_UPDATED;
      }
    }
  }

  bool SoundManager::loadMusic( const char *file )
  {
    logFile.print( "Loading music '%s' ...", file );

    music = Mix_LoadMUS( file );
    Mix_PlayMusic( music, -1 );

    isMusicPlaying = true;

    logFile.printRaw( " OK\n" );
    return true;
  }

  void SoundManager::freeMusic()
  {
    if( isMusicPlaying ) {
      Mix_HaltMusic();
      isMusicPlaying = false;
    }
    if( music != null ) {
      Mix_FreeMusic( music );
      music = null;
    }
  }

  void SoundManager::setVolume( float volume )
  {
    Mix_Volume( -1, (int) ( volume * 128.0f ) );
  }

  void SoundManager::setMusicVolume( float volume )
  {
    Mix_VolumeMusic( (int) ( volume * 128.0f ) );
  }

#endif

}
}
