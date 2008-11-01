INCLUDE_DIRECTORIES( ../base ../nirvana ../matrix )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( test test.cpp )
