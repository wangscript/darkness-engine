/*
 *  Graphics_Terrain.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Graphics_Terrain.h"

#include "World.h"

#ifdef __WIN32__

static PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = null;
static PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = null;
static PFNGLACTIVETEXTUREPROC glActiveTexture = null;

#endif

namespace Dark
{
namespace Graphics
{

  Quadtree::~Quadtree()
  {
    if( next[1] != null ) {
      delete next[0];
      delete next[1];
      delete next[2];
      delete next[3];
    }
  }

  Terrain::~Terrain()
  {
    free();
  }

  uint Terrain::makeQuad( int minX, int minY, int maxX, int maxY, float *minHeight, float *maxHeight )
  {
    assert( 0 <= minX && minX <= Dark::Terrain::MAX );
    assert( 0 <= minY && minY <= Dark::Terrain::MAX );
    assert( 0 <= maxX && maxX <= Dark::Terrain::MAX );
    assert( 0 <= maxY && maxY <= Dark::Terrain::MAX );

    float (&heightMap)[Dark::Terrain::MAX + 1][Dark::Terrain::MAX + 1] = world.terrain.heightMap;
    TerraQuad (&terraQuad)[128][128] = world.terrain.terra;

    uint list = context.genList();
    glNewList( list, GL_COMPILE );

    *minHeight = Math::INF;
    *maxHeight = -Math::INF;

    for( int y = minY; y < maxY; y++ ) {
      glBegin( GL_TRIANGLE_STRIP );

      for( int x = minX; x <= maxX; x ++ ) {

        Vec3 v0(   x       * Dark::TerraQuad::SIZE - Dark::Terrain::DIM,
                 ( y + 1 ) * Dark::TerraQuad::SIZE - Dark::Terrain::DIM,
                   heightMap[x][y + 1] );
        Vec3 v1(   x       * Dark::TerraQuad::SIZE - Dark::Terrain::DIM,
                   y       * Dark::TerraQuad::SIZE - Dark::Terrain::DIM,
                   heightMap[x][y] );

        Vec3 n0 = terraQuad[x][y].normal[0];
        Vec3 n1 = terraQuad[x][y].normal[0] + terraQuad[x][y].normal[1];

        if( x > 0 ) {
          n0 += terraQuad[x - 1][y].normal[0] + terraQuad[x - 1][y].normal[1];
          n1 += terraQuad[x - 1][y].normal[1];
        }
        if( y > 0 ) {
          n1 += terraQuad[x][y - 1].normal[0];
        }
        if( x > 0 && y > 0 ) {
          n1 += terraQuad[x - 1][y - 1].normal[0] + terraQuad[x - 1][y - 1].normal[1];
        }
        if( y < Dark::Terrain::MAX ) {
          n0 += terraQuad[x][y + 1].normal[0] + terraQuad[x][y + 1].normal[1];
        }
        if( x > 0 && y < Dark::Terrain::MAX ) {
          n0 += terraQuad[x - 1][y + 1].normal[1];
        }

        n0 = ( n0 / 6.0 ).norm();
        n1 = ( n1 / 6.0 ).norm();

        glMultiTexCoord2i( GL_TEXTURE0_ARB,
                           x * TERRA_DETAILTEX_SCALE,
                           ( y + 1 ) * TERRA_DETAILTEX_SCALE );
        glMultiTexCoord2f( GL_TEXTURE1_ARB,
                           (float) x / Dark::Terrain::MAX,
                           (float) ( y + 1 ) / Dark::Terrain::MAX );
        glNormal3fv( n0 );
        glVertex3fv( v0 );

        glMultiTexCoord2i( GL_TEXTURE0_ARB,
                           x * TERRA_DETAILTEX_SCALE,
                           y * TERRA_DETAILTEX_SCALE );
        glMultiTexCoord2f( GL_TEXTURE1_ARB,
                           (float) x / Dark::Terrain::MAX,
                           (float) y / Dark::Terrain::MAX );
        glNormal3fv( n1 );
        glVertex3fv( v1 );

        *minHeight = min( *minHeight, heightMap[x][y] );
        *maxHeight = max( *maxHeight, heightMap[x][y] );
      }
      glEnd();
    }

    for( int x = minX; x <= maxX; x++ ) {
      *minHeight = min( *minHeight, heightMap[x][maxY] );
      *maxHeight = max( *maxHeight, heightMap[x][maxY] );
    }

    glEndList();

    return list;
  }

  void Terrain::buildQuadtree( Quadtree *qTree, int minX, int minY, int maxX, int maxY,
                               float *minHeight, float *maxHeight )
  {
    static int depth = 0;

    depth++;

    *minHeight = Math::INF;
    *maxHeight = -Math::INF;

    if( depth <= TERRA_DEPTH ) {
      float minChildZ, maxChildZ;

      qTree->next[0] = new Quadtree;
      buildQuadtree( qTree->next[0], minX, minY, ( minX + maxX ) / 2, ( minY + maxY ) / 2,
                     &minChildZ, &maxChildZ );

      *minHeight = min( *minHeight, minChildZ );
      *maxHeight = max( *maxHeight, maxChildZ );

      qTree->next[1] = new Quadtree;
      buildQuadtree( qTree->next[1], ( minX + maxX ) / 2, minY, maxX, ( minY + maxY ) / 2,
                     &minChildZ, &maxChildZ );

      *minHeight = min( *minHeight, minChildZ );
      *maxHeight = max( *maxHeight, maxChildZ );

      qTree->next[2] = new Quadtree;
      buildQuadtree( qTree->next[2], minX, ( minY + maxY ) / 2, ( minX + maxX ) / 2, maxY,
                     &minChildZ, &maxChildZ );

      *minHeight = min( *minHeight, minChildZ );
      *maxHeight = max( *maxHeight, maxChildZ );

      qTree->next[3] = new Quadtree;
      buildQuadtree( qTree->next[3], ( minX + maxX ) / 2, ( minY + maxY ) / 2, maxX, maxY,
                     &minChildZ, &maxChildZ );

      *minHeight = min( *minHeight, minChildZ );
      *maxHeight = max( *maxHeight, maxChildZ );

      qTree->p = Vec3( ( qTree->next[0]->p.x + qTree->next[1]->p.x ) * 0.5,
                       ( qTree->next[0]->p.y + qTree->next[2]->p.y ) * 0.5,
                       ( *minHeight + *maxHeight ) * 0.5 );

      // pitagora
      float a  = ( *maxHeight - *minHeight ) * 0.5;
      float b  = ( maxX - minX ) * Dark::TerraQuad::DIM;
      float b2 = b*b;

      qTree->r = Math::sqrt( a*a + b2 + b2 );
    }
    else {
      qTree->list = makeQuad( minX, minY, maxX, maxY, minHeight, maxHeight );
      qTree->next[1] = null;

      qTree->p = Vec3( ( minX + maxX ) * Dark::TerraQuad::DIM - Dark::Terrain::DIM,
                       ( minY + maxY ) * Dark::TerraQuad::DIM - Dark::Terrain::DIM,
                       ( *minHeight + *maxHeight ) * 0.5 );

      // pitagora
      float a  = ( *maxHeight - *minHeight ) * 0.5;
      float b  = ( maxX - minX ) * Dark::TerraQuad::DIM;
      float b2 = b*b;

      qTree->r = Math::sqrt( a*a + b2 + b2 );
    }

    depth--;
  }

  void Terrain::init( uint terraMap, uint terraDetail )
  {
    tTerraDetail = terraDetail;
    tTerraMap = terraMap;

#ifdef __WIN32__
    glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC) SDL_GL_GetProcAddress( "glMultiTexCoord2i" );
    glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC) SDL_GL_GetProcAddress( "glMultiTexCoord2f" );
    glActiveTexture   = (PFNGLACTIVETEXTUREPROC)   SDL_GL_GetProcAddress( "glActiveTexture" );
#endif

    float dummy0, dummy1;

    qTerra = new Quadtree;
    buildQuadtree( qTerra, 0, 0, Dark::Terrain::MAX, Dark::Terrain::MAX, &dummy0, &dummy1 );
  }

  void Terrain::drawQuadtree( const Quadtree *qTree )
  {
    static int depth = 0;

    depth++;

    if( frustum.isVisible( *qTree ) ) {
      if( depth <= TERRA_DEPTH ) {
        drawQuadtree( qTree->next[0] );
        drawQuadtree( qTree->next[1] );
        drawQuadtree( qTree->next[2] );
        drawQuadtree( qTree->next[3] );
      }
      else {
        glCallList( qTree->list );
      }
    }

    depth--;
  }

  void Terrain::draw()
  {
    glBindTexture( GL_TEXTURE_2D, tTerraDetail );
    glActiveTexture( GL_TEXTURE1_ARB );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, tTerraMap );

    drawQuadtree( qTerra );

    glDisable( GL_TEXTURE_2D );
    glActiveTexture( GL_TEXTURE0_ARB );
  }

  void Terrain::free() {
    delete qTerra;
  }

}
}