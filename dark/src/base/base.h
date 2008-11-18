/*
 *  base.h
 *
 *  Common include file.
 *  It is included in "precompiled.h", so include the latter instead of this file for faster
 *  compiling.
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_base_h_
#define _Dark_base_h_

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>

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

#endif // _Dark_base_h_
