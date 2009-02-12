INCLUDE_DIRECTORIES( .. )

ADD_LIBRARY( base STATIC
  Bitset.h
  Config.cpp
  Config.h
  DList.h
  HashIndex.h
  HashString.h
  List.h
  LogFile.cpp
  LogFile.h
  Mat33.h
  Mat44.h
  Math.cpp
  Math.h
  PoolAlloc.h
  Quat.h
  ReuseAlloc.h
  SVector.h
  String.h
  Vec3.h
  Vector.h
  base.h
  common.h )
