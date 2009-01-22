INCLUDE_DIRECTORIES( base . )

# precompiled header
IF( WIN32 )

  # TODO: precompiled headers for VC++
  ADD_CUSTOM_TARGET( precompile ALL )

ELSE( WIN32 )

  ADD_CUSTOM_TARGET( precompile ALL
    DEPENDS precompiled.h.gch )

  ADD_CUSTOM_COMMAND(
    OUTPUT precompiled.h.gch
    DEPENDS base
    COMMAND
      rm -f precompiled.h.gch &&
      ${CMAKE_CXX_COMPILER} ${CXX_FLAGS} precompiled.h )

ENDIF( WIN32 )

#SUBDIRS( base matrix nirvana server client test )
SUBDIRS( base test )
