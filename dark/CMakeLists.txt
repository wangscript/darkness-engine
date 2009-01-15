cmake_minimum_required( VERSION 2.6 )

PROJECT( Dark CXX )

IF( WIN32 )

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
  # lowercase so that precompile.sh script doesn't screw up
  add_definitions( /W4 )

ELSE( WIN32 )

  INCLUDE_DIRECTORIES( /usr/include/libxml2 )
  LINK_LIBRARIES( xml2 SDL SDL_image SDL_mixer GL GLU openal alut vorbisfile )
  ADD_DEFINITIONS( -g3 -Wall -Wextra -Winvalid-pch -pipe -I/usr/include -I/usr/include/SDL  )

ENDIF( WIN32 )

SUBDIRS( src )
