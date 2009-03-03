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

namespace oz
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

      uint createTexture( char *data, int width, int height, int bytesPerPixel,
                          int magFilter, int minFilter, bool wrap );
      uint createNormalmap( char *data, int width, int height, int bytesPerPixel,
                            int magFilter, int minFilter, bool wrap,
                            const Vec3 &lightNormal );

      uint loadTexture( const char *fileName, int magFilter, int minFilter, bool wrap );
      uint loadNormalmap( const char *fileName, int magFilter, int minFilter, bool wrap,
                          const Vec3 &lightNormal );

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
