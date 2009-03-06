/*
 *  ResourceManager.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2009, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace oz
{
namespace Client
{

  class Context;

  class ResourceManager
  {
    friend class Context;

    private:

      struct Texture
      {
        uint id;
        int  nUsers;
      };

      struct Sound
      {
        uint buffer;
        int  nUsers;
      };

      struct Lists
      {
        uint base;
        int  count;
      };

      Texture         *textures;
      Sound           *sounds;
      Lists           *lists;
      Sparse<uint>    bufferTextures;

      static uint buildTexture( const ubyte *data,
                                int width,
                                int height,
                                int bytesPerPixel,
                                bool wrap,
                                int magFilter,
                                int minFilter );

      static uint buildNormalmap( ubyte *data,
                                  const Vec3 &lightNormal,
                                  int width,
                                  int height,
                                  int bytesPerPixel,
                                  bool wrap,
                                  int magFilter,
                                  int minFilter );

      static uint createTexture( const ubyte *data,
                                 int width,
                                 int height,
                                 int bytesPerPixel,
                                 bool wrap,
                                 int magFilter,
                                 int minFilter );

      static uint createNormalmap( ubyte *data,
                                   const Vec3 &lightNormal,
                                   int width,
                                   int height,
                                   int bytesPerPixel,
                                   bool wrap,
                                   int magFilter,
                                   int minFilter );

      uint loadTexture( int resource, bool wrap, int magFilter, int minFilter );

      uint loadNormalmap( int resource,
                          const Vec3 &lightNormal,
                          bool wrap,
                          int magFilter,
                          int minFilter );

      uint loadSound( int context, int resource );

      uint genList( int contextId );

      uint genLists( int contextId, int count );

    public:

      void init();
      void free();

  };

  extern ResourceManager resourceManager;

}
}
