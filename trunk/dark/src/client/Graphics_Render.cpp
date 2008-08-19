/*
 *  Graphics_Render.cpp
 *
 *  Graphics render engine
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_Render.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "Graphics_Render.h"

#include "Matrix.h"
#include "Physics.h"

#include "Graphics_Frustum.h"
#include "Graphics_Shape.h"

#include "Graphics_Sky.h"
#include "Graphics_Water.h"
#include "Graphics_Terrain.h"
#include "Graphics_BSP.h"

#include "B_Goblin.h"

namespace Dark
{
namespace Graphics
{

  Render render;

  const float Render::RELEASED_CULL_FACTOR = 5.0;
  const float Render::INCH = 0.0252;

  const float Render::BLACK[] = { 0.0, 0.0, 0.0, 1.0 };
  const float Render::WHITE[] = { 1.0, 1.0, 1.0, 1.0 };

  const float Render::GLOBAL_AMBIENT[] = { 0.2, 0.2, 0.2, 1.0 };

  const float Render::NIGHT_FOG_COEFF = 2.0;
  const float Render::NIGHT_FOG_DIST = 0.3;

  void Render::init()
  {
    logFile.println( "OpenGL vendor: %s", glGetString( GL_VENDOR ) );
    logFile.println( "OpenGL version: %s", glGetString( GL_VERSION ) );
    logFile.println( "OpenGL extensions: %s", glGetString( GL_EXTENSIONS ) );

    font.init( "base/font.png", 2.0 );

    int screenX = atoi( config["screen.width"] );
    int screenY = atoi( config["screen.height"] );

    sscanf( config["render.perspective.angle"], "%f", &perspectiveAngle );
    sscanf( config["render.perspective.aspect"], "%f", &perspectiveAspect );
    sscanf( config["render.perspective.min"], "%f", &perspectiveMin );
    sscanf( config["render.perspective.max"], "%f", &perspectiveMax );

    if( perspectiveAspect == 0.0 ) {
      perspectiveAspect = (double) screenX / (double) screenY;
    }

    glViewport( 0, 0, screenX, screenY );
    glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( perspectiveAngle, perspectiveAspect, perspectiveMin, perspectiveMax );
    glMatrixMode( GL_MODELVIEW );

    glLoadIdentity();
    glRotatef( -90.0, 1.0, 0.0, 0.0 );

    glEnable( GL_TEXTURE_2D );

    font.print( -10, 0, "LOADING ..." );

    SDL_GL_SwapBuffers();
  }

  void Render::load()
  {
    context.init();

    glDepthFunc( GL_LEQUAL );
    glEnable( GL_CULL_FACE );

    // fog
    glFogi( GL_FOG_MODE, GL_LINEAR );
    glFogf( GL_FOG_START, 0.0 );
    glFogf( GL_FOG_END, perspectiveMax );

    // lighting
    glLightModeli(  GL_LIGHT_MODEL_TWO_SIDE, false );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, GLOBAL_AMBIENT );

    glEnable( GL_COLOR_MATERIAL );
    glColor4fv( WHITE );

    glEnable( GL_LIGHT0 );

    sscanf( config["render.particleRadius"], "%f", &particleRadius );
    drawAABBs   = config["render.drawAABBs"] == "1";
    showAim     = config["render.showAim"] == "1";
    blendHeaven = config["render.blendHeaven"] == "1";

    camera.init();
    frustum.init( perspectiveAngle, perspectiveAspect, perspectiveMax );
    sky.init();
    water.init();

    terra.init( context.loadTexture( "terra/map.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, false ),
                context.loadTexture( "terra/detail.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true ) );

    for( int i = 0; i < world.bsps.length(); i++ ) {
      BSP *bsp = new BSP( world.bsps[i] );

      bsps << bsp->genList();
      delete bsp;
    }

    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 0.01, 0.01, 0.01 ) ), 0 );
    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 10, 10, 10 ) ), 0 );

    lists << shape.genRandomTetrahedicParticle( 0.5 );

    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 0.3, 0.3, 0.3 ) ),
                           context.loadTexture( "tex/crate1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, false ) );
    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 0.6, 0.6, 0.6 ) ),
                           context.loadTexture( "tex/crate2.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, false ) );

    lists << MD2::genList( "md2/woodBarrel", INCH, Vec3( 0.0, 0.0, -0.482 ) );
    lists << MD2::genList( "md2/metalBarrel", INCH, Vec3( 0.0, 0.0, -0.5922 ) );

    lists << MD2::genList( "md2/tree2", 0.1, Vec3( 0.0, 0.0, -3.8 ) );
    lists << MD2::genList( "md2/tree3", 0.2, Vec3( 0.0, 0.0, -2.2 ) );

    md2s << new MD2();
    md2s.last()->load( "md2/goblin" );
    md2s.last()->scale( 0.03 );
    md2s.last()->translate( Vec3( 0.0, 0.0, 0.1 ) );
    md2s.last()->translate( ANIM_CROUCH_STAND, Vec3( 0.0, 0.0, 0.15 ) );
    md2s.last()->translate( ANIM_CROUCH_WALK, Vec3( 0.0, 0.0, 0.15 ) );

    md2s << new MD2();
    md2s.last()->load( "md2/knight" );
    md2s.last()->scale( 0.04 );

    // prepare for first frame
    glEnable( GL_DEPTH_TEST );

    glDisable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glEnable( GL_FOG );

    glEnable( GL_LIGHTING );
  }

  void Render::drawObject( Object *obj )
  {
    glPushMatrix();

    glTranslatef( obj->p.x, obj->p.y, obj->p.z );
    glRotatef( obj->rotZ, 0.0, 0.0, 1.0 );

    if( obj->type == WATER ) {
      waterObjects << obj;
    }
    else if( obj->alpha != 1.0 ) {
      blendedObjects << obj;
    }
    else if( obj->model >= 0 ) {
      glCallList( lists[obj->model] );
    }
    else {
      if( models.contains( (uint) obj ) ) {
        Model &model = models.cachedValue();

        model.state = Model::UPDATED;

        // draw model
        model.setAnim( obj->anim );
        md2s[model.model]->draw( &model.anim );
      }
      else {
        Model model( ~obj->model );

        model.state = Model::UPDATED;

        // generate & draw model
        model.setAnim( obj->anim );
        md2s[model.model]->draw( &model.anim );

        models.add( (uint) obj, model );
      }
    }
    if( drawAABBs ) {
      glRotatef( -obj->rotZ, 0.0, 0.0, 1.0 );

      glDisable( GL_LIGHTING );
      glDisable( GL_TEXTURE_2D );
      glEnable( GL_BLEND );
      glColor4f( 1.0, 1.0, 0.0, 0.3 );

      shape.drawBox( *obj );

      glColor4fv( WHITE );
      glDisable( GL_BLEND );
      glEnable( GL_TEXTURE_2D );
      glEnable( GL_LIGHTING );
    }
    glPopMatrix();
  }

  void Render::scheduleSector( int sectorX, int sectorY )
  {
    Sector &sector = world.sectors[sectorX][sectorY];

    for( int i = 0; i < sector.structures.length(); i++ ) {
      Structure *str = world.structures[ sector.structures[i] ];

      if( !drawnStructures.get( sector.structures[i] ) && frustum.isVisible( *str ) ) {
        drawnStructures.set( sector.structures[i] );
        structures << str;
      }
    }

    for( Object *obj = sector.objects.first(); obj != null; obj = obj->next[0] ) {
      if( obj == camera.player ) {
        continue;
      }
      bool isVisible =
          ( obj->flags & Object::RELEASED_CULL_BIT ) ?
          frustum.isVisible( *obj * RELEASED_CULL_FACTOR ) :
          frustum.isVisible( *obj );

      if( isVisible ) {
        if( obj->type == WATER && obj->includes( camera.p ) ) {
          isUnderWater = true;

          waterObjects << obj;
        }
        else if( obj->alpha != 1.0 ) {
          blendedObjects << obj;
        }
        else {
          objects << obj;
        }
      }
    }

    for( Particle *part = sector.particles.first(); part != null; part = part->next[0] ) {
      if( frustum.isVisible( part->p, particleRadius ) ) {
        particles << part;
      }
    }
  }

  void Render::draw()
  {
    // frustum
    frustum.update();
    frustum.getExtrems( camera.p );

    sky.update();
    water.update();

    bool wasUnderWater = isUnderWater;
    isUnderWater = false;

    // drawnStructures
    if( drawnStructures.length() != world.structures.length() ) {
      drawnStructures.setSize( world.structures.length() );
    }
    drawnStructures.clearAll();

    float minXCenter = (float) ( ( frustum.minX - World::MAX / 2 ) * Sector::DIM ) + Sector::DIM / 2.0;
    float minYCenter = (float) ( ( frustum.minY - World::MAX / 2 ) * Sector::DIM ) + Sector::DIM / 2.0;

    float x = minXCenter;
    for( int i = frustum.minX; i <= frustum.maxX; i++, x += Sector::DIM ) {
      float y = minYCenter;

      for( int j = frustum.minY; j <= frustum.maxY; j++, y += Sector::DIM ) {
        if( frustum.isVisible( x, y, Sector::RADIUS ) ) {
          scheduleSector( i, j );
        }
      }
    }

    // BEGIN RENDER
    if( isUnderWater ) {
      if( !wasUnderWater ) {
        glClearColor( water.COLOR[0], water.COLOR[1], water.COLOR[2], water.COLOR[3] );
        glFogfv( GL_FOG_COLOR, water.COLOR );
        glFogf( GL_FOG_END, Water::VISIBILITY );
      }
    }
    else {
      // we have to set this every time, since sky color changes all the time
      glClearColor( sky.color[0], sky.color[1], sky.color[2], sky.color[3] );
      glFogfv( GL_FOG_COLOR, sky.color );
      glFogf( GL_FOG_END,
              bound( NIGHT_FOG_COEFF * sky.lightDir[2], NIGHT_FOG_DIST, 1.0 ) * perspectiveMax );
    }
    // clear buffer
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    // camera transformation
    glMultMatrixf( camera.rotTMat );
    glTranslatef( -camera.p.x, -camera.p.y, -camera.p.z );

    // lighting
    glLightfv( GL_LIGHT0, GL_POSITION, sky.lightDir );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, sky.diffuseColor );
    glLightfv( GL_LIGHT0, GL_AMBIENT, sky.ambientColor );

    terra.draw();

    // draw structures
    BSP::beginRender();

    for( int i = 0; i < structures.length(); i++ ) {
      Structure *str = structures[i];

      glPushMatrix();
        glTranslatef( str->p.x, str->p.y, str->p.z );
        glCallList( bsps[str->bsp] );
      glPopMatrix();
    }
    structures.clear();

    BSP::endRender();

    // draw objects
    for( int i = 0; i < objects.length(); i++ ) {
      drawObject( objects[i] );
    }
    objects.clear();

    // draw particles
    glDisable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );

    for( int i = 0; i < particles.length(); i++ ) {
      Particle *part = particles[i];

      glPushMatrix();
        glTranslatef( part->p.x, part->p.y, part->p.z );

        glRotatef( part->rot.y, 0.0, 1.0, 0.0 );
        glRotatef( part->rot.x, 1.0, 0.0, 0.0 );
        glRotatef( part->rot.z, 0.0, 0.0, 1.0 );

        glColor4f( part->color.x, part->color.y, part->color.z, part->lifeTime );
        glCallList( lists[part->model] );
      glPopMatrix();
    }
    particles.clear();

    glColor4fv( WHITE );
    glEnable( GL_TEXTURE_2D );

    // draw transparent objects
    for( int i = 0; i < blendedObjects.length(); i++ ) {
      drawObject( blendedObjects[i] );
    }
    blendedObjects.clear();

    // draw water
    for( int i = 0; i < waterObjects.length(); i++ ) {
      water.draw( waterObjects[i], isUnderWater );
    }
    waterObjects.clear();

    glColor4fv( WHITE );
    glDisable( GL_BLEND );

    if( showAim ) {
      Vec3 move = camera.at * 1.0;
      collider.translate( camera.p, move );
      move *= collider.hit.ratio;

      glTranslatef( camera.p.x + move.x, camera.p.y + move.y, camera.p.z + move.z );

      glDisable( GL_TEXTURE_2D );
      glDisable( GL_LIGHTING );
      glColor3f( 0.0, 1.0, 0.0 );
      glCallList( lists[LIST_AIM] );
      glColor3fv( WHITE );
      glEnable( GL_TEXTURE_2D );
    }

    glLoadIdentity();
    glRotatef( -90.0, 1.0, 0.0, 0.0 );

    glDisable( GL_DEPTH_TEST );
    glDisable( GL_FOG );
    glDisable( GL_LIGHTING );

    glEnable( GL_BLEND );
    glBlendFunc( GL_ONE, GL_ONE );

    font.print( -45, 37, "cam( %.2f %.2f %.2f ) ( %.2f %.2f )",
                camera.p.x, camera.p.y, camera.p.z,
                camera.player->h, camera.player->v );
    font.print( -45, 35, "camera.player.vel ( %.2f %.2f %.2f )",
                camera.player->velocity.x, camera.player->velocity.y, camera.player->velocity.z );

    font.print( -45, 33, "l %d f %d ow %d iw %d ovlp %d",
                camera.player->lower >= 0,
                (bool) ( camera.player->flags & Object::ON_FLOOR_BIT ),
                (bool) ( camera.player->flags & Object::ON_WATER_BIT ),
                (bool) ( camera.player->flags & Object::UNDER_WATER_BIT ),
                collider.test( *camera.player ) );

    SDL_GL_SwapBuffers();

    // get ready for next frame
    glEnable( GL_DEPTH_TEST );

    glDisable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glEnable( GL_FOG );

    glEnable( GL_LIGHTING );

    // remove droped models
    for( HashIndex<Model, MODEL_HT_SIZE>::Iterator i( models ); !i.isPassed(); ) {
      Model &model = *i;
      uint key = i.key();

      // we should advance now, so that we don't remove the element the iterator is pointing at
      i.next();

      if( model.state == Model::NOT_UPDATED ) {
        models.remove( key );
      }
      else {
        model.state = Model::NOT_UPDATED;
      }
    }
  }

  void Render::free()
  {
    md2s.free();
    context.free();
  }

}
}
