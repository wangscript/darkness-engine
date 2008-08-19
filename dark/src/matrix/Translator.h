/*
 *  Translator.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Translator_h_
#define _Translator_h_

namespace Dark
{

  enum ListEnum
  {
    LIST_AIM,
    LIST_WATER,
    LIST_SPARK,
    LIST_SMALL_CRATE,
    LIST_BIG_CRATE,
    LIST_WOOD_BARREL,
    LIST_METAL_BARREL,
    LIST_TREE1,
    LIST_TREE2
  };

  enum ModelEnum
  {
    MODEL_GOBLIN
  };

  enum AnimEnum
  {
    ANIM_STAND,
    ANIM_RUN,
    ANIM_ATTACK,
    ANIM_PAIN_A,
    ANIM_PAIN_B,
    ANIM_PAIN_C,
    ANIM_JUMP,
    ANIM_FLIP,
    ANIM_SALUTE,
    ANIM_FALLBACK,
    ANIM_WAVE,
    ANIM_POINT,
    ANIM_CROUCH_STAND,
    ANIM_CROUCH_WALK,
    ANIM_CROUCH_ATTACK,
    ANIM_CROUCH_PAIN,
    ANIM_CROUCH_DEATH,
    ANIM_DEATH_FALLBACK,
    ANIM_DEATH_FALLFORWARD,
    ANIM_DEATH_FALLBACKSLOW,
    ANIM_MAX
  };

  enum ObjectEnum
  {
    WATER,
    LADDER,

    O_TREE1,
    O_TREE2,

    D_SMALL_CRATE,
    D_BIG_CRATE,
    D_WOOD_BARREL,
    D_METAL_BARREL,

    ITEM_BEGIN,
    ITEM_END,

    WEAPON_BEGIN,
    WEAPON_END,

    BOT_BEGIN,
    B_SPIRIT,
    B_HUMAN,
    B_GOBLIN,
    BOT_END
  };

  enum SoundEnum
  {
    SND_FRICTION_SOFT,
    SND_FRICTION_HARD,
    SND_HIT_SOFT,
    SND_HIT_HARD,
    SND_SPLASH_SOFT,
    SND_SPLASH_HARD,
    SND_LAND,
    SND_JUMP,

    SND_MAX
  };

  class Translator
  {
    protected:

      HashString<int, 256> textureIndices;

    public:

      static const char * const textures[];
      static const char * const sounds[];

      int nTextures;
      int getTexture( const char *name );

      Translator();
  };

  extern Translator translator;

}

#endif // _Translator_h_
