/*
 *  Graphics_SparkGen.cpp
 *
 *  Visual particle generator
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_SparkGen.cpp 11 2007-08-31 12:03:10Z davorin $
 */

#include "precompiled.h"

#include "Graphics_SparkGen.h"

namespace Dark
{
namespace Graphics
{

//   SparkGen::SparkGen( Dark::SparkGen *sparkGen_ ) : sparkGen( sparkGen_ )
//   {
//     sparks = new Spark[sparkGen->number];
//
//     for( int i = 0; i < sparkGen->number; i++ ) {
//       float spread2 = sparkGen->spread * 0.5f;
//       Vec3 velDisturb = Vec3( sparkGen->spread * Math::frand() - spread2, sparkGen->spread * Math::frand() - spread2,
//                               sparkGen->spread * Math::frand() - spread2 );
//
//       Vec3 colorDisturb = Vec3( sparkGen->colorSpread.x * Math::frand(), sparkGen->colorSpread.y * Math::frand(),
//                                 sparkGen->colorSpread.z * Math::frand() );
//
//       float timeDisturb = sparkGen->lifeTime * Math::frand();
//
//       sparks[i].p = sparkGen->p;
//       sparks[i].velocity = sparkGen->velocity + velDisturb;
//       sparks[i].color = sparkGen->color + colorDisturb;
//       sparks[i].lifeTime = 0.5 * sparkGen->lifeTime + timeDisturb;
//     }
//   }
//
//   SparkGen::~SparkGen()
//   {
//     delete[] sparks;
//   }
//
//   // TODO: spark rendering
//   void SparkGen::draw()
//   {
//   }
//
//   void SparkGen::update() {
//     for( int i = 0; i < sparkGen->number; i++ ) {
//       sparks[i].lifeTime -= timer.frameTime;
//
//       if( sparks[i].lifeTime < 0.0f ) {
//         float spread2 = sparkGen->spread * 0.5f;
//         Vec3 velDisturb = Vec3( sparkGen->spread * Math::frand() - spread2,
//                                 sparkGen->spread * Math::frand() - spread2,
//                                 sparkGen->spread * Math::frand() - spread2 );
//
//         float timeDisturb = sparks[i].lifeTime * Math::frand();
//
//         sparks[i].p = sparkGen->p;
//         sparks[i].velocity = sparkGen->velocity + velDisturb;
//         sparks[i].lifeTime = 0.5f * sparkGen->lifeTime + timeDisturb;
//       }
//     }
//   }

}
}
