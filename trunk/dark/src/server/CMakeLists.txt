INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( server Server.cpp
                       Main.cpp )
