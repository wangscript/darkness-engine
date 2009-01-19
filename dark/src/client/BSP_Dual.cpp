/*
 *  BSP_Dual.cpp
 *
 *  BSP level rendering class
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: BSP.cpp 52 2009-01-07 23:17:53Z Davorin.Ucakar $
 */

#include "precompiled.h"

#include "BSP_Dual.h"

#include "Frustum.h"

#ifdef __WIN32__
static PFNGLACTIVETEXTUREPROC glActiveTexture = null;
static PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = null;
#endif

namespace Dark
{

  BSP_Dual::BSP_Dual()
  {}

  BSP_Dual::BSP_Dual( BSP *bsp )
  {
    textures = null;
    lightMaps = null;

    init( bsp );
  }

  BSP_Dual::~BSP_Dual()
  {
    free();
  }

  int BSP_Dual::getLeafIndex( const Vec3 &p ) const
  {
    int nodeIndex = 0;

    do {
      const BSP::Node  &node  = bsp->nodes[nodeIndex];
      const BSP::Plane &plane = bsp->planes[node.plane];

      if( ( p * plane.normal - plane.distance ) < 0.0f ) {
        nodeIndex = node.back;
      }
      else {
        nodeIndex = node.front;
      }
    }
    while( nodeIndex >= 0 );

    return ~nodeIndex;
  }

  void BSP_Dual::drawFace( int faceIndex ) const
  {
    BSP::Face &face = bsp->faces[faceIndex];

    glVertexPointer( 3, GL_FLOAT, sizeof( BSP::Vertex ),
                     (float*) bsp->vertices[face.firstVertex].p );

    glActiveTexture( GL_TEXTURE0 );
    glClientActiveTexture( GL_TEXTURE0 );

    glBindTexture( GL_TEXTURE_2D, textures[face.texture] );
    glTexCoordPointer( 2, GL_FLOAT, sizeof( BSP::Vertex ),
                       bsp->vertices[face.firstVertex].texCoord );

    glActiveTexture( GL_TEXTURE1 );
    glClientActiveTexture( GL_TEXTURE1 );

    glBindTexture( GL_TEXTURE_2D, lightMaps[face.lightmap] );
    glTexCoordPointer( 2, GL_FLOAT, sizeof( BSP::Vertex ),
                       bsp->vertices[face.firstVertex].lightmapCoord );

    glNormal3fv( face.normal );
    glDrawElements( GL_TRIANGLES, face.nIndices, GL_UNSIGNED_INT, &bsp->indices[face.firstIndex] );
  }

  void BSP_Dual::init( BSP *bsp_ )
  {
    bsp = bsp_;

#ifdef __WIN32__
    if( glActiveTexture == null ) {
      glActiveTexture = (PFNGLACTIVETEXTUREPROC) SDL_GL_GetProcAddress( "glActiveTexture" );
      glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)
          SDL_GL_GetProcAddress( "glClientActiveTexture" );
    }
#endif

    logFile.println( "Loading BSP structure {" );
    logFile.indent();

    textures = new uint[bsp->nTextures];
    for( int i = 0; i < bsp->nTextures; i++ ) {
      if( bsp->textures[i] != null ) {
        textures[i] = context.loadTexture( bsp->textures[i],
                                           true );
      }
    }

    lightMaps = new uint[bsp->nLightmaps];
    for( int i = 0; i < bsp->nLightmaps; i++ ) {

      char *bits = bsp->lightmaps[i].bits;
      for( int j = 0; j < Dark::BSP::LIGHTMAP_SIZE; j++ ) {
        bits[j] += (char) ( ( 255 - bits[j] ) * BSP_GAMMA_CORR );
      }

      lightMaps[i] = context.createTexture( bits,
                                            Dark::BSP::LIGHTMAP_DIM,
                                            Dark::BSP::LIGHTMAP_DIM,
                                            Dark::BSP::LIGHTMAP_BPP,
                                            true );
    }

    hiddenFaces.setSize( bsp->nFaces );
    visibleLeafs.setSize( bsp->visual.bitsets[0].length() );
    drawnFaces.setSize( bsp->nFaces );
    hiddenFaces.clearAll();

    baseList = context.genLists( bsp->nFaces );
    for( int i = 0; i < bsp->nFaces; i++ ) {
      BSP::Vertex *verts = &bsp->vertices[ bsp->faces[i].firstVertex ];

      for( int j = 0; j < bsp->faces[i].nVertices; j++ ) {
        if( verts[j].p.x < -bsp->maxDim || verts[j].p.x > bsp->maxDim ||
            verts[j].p.y < -bsp->maxDim || verts[j].p.y > bsp->maxDim ||
            verts[j].p.z < -bsp->maxDim || verts[j].p.z > bsp->maxDim )
        {
          hiddenFaces.set( i );
          break;
        }
      }
    }

    logFile.unindent();
    logFile.println( "}" );
  }

  void BSP_Dual::draw( const Vec3 &p )
  {
    glPushMatrix();
    glTranslatef( p.x, p.y, p.z );

    drawnFaces = hiddenFaces;

    int    cluster = bsp->leafs[ getLeafIndex( camera.p ) ].cluster;
//     printf( "%d\n", getLeafIndex( camera.p ) );
    Bitset &bitset = bsp->visual.bitsets[cluster];

    for( int i = 0; i < bsp->nLeafs; i++ ) {
      BSP::Leaf &leaf = bsp->leafs[i];

      if( ( cluster < 0 || bitset.get( leaf.cluster ) ) && frustum.isVisible( leaf + p ) ) {
        for( int j = 0; j < leaf.nFaces; j++ ) {
          int faceIndex = bsp->leafFaces[leaf.firstFace + j];

          if( !drawnFaces.get( faceIndex ) ) {
            drawFace( faceIndex );
            drawnFaces.set( faceIndex );
          }
        }
      }
    }
    glPopMatrix();
  }

  uint BSP_Dual::genList()
  {
    uint list = context.genList();

    glNewList( list, GL_COMPILE );

    drawnFaces = hiddenFaces;

    for( int i = 0; i < bsp->nLeafs; i++ ) {
      BSP::Leaf &leaf = bsp->leafs[i];

      for( int j = 0; j < leaf.nFaces; j++ ) {
        int faceIndex = bsp->leafFaces[leaf.firstFace + j];

        if( !drawnFaces.get( faceIndex ) ) {
          drawFace( faceIndex );
          drawnFaces.set( faceIndex );
        }
      }
    }
    glEndList();

    return list;
  }

  void BSP_Dual::beginRender()
  {
    glFrontFace( GL_CW );
    glActiveTexture( GL_TEXTURE1 );
    glEnable( GL_TEXTURE_2D );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
  }

  void BSP_Dual::endRender()
  {
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

    glDisable( GL_TEXTURE_2D );
    glActiveTexture( GL_TEXTURE0 );
    glFrontFace( GL_CCW );
  }

  void BSP_Dual::free()
  {
    if( textures != null ) {
      delete[] textures;
    }
    if( lightMaps != null ) {
      delete[] lightMaps;
    }
  }

}
