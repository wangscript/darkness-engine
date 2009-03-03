cmake_minimum_required( VERSION 2.6 )
project( backdark CXX )

if( WIN32 )

  include_directories(
      ../iconv/include
      ../libxml2/include
      ../SDL/include
      ../SDL_image/include
      ../ogg/include
      ../vorbis/include
      ../OpenAL/include
      ../freealut/include )

  link_directories(
      ../../../iconv/lib
      ../../../libxml2/lib
      ../../../SDL/lib
      ../../../SDL_image/lib
      ../../../SDL_mixer/lib
      ../../../ogg/lib
      ../../../vorbis/lib
      ../../../OpenAL/libs/Win32
      ../../../freealut/lib )

  link_libraries(
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

  add_definitions( /W4 )

  # TODO: precompiled headers for VC++
  add_custom_target( precompile ALL )

else( WIN32 )

  # required libraries
  find_file( xml2_h libxml2/libxml )
  find_library( xml2_so xml2 )
  find_file( SDL_h SDL/SDL.h )
  find_library( SDL_so SDL )
  find_file( SDL_image_h SDL/SDL_image.h )
  find_library( SDL_image_so SDL_image )
  find_file( GL_h GL/gl.h )
  find_library( GL_so GL )
  find_file( GLU_h GL/glu.h )
  find_library( GLU_so GLU )
  find_file( AL_h AL/al.h )
  find_library( AL_so openal )
  find_file( ALUT_h AL/alut.h )
  find_library( ALUT_so alut )
  find_file( OGG_h ogg/ogg.h )
  find_library( OGG_so ogg )
  find_file( VORBIS_h vorbis/vorbisfile.h )
  find_library( VORBIS_so vorbisfile )

  set( CXX_FLAGS -g3 -Wall -Wextra -Winvalid-pch -pipe -I/usr/include/libxml2 )
  add_definitions( ${CXX_FLAGS} )
  link_libraries( xml2 SDL SDL_image GL GLU openal alut vorbisfile )

  install( FILES src/client/dark
           DESTINATION bin/dark
           PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                       GROUP_READ GROUP_EXECUTE
                       WORLD_READ WORLD_EXECUTE )

  # precompiled header
  include_directories( . )

  add_custom_target( precompile ALL
    DEPENDS precompiled.h.gch )

  add_custom_command(
    OUTPUT precompiled.h.gch
    DEPENDS base
    COMMAND
      rm -f precompiled.h.gch &&
      ${CMAKE_CXX_COMPILER} ${CXX_FLAGS} precompiled.h )

endif( WIN32 )

subdirs( src )
