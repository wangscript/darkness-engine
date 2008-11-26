cmake_minimum_required( VERSION 2.6 )

PROJECT( Dark CXX )

IF(WIN32)

  INCLUDE_DIRECTORIES(
      ../iconv/include 
      ../libxml2/include 
      ../SDL/include
      ../SDL_image/include
      ../ogg/include 
      ../vorbis/include
      ../OpenAL/include
      ../freealut/include )
  LINK_DIRECTORIES(
      ../../../iconv/lib 
      ../../../libxml2/lib
      ../../../SDL/lib
      ../../../SDL_image/lib
      ../../../SDL_mixer/lib
      ../../../ogg/lib
      ../../../vorbis/lib
      ../../../OpenAL/libs/Win32
      ../../../freealut/lib )
  ADD_DEFINITIONS( /W4 )
  LINK_LIBRARIES(
      iconv.lib
      libxml2.lib
      SDLmain.lib
      SDL.lib
      SDL_image.lib
      SDL_mixer.lib
      opengl32.lib
      glu32.lib
      openal32.lib 
      alut.lib 
      vorbisfile.lib )

ELSE(WIN32)

  INCLUDE_DIRECTORIES( /usr/include/libxml2 )
  ADD_DEFINITIONS( -O0 -g -pedantic -Wall -Wextra -Winvalid-pch -pipe )
  LINK_LIBRARIES( xml2 SDL SDL_image SDL_mixer GL GLU openal alut vorbisfile )

ENDIF(WIN32)

SUBDIRS( src )
