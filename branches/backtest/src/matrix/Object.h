/*
 *  Object.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "bv.h"
#include "Hit.h"
#include "Sound.h"
#include "Translator.h"

namespace Dark
{

  struct Sector;
  class Matrix;

  // static object abstract class
  class Object : public AABB
  {
    protected:

      /*
       *  FUNCTION FLAGS
       */

      // if the update method should be called each step
      static const int UPDATE_FUNC_BIT = 0x80000000;

      // if the "use" method is called when we want to use the object (otherwise, nothing happens)
      static const int USE_FUNC_BIT = 0x40000000;

      // if the hit function should be called on hit
      static const int HIT_FUNC_BIT = 0x20000000;

      // (DynObject) if the xxxFriction should be invoked on friction begin or end
      static const int FRICT_FUNC_BIT = 0x10000000;

      // if object is currently fricting
      static const int FRICTING_BIT = 0x08000000;

    public:

      /*
       *  DYNAMIC OBJECTS' BITS
       */

      // if the object is dynamic
      static const int DYNAMIC_BIT = 0x00800000;

      // if object is still and on surface, we won't handle physics for it
      static const int DISABLED_BIT = 0x00400000;

      // handle collisions for this object
      static const int CLIP_BIT = 0x00200000;

      // if the object is immune to gravity
      static const int HOVER_BIT = 0x00100000;

      // if object can push other objects in orthogonal direction of collision normal
      static const int PUSHING_BIT = 0x00080000;

      // if the object lies or moves on a structure, terrain on non-dynamic object
      // (if on another dynamic object, we determine that with "lower" index)
      static const int ON_FLOOR_BIT = 0x00040000;

      // if object intersects with water (this bit is cleared every update)
      static const int ON_WATER_BIT = 0x00020000;

      // if object center is in water (this bit is cleared every update)
      static const int UNDER_WATER_BIT = 0x00010000;

      // if object intersects with water (cleared when comes out of water)
      static const int IN_WATER_BIT = 0x00008000;

      // if object can climb
      static const int CLIMBER_BIT = 0x00004000;

      // if object is on ladder (this bit is cleared every ipdate)
      static const int ON_LADDER_BIT = 0x00002000;

      // if object is on ladder (cleared when goes off the ladder)
      static const int CLIMBING_LADDER_BIT = 0x00001000;

    public:

      static const int BOT_BIT = 0x00000080;
      static const int WATER_BIT = 0x00000040;
      static const int SPARKGEN_BIT = 0x00000020;

      /*
       *  RENDER FLAGS
       */

      // released frustum culling: object is represented some times larger to frustum culling
      // system than it really is;
      // how larger it is, is specified by Client::Render::RELEASED_CULL_FACTOR
      static const int RELEASED_CULL_BIT = 0x00000001;

      // determines visibility of the object for rendering
      // (e.g. ghosts are visible by other spirits, but not by alive units)
      static const int SPIRIT_BIT = 0x00000002;

      /*
       *  FIELDS
       */

      int     index;        // position in world.objects vector
      Sector  *sector;      // parent sector, null if not positioned in the world

      Object  *prev[1];     // previous object in sector.objects list
      Object  *next[1];     // next object in sector.objects list

      int     flags;
      int     type;

      // damage
      float   damage;

      // graphics data
      int     model;
      int     anim;

      float   rotZ;
      float   alpha;

      // once played sounds
      List<Sound, 0> sounds;
      // continous sounds
      List<Sound, 0> contSounds;

    protected:

      virtual void onUpdate()
      {}

      virtual void onUse( Object *user )
      {
        user = null;
      }

      virtual void onHit( const Hit *hit )
      {
        hit = null;
      }

      virtual void onDestroy()
      {}

    public:

      Object() : index( -1 ), sector( null ), flags( 0 ), type( -1 ),
          damage( Math::INF ), model( 0 ), anim( 0 ), rotZ( 0.0f ), alpha( 1.0f )
      {}

      virtual ~Object()
      {
        assert( dim.x <= AABB::REAL_MAX_DIMXY );
        assert( dim.y <= AABB::REAL_MAX_DIMXY );

        sounds.free();
        contSounds.free();
      }

      void update()
      {
        cleanSounds();

        if( flags & UPDATE_FUNC_BIT ) {
          onUpdate();
        }
      }

      void use( Object *user )
      {
        if( flags & USE_FUNC_BIT ) {
          onUse( user );
        }
      }

      void hit( const Hit *hit )
      {
        if( flags & HIT_FUNC_BIT ) {
          onHit( hit );
        }
      }

      void destroy()
      {
        onDestroy();
      }

      void addSound( SoundEnum sound )
      {
        sounds << new Sound( sound );
      }

      void cleanSounds()
      {
        sounds.free();
      }

      void addContSound( SoundEnum sound )
      {
        contSounds << new Sound( sound );
      }

      void removeContSound( SoundEnum sound )
      {
        Sound *prev = null;
        Sound *p = contSounds.first();

        while( p != null ) {
          if( p->sample == sound ) {
            Sound *next = p->next[0];

            contSounds.remove( p, prev );
            delete p;

            p = next;
          }
          else {
            prev = p;
            p = p->next[0];
          }
        }
      }

      void cleanContSounds()
      {
        contSounds.free();
      }

      /*
       *  SERIALIZATION
       */

      void load( FILE *stream );
      void save( FILE *stream );
  };

}
