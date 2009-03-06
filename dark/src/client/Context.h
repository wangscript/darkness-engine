/*
 *  Context.h
 *
 *  Evidenca in nalaganja in nalagalnik tekstur, zvokov in listov
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

namespace oz
{
namespace Client
{

  class Context
  {
    private:

      Vector<int> textures;
      Vector<int> bufferTextures;
      Vector<int> sounds;
      Vector<int> lists;

    public:

      ~Context();

      uint createTexture( const ubyte *data,
                          int width,
                          int height,
                          int bytesPerPixel,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint createNormalmap( ubyte *data,
                            const Vec3 &lightNormal,
                            int width,
                            int height,
                            int bytesPerPixel,
                            bool wrap = true,
                            int magFilter = GL_LINEAR,
                            int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadTexture( int resource,
                        bool wrap = true,
                        int magFilter = GL_LINEAR,
                        int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadNormalmap( int resource,
                          const Vec3 &lightNormal,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadSound( int context, int resource );

      uint genList( int contextId );

      uint genLists( int contextId, int count );

      int createContext();
      void freeContext( int context );

  };

  extern Context context;

}
}
