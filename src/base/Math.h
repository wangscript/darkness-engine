/*
 *  Math.h
 *
 *  Replacement for math.h and some other utility functions
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Math.h 11 2007-08-31 12:03:10Z davorin $
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

      static const scalar FLOAT_EPS;
      static const scalar DOUBLE_EPS;
      static const scalar E;
      static const scalar LOG2E;
      static const scalar LOG10E;
      static const scalar LN2;
      static const scalar LN10;
      static const scalar PI;
      static const scalar PI_2;
      static const scalar PI_4;
      static const scalar _1_PI;
      static const scalar _2_PI;
      static const scalar _2_SQRTPI;
      static const scalar SQRT2;
      static const scalar SQRT1_2;
      static const scalar NaN;
      static const scalar INF;

      static void init();

      /*
       * Standard math functions
       */
      static scalar abs( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::fabsf( x );
#else
        return ::fabs( x );
#endif
      }

      static scalar floor( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::floorf( x );
#else
        return ::floor( x );
#endif
      }

      static scalar ceil( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::ceilf( x );
#else
        return ::ceil( x );
#endif
      }

      static scalar round( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::roundf( x );
#else
        return ::round( x );
#endif
      }

      static scalar mod( scalar x, scalar y )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::fmodf( x, y );
#else
        return ::fmod( x, y );
#endif
      }

      static scalar sqrt( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::sqrtf( x );
#else
        return ::sqrt( x );
#endif
      }

      static scalar exp( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::expf( x );
#else
        return ::exp( x );
#endif
      }

      static scalar log( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::logf( x );
#else
        return ::log( x );
#endif
      }

      static scalar pow( scalar x, scalar y )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::powf( x, y );
#else
        return ::pow( x, y );
#endif
      }

      static scalar sin( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::sinf( x );
#else
        return ::sin( x );
#endif
      }

      static scalar cos( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::cosf( x );
#else
        return ::cos( x );
#endif
      }

      static void sincos( scalar x, scalar *s, scalar *c )
      {
        // FreeBSD libc doesn't have sincos function
#ifdef HAVE_SINCOS

#ifdef DARK_FLOAT_SCALAR
          ::sincosf( x, s, c );
#else
          ::sincos( x, s, c );
#endif

#else

#ifdef DARK_FLOAT_SCALAR
          *s = ::sinf( x );
          *c = ::cosf( x );
#else
          *s = ::sin( x );
          *c = ::cos( x );
#endif

#endif
      }

      static scalar tan( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::tanf( x );
#else
        return ::tan( x );
#endif
      }

      static scalar asin( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::asinf( x );
#else
        return ::asin( x );
#endif
      }

      static scalar acos( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::acosf( x );
#else
        return ::acos( x );
#endif
      }

      static scalar atan( scalar x )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::atanf( x );
#else
        return ::atan( x );
#endif
      }

      static scalar atan2( scalar x, scalar y )
      {
#ifdef DARK_FLOAT_SCALAR
        return ::atan2f( x, y );
#else
        return ::atan2( x, y );
#endif
      }

      /*
       * Some additional functions
       */

      // returns true, if value is not a number
      static bool isNAN( scalar x )
      {
#if defined( DARK_FLOAT_SCALAR ) && !defined( __WIN32__ )
        return isnanf( x );
#else
        return isnan( x );
#endif
      }

      static scalar sgn( scalar x )
      {
        return x < 0 ? -1.0 : x > 0 ? 1.0 : 0.0;
      }

      // deg-to-rad and rad-to-deg conversion
      static scalar rad( scalar x )
      {
        return x * ( PI / 180.0 );
      }

      static scalar deg( scalar x )
      {
        return x * ( _1_PI * 180.0 );
      }

      // random integer from 0 to RAND_MAX
      static int rand()
      {
        return ::rand();
      }

      // random scalar from interval [0, 1]
      static scalar frand()
      {
        return (scalar) ::rand() / (scalar) RAND_MAX;
      }

  };

}

#endif // _Dark_Math_h_
