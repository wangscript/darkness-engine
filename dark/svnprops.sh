#!/bin/sh

svn propdel -R svn:keywords .
svn propdel -R svn:ignore .

svn propset -R svn:keywords 'Id' src
svn propset svn:keywords 'Id' *.sh

svn propset -R svn:ignore 'CMakeFiles
CMakeCache.txt
cmake_install.cmake
Makefile' src

svn propset svn:ignore 'CMakeFiles
CMakeCache.txt
cmake_install.cmake
Makefile
doyxgen
dark.kdev*' .
