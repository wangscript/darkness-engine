cmake_minimum_required(VERSION 2.6)

PROJECT( Dark CXX )

INCLUDE_DIRECTORIES( /usr/include/libxml2 )
ADD_DEFINITIONS( -O0 -g -Wall -Wextra -Winvalid-pch -pipe )
LINK_LIBRARIES( xml2 SDL SDL_image SDL_mixer GL GLU openal alut vorbisfile )

SUBDIRS( src )
