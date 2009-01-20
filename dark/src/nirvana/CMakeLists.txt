INCLUDE_DIRECTORIES( .. )

ADD_LIBRARY( nirvana STATIC
  M_Walker.cpp
  M_Walker.h
  Mind.cpp
  Mind.h
  Nirvana.cpp
  Nirvana.h
  Soul.cpp
  Soul.h )

ADD_DEPENDENCIES( nirvana precompile )
