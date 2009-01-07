/*
 *  Context.h
 *
 *  Evidenca nalaganja tekstur in listov ter nalagalnik tekstur
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Context_h_
#define _Client_Context_h_

namespace Dark
{
namespace Client
{

  struct ContextList
  {
    uint base;
    uint count;
  };

  class Context
  {
    protected:

      uint *loadedTextures;

    public:

      Vector<uint>        textures;
      Vector<ContextList> lists;

      ~Context();

      void init();

      uint createTexture( char *data,
                          int width,
                          int height,
                          int bytesPerPixel,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint createNormalmap( char *data,
                            int width,
                            int height,
                            int bytesPerPixel,
                            const Vec3 &lightNormal,
                            bool wrap = true,
                            int magFilter = GL_LINEAR,
                            int minFilter = GL_LINEAR_MIPMAP_LINEAR );

      uint loadTexture( const char *fileName,
                        bool wrap = true,
                        int magFilter = GL_LINEAR,
                        int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadNormalmap( const char *fileName,
                          const Vec3 &lightNormal,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      void freeTextures();

      uint genList();
      uint genLists( int count );
      void freeLists();
      void free();

      uint getLastTexture();
      uint getLastList();
  };

  extern Context context;

}
}

#endif // _Client_Context_h_
