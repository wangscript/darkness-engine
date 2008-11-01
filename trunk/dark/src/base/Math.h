/*
 *  Math.h
 *
 *  Replacement for math.h and some other utility functions
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_Math_h_
#define _Dark_Math_h_

namespace Dark
{

  class Math
  {
    private:

      Math();
      Math( const Math& );

    public:

      static const float FLOAT_EPS;
      static const float DOUBLE_EPS;
      static const float E;
      static const float LOG2E;
      static const float LOG10E;
      static const float LN2;
      static const float LN10;
      static const float PI;
      static const float PI_2;
      static const float PI_4;
      static const float _1_PI;
      static const float _2_PI;
      static const float _2_SQRTPI;
      static const float SQRT2;
      static const float SQRT1_2;
      static const float NaN;
      static const float INF;

      /*
       * Standard math functions
       */
      static float abs( float x )
      {
        return ::fabsf( x );
      }

      static float floor( float x )
      {
        return ::floorf( x );
      }

      static float ceil( float x )
      {
        return ::ceilf( x );
      }

      static float round( float x )
      {
        return ::roundf( x );
      }

      static float mod( float x, float y )
      {
        return ::fmodf( x, y );
      }

      static float sqrt( float x )
      {
        return ::sqrtf( x );
      }

      static float exp( float x )
      {
        return ::expf( x );
      }

      static float log( float x )
      {
        return ::logf( x );
      }

      static float pow( float x, float y )
      {
        return ::powf( x, y );
      }

      static float sin( float x )
      {
        return ::sinf( x );
      }

      static float cos( float x )
      {
        return ::cosf( x );
      }

      static void sincos( float x, float *s, float *c )
      {
        // FreeBSD libc doesn't have sincos function
#ifdef HAVE_SINCOS
          ::sincosf( x, s, c );
#else
          *s = ::sinf( x );
          *c = ::cosf( x );
#endif
      }

      static float tan( float x )
      {
        return ::tanf( x );
      }

      static float asin( float x )
      {
        return ::asinf( x );
      }

      static float acos( float x )
      {
        return ::acosf( x );
      }

      static float atan( float x )
      {
        return ::atanf( x );
      }

      static float atan2( float x, float y )
      {
        return ::atan2f( x, y );
      }

      /*
       * Some additional functions
       */

      // returns true, if value is not a number
      static bool isNAN( float x )
      {
        return isnanf( x );
      }

      static float sgn( float x )
      {
        return x < 0.0f ? -1.0f : x > 0.0f ? 1.0f : 0.0f;
      }

      // deg-to-rad and rad-to-deg conversion
      static float rad( float x )
      {
        return x * ( PI / 180.0f );
      }

      static float deg( float x )
      {
        return x * ( _1_PI * 180.0f );
      }

      // random integer from 0 to RAND_MAX
      static int rand()
      {
        return ::rand();
      }

      // random float from interval [0, 1]
      static float frand()
      {
        return (float) ::rand() / (float) RAND_MAX;
      }

  };

}

#endif // _Dark_Math_h_
