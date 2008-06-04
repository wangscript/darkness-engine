CXXFLAGS="-O0 -g -Wall -Wextra -Winvalid-pch -pipe"
PREFIX="src/base"

if [ "$1" == "clean" ]; then
  echo rm -f $PREFIX/precompiled.h.gch
  rm -f $PREFIX/precompiled.h.gch
else
  echo rm -f $PREFIX/precompiled.h.gch
  rm -f $PREFIX/precompiled.h.gch
  echo g++ $CXXFLAGS $PREFIX/precompiled.h
  g++ $CXXFLAGS $PREFIX/precompiled.h
fi

unset CXXFLAGS
