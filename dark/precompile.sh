CXXFLAGS=`grep 'ADD_DEFINITIONS' CMakeLists.txt | sed -e 's/ADD_DEFINITIONS( \([^)].*\) )/\1/'`
PREFIX="src"

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
