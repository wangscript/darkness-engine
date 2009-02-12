INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base )

ADD_EXECUTABLE( test
  sparse.cpp )

ADD_DEPENDENCIES( test precompile )
