/*
 *  Graphics_Skybox.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Graphics_Skybox.h"

namespace Dark
{
namespace Graphics
{

  void Skybox::drawUpper( uint top, uint front, uint left, uint back, uint right ) {
    //  top
    glBindTexture( GL_TEXTURE_2D, top );
    glBegin( GL_QUADS );
      glTexCoord2f( 0, 1 ); glVertex3f(  SKY_DIST,  SKY_DIST,  SKY_DIST );
      glTexCoord2f( 0, 0 ); glVertex3f(  SKY_DIST, -SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 0 ); glVertex3f( -SKY_DIST, -SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 1 ); glVertex3f( -SKY_DIST,  SKY_DIST,  SKY_DIST );
    glEnd();
    // fore
    glBindTexture( GL_TEXTURE_2D, right );
    glBegin( GL_QUADS );
      glTexCoord2i( 0, 0 ); glVertex3f(  SKY_DIST,  SKY_DIST,  SKY_DIST );
      glTexCoord2i( 1, 0 ); glVertex3f( -SKY_DIST,  SKY_DIST,  SKY_DIST );
      glTexCoord2i( 1, 1 ); glVertex3f( -SKY_DIST,  SKY_DIST, -SKY_DIST );
      glTexCoord2i( 0, 1 ); glVertex3f(  SKY_DIST,  SKY_DIST, -SKY_DIST );
    glEnd();
    // left
    glBindTexture( GL_TEXTURE_2D, back );
    glBegin( GL_QUADS );
      glTexCoord2f( 0, 0 ); glVertex3f( -SKY_DIST,  SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 0 ); glVertex3f( -SKY_DIST, -SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 1 ); glVertex3f( -SKY_DIST, -SKY_DIST, -SKY_DIST );
      glTexCoord2f( 0, 1 ); glVertex3f( -SKY_DIST,  SKY_DIST, -SKY_DIST );
    glEnd();
    // back
    glBindTexture( GL_TEXTURE_2D, left );
    glBegin( GL_QUADS );
      glTexCoord2f( 0, 0 ); glVertex3f( -SKY_DIST, -SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 0 ); glVertex3f(  SKY_DIST, -SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 1 ); glVertex3f(  SKY_DIST, -SKY_DIST, -SKY_DIST );
      glTexCoord2f( 0, 1 ); glVertex3f( -SKY_DIST, -SKY_DIST, -SKY_DIST );
    glEnd();
    // right
    glBindTexture( GL_TEXTURE_2D, front );
    glBegin( GL_QUADS );
      glTexCoord2f( 0, 0 ); glVertex3f(  SKY_DIST, -SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 0 ); glVertex3f(  SKY_DIST,  SKY_DIST,  SKY_DIST );
      glTexCoord2f( 1, 1 ); glVertex3f(  SKY_DIST,  SKY_DIST, -SKY_DIST );
      glTexCoord2f( 0, 1 ); glVertex3f(  SKY_DIST, -SKY_DIST, -SKY_DIST );
    glEnd();
  }

  void Skybox::init( Context *context, uint top, uint front, uint left, uint back, uint right ) {
    list = context->genList();
    glNewList( list, GL_COMPILE );
      drawUpper( top, front, left, back, right );
    glEndList();
  }

  void Skybox::init( Context *context, uint top, uint front, uint left, uint back, uint right,
    uint bottom )
  {
    list = context->genList();
    glNewList( list, GL_COMPILE );
      drawUpper( top, front, left, back, right );
      //  bottom
      glBindTexture( GL_TEXTURE_2D, bottom );
      glBegin( GL_QUADS );
        glTexCoord2f( 0, 0 ); glVertex3f(  SKY_DIST,  SKY_DIST, -SKY_DIST );
        glTexCoord2f( 1, 0 ); glVertex3f( -SKY_DIST,  SKY_DIST, -SKY_DIST );
        glTexCoord2f( 1, 1 ); glVertex3f( -SKY_DIST, -SKY_DIST, -SKY_DIST );
        glTexCoord2f( 0, 1 ); glVertex3f(  SKY_DIST, -SKY_DIST, -SKY_DIST );
      glEnd();
    glEndList();
  }

  void Skybox::draw() {
    glCallList( list );
  }

}
}
