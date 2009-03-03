/*
 *  Render.cpp
 *
 *  Graphics render engine
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Render.h"

#include "matrix/Matrix.h"
#include "matrix/Physics.h"
#include "matrix/B_Goblin.h"
#include "matrix/Translator.h"

#include "Frustum.h"
#include "Shape.h"

#include "Sky.h"
#include "Water.h"
#include "Terrain.h"
#include "BSP.h"

namespace oz
{
namespace Client
{

  Render render;

  const float Render::RELEASED_CULL_FACTOR = 5.0f;
  const float Render::INCH = 0.0252f;

  const float Render::BLACK[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  const float Render::WHITE[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  const float Render::GLOBAL_AMBIENT[] = { 0.2f, 0.2f, 0.2f, 1.0f };

  const float Render::NIGHT_FOG_COEFF = 2.0f;
  const float Render::NIGHT_FOG_DIST = 0.3f;

  void Render::init()
  {
    logFile.println( "OpenGL vendor: %s", glGetString( GL_VENDOR ) );
    logFile.println( "OpenGL version: %s", glGetString( GL_VERSION ) );
    logFile.println( "OpenGL extensions: %s", glGetString( GL_EXTENSIONS ) );

    font.init( "base/font.png", 2.0f );

    int screenX = atoi( config["screen.width"] );
    int screenY = atoi( config["screen.height"] );

    sscanf( config["render.perspective.angle"], "%f", &perspectiveAngle );
    sscanf( config["render.perspective.aspect"], "%f", &perspectiveAspect );
    sscanf( config["render.perspective.min"], "%f", &perspectiveMin );
    sscanf( config["render.perspective.max"], "%f", &perspectiveMax );

    if( perspectiveAspect == 0.0f ) {
      perspectiveAspect = (float) screenX / (float) screenY;
    }

    glViewport( 0, 0, screenX, screenY );
    glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( perspectiveAngle, perspectiveAspect, perspectiveMin, perspectiveMax );
//       gluPerspective( 150, perspectiveAspect, perspectiveMin, perspectiveMax );
    glMatrixMode( GL_MODELVIEW );

    glLoadIdentity();
    glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );

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
    glFogf( GL_FOG_START, 0.0f );
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
      bsps << new BSP( world.bsps[i] );
    }

    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 0.01f, 0.01f, 0.01f ) ), 0 );
    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 10, 10, 10 ) ), 0 );

    lists << shape.genRandomTetrahedicParticle( 0.5f );

    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 0.3f, 0.3f, 0.3f ) ),
                           context.loadTexture( "tex/crate1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, false ) );
    lists << shape.genBox( AABB( Vec3::zero(), Vec3( 0.6f, 0.6f, 0.6f ) ),
                           context.loadTexture( "tex/crate2.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, false ) );

    lists << MD2::genList( "md2/woodBarrel", INCH, Vec3( 0.0f, 0.0f, -0.482f ) );
    lists << MD2::genList( "md2/metalBarrel", INCH, Vec3( 0.0f, 0.0f, -0.5922f ) );

    lists << MD2::genList( "md2/tree2", 0.1f, Vec3( 0.0f, 0.0f, -3.8f ) );
    lists << MD2::genList( "md2/tree3", 0.2f, Vec3( 0.0f, 0.0f, -2.2f ) );

    md2s << new MD2();
    md2s.last()->load( "md2/goblin" );
    md2s.last()->scale( 0.03f );
    md2s.last()->translate( Vec3( 0.0f, 0.0f, 0.1f ) );
    md2s.last()->translate( ANIM_CROUCH_STAND, Vec3( 0.0f, 0.0f, 0.15f ) );
    md2s.last()->translate( ANIM_CROUCH_WALK, Vec3( 0.0f, 0.0f, 0.15f ) );

    md2s << new MD2();
    md2s.last()->load( "md2/knight" );
    md2s.last()->scale( 0.04f );

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
    glRotatef( obj->rotZ, 0.0f, 0.0f, 1.0f );

    if( obj->flags & Object::WATER_BIT ) {
      waterObjects << obj;
    }
    else if( obj->alpha != 1.0f ) {
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
        models.add( (uint) obj, Model( ~obj->model ) );

        Model &model = models.cachedValue();

        model.state = Model::UPDATED;

        // generate & draw model
        model.setAnim( obj->anim );
        md2s[model.model]->draw( &model.anim );
      }
    }
    if( drawAABBs ) {
      glRotatef( -obj->rotZ, 0.0f, 0.0f, 1.0f );

      glDisable( GL_LIGHTING );
      glDisable( GL_TEXTURE_2D );
      glEnable( GL_BLEND );
      glColor4f( 1.0f, 1.0f, 0.0f, 0.3f );

      shape.drawBox( *obj );

      glColor4fv( WHITE );
      glDisable( GL_BLEND );
      glEnable( GL_TEXTURE_2D );
      glEnable( GL_LIGHTING );
    }
    glPopMatrix();
  }

  void Render::drawSparkGen( SparkGen *sparkGen )
  {
    if( sparkGenRenders.contains( (uint) sparkGen ) ) {
      // spark generator is registered
      SparkGenRender &sparkGenRender = sparkGenRenders.cachedValue();

      sparkGenRender.state = SparkGenRender::UPDATED;
      // draw spars
      sparkGenRender.draw();
    }
    else {
      // spark generator is not registered, we need to create a new renderer for it
      sparkGenRenders.add( (uint) sparkGen, SparkGenRender( sparkGen ) );

      SparkGenRender &sparkGenRender = sparkGenRenders.cachedValue();

      sparkGenRender.state = SparkGenRender::UPDATED;
      // draw spars
      sparkGenRender.draw();
    }
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
        if( ( obj->flags & Object::WATER_BIT ) && obj->includes( camera.p ) ) {
          isUnderWater = true;

          waterObjects << obj;
        }
        else if( obj->alpha != 1.0f ) {
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

    float minXCenter = (float) ( ( frustum.minX - World::MAX / 2 ) * Sector::DIM ) + Sector::DIM / 2.0f;
    float minYCenter = (float) ( ( frustum.minY - World::MAX / 2 ) * Sector::DIM ) + Sector::DIM / 2.0f;

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
              bound( NIGHT_FOG_COEFF * sky.lightDir[2], NIGHT_FOG_DIST, 1.0f ) * perspectiveMax );
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

      bsps[str->bsp]->draw( str->p );
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

        glRotatef( part->rot.y, 0.0f, 1.0f, 0.0f );
        glRotatef( part->rot.x, 1.0f, 0.0f, 0.0f );
        glRotatef( part->rot.z, 0.0f, 0.0f, 1.0f );

        glColor4f( part->color.x, part->color.y, part->color.z, part->lifeTime );
        glCallList( LIST_SPARK );
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

    for( int i = 0; i < sparkGens.length(); i++ ) {
      drawSparkGen( sparkGens[i] );
    }
    sparkGens.clear();

    // draw water
    for( int i = 0; i < waterObjects.length(); i++ ) {
      water.draw( waterObjects[i], isUnderWater );
    }
    waterObjects.clear();

    glColor4fv( WHITE );
    glDisable( GL_BLEND );

    if( showAim ) {
      Vec3 move = camera.at * 1.0f;
      collider.translate( camera.p, move );
      move *= collider.hit.ratio;

      glTranslatef( camera.p.x + move.x, camera.p.y + move.y, camera.p.z + move.z );

      glDisable( GL_TEXTURE_2D );
      glDisable( GL_LIGHTING );
      glColor3f( 0.0f, 1.0f, 0.0f );
      glCallList( lists[LIST_AIM] );
      glColor3fv( WHITE );
      glEnable( GL_TEXTURE_2D );
    }

    glLoadIdentity();
    glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );

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
                ( camera.player->flags & Object::ON_FLOOR_BIT ) != 0,
                ( camera.player->flags & Object::ON_WATER_BIT ) != 0,
                ( camera.player->flags & Object::UNDER_WATER_BIT ) != 0,
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
      i++;

      if( model.state == Model::NOT_UPDATED ) {
        models.remove( key );
      }
      else {
        model.state = Model::NOT_UPDATED;
      }
    }

    // remove droped spark renderers
    for( HashIndex<SparkGenRender, SPARKGENRENDER_HT_SIZE>::Iterator i( sparkGenRenders );
         !i.isPassed(); )
    {
      SparkGenRender &sparkGenRender = *i;
      uint key = i.key();

      // we should advance now, so that we don't remove the element the iterator is pointing at
      i++;

      if( sparkGenRender.state == SparkGenRender::NOT_UPDATED ) {
        sparkGenRenders.remove( key );
      }
      else {
        sparkGenRender.state = SparkGenRender::NOT_UPDATED;
      }
    }
  }

  void Render::free()
  {
    models.clear();
    sparkGenRenders.clear();

    models.clear();
    md2s.free();
    bsps.free();
    context.free();

//     models.deallocate();
  }

}
}
