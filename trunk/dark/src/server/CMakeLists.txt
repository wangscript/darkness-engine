INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( server
  Main.cpp
  Main.h
  Server.cpp
  Server.h )

ADD_DEPENDENCIES( server precompile )
