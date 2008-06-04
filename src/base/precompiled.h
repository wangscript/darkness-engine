/*
 *  precompiled.h
 *
 *  Common include file. Should not be directly included. Include "base.h" instead.
 *  Warning: DOES NOT WORK with "-g3" gcc flag. Use -g instead.
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: precompiled.h 11 2007-08-31 12:03:10Z davorin $
 */

// defining NDEBUG disables assert macro
// #define NDEBUG

#define DARK_FLOAT_SCALAR 1

#include <assert.h>
#include <stdlib.h>
#include <math.h>

/*
 *  Basic definitons and template functions
 */
#include "common.h"

/*
 *  Reuser base class for improved memory management (reusing freed blocks)
 */
#include "Reuser.h"

/*
 *  Containers
 */
#include "Vector.h"
#include "SVector.h"

#include "List.h"
#include "DList.h"

/*
 *  String
 */
#include "String.h"

/*
 *  Containers 2
 */
#include "Bitset.h"
#include "HashIndex.h"
#include "HashString.h"

/*
 *  Math
 */
#include "Math.h"

#include "Vec3.h"
#include "Quat.h"
#include "Mat33.h"
#include "Mat44.h"

/*
 *  Utilities
 */
#include "LogFile.h"
#include "Config.h"
