/*
 *  BSP.cpp
 *
 *  BSP level rendering class
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "BSP.h"

#include "matrix/BSP.h"
#include "Frustum.h"

#ifdef __WIN32__
static PFNGLACTIVETEXTUREPROC glActiveTexture = null;
static PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = null;
#endif

namespace Dark
{
namespace Client
{

  BSP::BSP()
  {}

  BSP::BSP( Dark::BSP *bsp )
  {
    textures = null;
    lightMaps = null;

    init( bsp );
  }

  BSP::~BSP()
  {
    free();
  }

  int BSP::getLeafIndex( const Vec3 &p ) const
  {
    int nodeIndex = 0;

    do {
      const Dark::BSP::Node  &node  = bsp->nodes[nodeIndex];
      const Dark::BSP::Plane &plane = bsp->planes[node.plane];

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

  void BSP::drawFace( int faceIndex ) const
  {
    Dark::BSP::Face &face = bsp->faces[faceIndex];

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, sizeof( Dark::BSP::Vertex ),
                     (float*) bsp->vertices[face.firstVertex].p );

    glActiveTexture( GL_TEXTURE0 );
    glClientActiveTexture( GL_TEXTURE0 );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );

    glBindTexture( GL_TEXTURE_2D, textures[face.texture] );
    glTexCoordPointer( 2, GL_FLOAT, sizeof( Dark::BSP::Vertex ),
                       bsp->vertices[face.firstVertex].texCoord );

    glActiveTexture( GL_TEXTURE1 );
    glClientActiveTexture( GL_TEXTURE1 );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );

    glBindTexture( GL_TEXTURE_2D, lightMaps[face.lightmap] );
    glTexCoordPointer( 2, GL_FLOAT, sizeof( Dark::BSP::Vertex ),
                       bsp->vertices[face.firstVertex].lightmapCoord );

    glNormal3fv( face.normal );
    glDrawElements( GL_TRIANGLES, face.nIndices, GL_UNSIGNED_INT, &bsp->indices[face.firstIndex] );
  }

  void BSP::init( Dark::BSP *bsp_ )
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
      if( bsp->textures[i] >= 0 ) {
        textures[i] = context.loadTexture( translator.textures[ bsp->textures[i] ],
                                           GL_LINEAR,
                                           GL_LINEAR_MIPMAP_LINEAR,
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
                                            GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true );
    }

    hiddenFaces.setSize( bsp->nFaces );
    visibleLeafs.setSize( bsp->visual.bitsets[0].length() );
    drawnFaces.setSize( bsp->nFaces );
    hiddenFaces.clearAll();

    baseList = context.genLists( bsp->nFaces );
    for( int i = 0; i < bsp->nFaces; i++ ) {
      Dark::BSP::Vertex *verts = &bsp->vertices[ bsp->faces[i].firstVertex ];

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

  void BSP::draw( const Vec3 &p )
  {
    glPushMatrix();
    glTranslatef( p.x, p.y, p.z );

    drawnFaces = hiddenFaces;

    int    cluster = bsp->leafs[ getLeafIndex( camera.p ) ].cluster;
//     printf( "%d\n", getLeafIndex( camera.p ) );
    Bitset &bitset = bsp->visual.bitsets[cluster];

    for( int i = 0; i < bsp->nLeafs; i++ ) {
      Dark::BSP::Leaf &leaf = bsp->leafs[i];

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

  uint BSP::genList()
  {
    uint list = context.genList();

    glNewList( list, GL_COMPILE );

    drawnFaces = hiddenFaces;

    for( int i = 0; i < bsp->nLeafs; i++ ) {
      Dark::BSP::Leaf &leaf = bsp->leafs[i];

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

  void BSP::beginRender()
  {
    glFrontFace( GL_CW );
    glActiveTexture( GL_TEXTURE1 );
    glEnable( GL_TEXTURE_2D );
  }

  void BSP::endRender()
  {
    glDisable( GL_TEXTURE_2D );
    glActiveTexture( GL_TEXTURE0 );
    glFrontFace( GL_CCW );
  }

  void BSP::free()
  {
    if( textures != null ) {
      delete[] textures;
    }
    if( lightMaps != null ) {
      delete[] lightMaps;
    }
  }

}
}
