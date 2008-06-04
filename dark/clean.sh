#!/bin/sh

if [ -f Makefile ]; then
  echo 'make clean'
  make clean
fi
sh precompile.sh clean
echo 'rm -rf CMakeCache.txt'
rm -rf CMakeCache.txt
echo 'rm -rf CMakeFiles cmake_install.cmake Makefile'
rm -rf CMakeFiles cmake_install.cmake Makefile
echo 'rm -rf src/CMakeFiles src/cmake_install.cmake src/Makefile'
rm -rf src/CMakeFiles src/cmake_install.cmake src/Makefile
echo 'rm -rf src/*/CMakeFiles src/*/cmake_install.cmake src/*/Makefile'
rm -rf src/*/CMakeFiles src/*/cmake_install.cmake src/*/Makefile
echo 'rm -f dark.kdevelop.pcs dark.kdevses'
rm -f dark.kdevelop.pcs dark.kdevses
