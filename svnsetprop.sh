#!/bin/sh

svn ps -R svn:ignore 'CMakeFiles
CMakeCache.txt
cmake_install.cmake
Makefile
dark.kdev*' .

svn ps -R svn:keywords 'Id' .
