INCLUDE_DIRECTORIES( .. )

ADD_LIBRARY( base STATIC
    common.h
    Vector.h
    SVector.h
    List.h
    DList.h
    String.h
    Reuser.h
    Bitset.h
    HashIndex.h
    HashString.h
    Math.h
    Math.cpp
    Vec3.h
    Quat.h
    Mat33.h
    Mat44.h
    LogFile.h
    LogFile.cpp
    Config.h
    Config.cpp )
