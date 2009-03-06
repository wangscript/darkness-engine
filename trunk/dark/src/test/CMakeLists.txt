INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base )

ADD_EXECUTABLE( test
  test.cpp )

ADD_DEPENDENCIES( test precompile )
