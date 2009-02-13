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

namespace Dark
{

  class Context
  {
    private:

      static const int TEXTURE_HASHSTRING_SIZE = 4096;
      static const int SOUND_HASHSTRING_SIZE = 1024;

      struct Texture
      {
        uint id;
        int  nEntries;

        Texture()
        {}

        Texture( uint id_, int nEntries_ ) : id( id_ ), nEntries( nEntries_ )
        {}
      };

      struct Sound
      {
        uint buffer;
        int  nEntries;

        Sound()
        {}

        Sound( uint buffer_, int nEntries_ ) : buffer( buffer_ ), nEntries( nEntries_ )
        {}
      };

      struct Lists
      {
        uint base;
        int  count;

        Lists()
        {}

        Lists( uint base_, int count_ ) : base( base_ ), count( count_ )
        {}
      };

      struct Entry
      {
        int nextSlot;

        Vector<Texture*> textures;
        Vector<Sound*>   sounds;
        Vector<Lists>    lists;
      };

      HashString<Texture, TEXTURE_HASHSTRING_SIZE> textures;
      HashString<Sound, SOUND_HASHSTRING_SIZE> sounds;

      Sparse<Entry> entries;

      uint buildTexture( const ubyte *data,
                         int width,
                         int height,
                         int bytesPerPixel,
                         bool wrap,
                         int magFilter,
                         int minFilter );

      uint buildNormalmap( ubyte *data,
                           const Vec3 &lightNormal,
                           int width,
                           int height,
                           int bytesPerPixel,
                           bool wrap,
                           int magFilter,
                           int minFilter );

    public:

      ~Context();

      void init();

      uint createTexture( int contextId,
                          const ubyte *data,
                          int width,
                          int height,
                          int bytesPerPixel,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint createNormalmap( int contextId,
                            ubyte *data,
                            const Vec3 &lightNormal,
                            int width,
                            int height,
                            int bytesPerPixel,
                            bool wrap = true,
                            int magFilter = GL_LINEAR,
                            int minFilter = GL_LINEAR_MIPMAP_LINEAR );

      uint loadTexture( int context,
                        const char *fileName,
                        bool wrap = true,
                        int magFilter = GL_LINEAR,
                        int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadNormalmap( int context,
                          const char *fileName,
                          const Vec3 &lightNormal,
                          bool wrap = true,
                          int magFilter = GL_LINEAR,
                          int minFilter = GL_LINEAR_MIPMAP_NEAREST );

      uint loadSound( int context, const char *fileName );

      uint genList( int contextId );
      uint genLists( int contextId, int count );

      int createContext();
      void freeContext( int context );

      void free();

      uint getLastTexture();
      uint getLastSound();
      uint getLastList();
  };

  extern Context context;

}
