/*
 *  Font.h
 *
 *  Bitmap font loader and print function
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Font_h_
#define _Client_Font_h_

#define FONT_BIAS_X     0.01f
#define FONT_BIAS_Y     0
#define FONT_WIDTH      0.65f
#define FONT_HEIGHT     1.0f
#define FONT_DEPTH      -50.0f

namespace oz
{
namespace Client
{

  class Font
  {
    protected:
      uint texture;
      uint baseList;

      uint loadTexture( const char *fileName );

    public:
      Font();
      ~Font();

      void init( const char *fileName, float scale );
      void print( float x, float y, const char *string, ... ) const;
      void free();
  };

}
}

#endif // _Client_Font_h_
