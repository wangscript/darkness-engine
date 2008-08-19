/*
 *  Graphics_Context.h
 *
 *  Evidenca nalaganja tekstur in listov ter nalagalnik tekstur
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_Context.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Graphics_Context_h_
#define _Graphics_Context_h_

namespace Dark
{
namespace Graphics
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

#endif // _Graphics_Context_h_
