cmake_minimum_required( VERSION 2.6 )

PROJECT( openzone C CXX )

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

  ADD_DEFINITIONS( /W4 )

  # TODO: precompiled headers for VC++
  ADD_CUSTOM_TARGET( precompile ALL )

ELSE( WIN32 )

  # required libraries
  find_package( LibXml2 REQUIRED )
  find_package( PhysFS REQUIRED )
  find_package( SDL REQUIRED )
  find_package( SDL_image REQUIRED )
  find_package( OpenGL REQUIRED )
  find_package( GLU REQUIRED )
  find_package( OpenAL REQUIRED )

  find_file( ALUT_INCLUDE_DIR AL )
  find_library( ALUT_LIBRARY alut )
  find_file( OGG_INCLUDE_DIR ogg )
  find_library( OGG_LIBRARY ogg )
  find_file( VORBIS_INCLUDE_DIR vorbis )
  find_library( VORBIS_LIBRARY vorbisfile )

  SET( CXX_FLAGS -g3 -Wall -Wextra -Winvalid-pch -pipe -I/usr/include/libxml2 -I/usr/include/SDL )
  ADD_DEFINITIONS( ${CXX_FLAGS} )
  LINK_LIBRARIES( xml2 SDL SDL_image GL GLU openal alut vorbisfile )

  INSTALL( FILES src/client/dark
           DESTINATION bin/dark
           PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                       GROUP_READ GROUP_EXECUTE
                       WORLD_READ WORLD_EXECUTE )

  # precompiled header
  INCLUDE_DIRECTORIES( . )

  ADD_CUSTOM_TARGET( precompile ALL
    DEPENDS precompiled.h.gch )

  ADD_CUSTOM_COMMAND(
    OUTPUT precompiled.h.gch
    DEPENDS base precompiled.h
    COMMAND
      rm -f precompiled.h.gch &&
      ${CMAKE_CXX_COMPILER} ${CXX_FLAGS} precompiled.h )

ENDIF( WIN32 )

SUBDIRS( src )
