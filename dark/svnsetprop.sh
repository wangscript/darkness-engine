#!/bin/sh

svn pd -R svn:keywords .
svn pd -R svn:ignore .

svn ps -R svn:keywords 'Id' src
svn ps -R svn:ignore 'CMakeFiles
CMakeCache.txt
cmake_install.cmake
Makefile' src

svn ps svn:ignore 'CMakeFiles
CMakeCache.txt
cmake_install.cmake
Makefile
doyxgen
dark.kdev*' .
