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

  FIND_FILE( xml2_h libxml2/libxml )
  FIND_LIBRARY( xml2_so xml2 )
  FIND_FILE( SDL_h SDL/SDL.h )
  FIND_LIBRARY( SDL_so SDL )
  FIND_FILE( SDL_image_h SDL/SDL_image.h )
  FIND_LIBRARY( SDL_image_so SDL_image )
  FIND_FILE( GL_h GL/gl.h )
  FIND_LIBRARY( GL_so GL )
  FIND_FILE( GLU_h GL/glu.h )
  FIND_LIBRARY( GLU_so GLU )
  FIND_FILE( AL_h AL/al.h )
  FIND_LIBRARY( AL_so openal )
  FIND_FILE( ALUT_h AL/alut.h )
  FIND_LIBRARY( ALUT_so alut )
  FIND_FILE( OGG_h ogg/ogg.h )
  FIND_LIBRARY( OGG_so ogg )
  FIND_FILE( VORBIS_h vorbis/vorbisfile.h )
  FIND_LIBRARY( VORBIS_so vorbisfile )

  SET( CXX_FLAGS -g -Wall -Wextra -Winvalid-pch -pipe -I/usr/include -I/usr/include/SDL )
  INCLUDE_DIRECTORIES( /usr/include/libxml2 )
  ADD_DEFINITIONS( ${CXX_FLAGS} )
  LINK_LIBRARIES( xml2 SDL SDL_image GL GLU openal alut vorbisfile )

  INSTALL( FILES src/client/dark
           DESTINATION bin/dark
           PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                       GROUP_READ GROUP_EXECUTE
                       WORLD_READ WORLD_EXECUTE )

ENDIF( WIN32 )

SUBDIRS( src )
