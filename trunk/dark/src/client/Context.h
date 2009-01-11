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

  class Context
  {
    private:

      struct Lists
      {
        uint base;
        uint count;
      };

      struct Texture
      {
        uint id;
        int  nUsers;
      };

      struct Sound
      {
        uint id;
      };

      struct Entry
      {
        Vector<List*>    lists;
        Vector<Texture*> textures;
        Vector<Sound*>   sounds;
      };

      Vector<List>      lists;
      Vector<Texture>   textures;

    public:

      ~Context();

      void init();

      uint createTexture( const String &context,
                          char *data,
                          int width,
                          int height,
                          int bytesPerPixel,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint createNormalmap( const String &context,
                            char *data,
                            int width,
                            int height,
                            int bytesPerPixel,
                            const Vec3 &lightNormal,
                            bool wrap = true,
                            int magFilter = GL_LINEAR,
                            int minFilter = GL_LINEAR_MIPMAP_LINEAR );

      uint loadTexture( const String &context,
                        const char *fileName,
                        bool wrap = true,
                        int magFilter = GL_LINEAR,
                        int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadNormalmap( const String &context,
                          const char *fileName,
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
