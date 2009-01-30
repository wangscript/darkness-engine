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

#pragma once

#ifdef WIN32
# define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>

/*
 * Basic definitons and template functions
 */
#include "common.h"

/*
 * Containers
 */
#include "List.h"
#include "DList.h"

#include "Vector.h"
#include "SVector.h"
#include "Pool.h"

/*
 * String
 */
#include "String.h"

/*
 * Reuser base class for improved memory management (reusing freed blocks)
 */
#include "Reuser.h"

/*
 * Containers 2
 */
#include "HashIndex.h"
#include "HashString.h"

/*
 * Bitset
 */
#include "Bitset.h"

/*
 * Math
 */
#include "Math.h"

#include "Vec3.h"
#include "Quat.h"
#include "Mat33.h"
#include "Mat44.h"

/*
 * Utilities
 */
#include "LogFile.h"
#include "Config.h"
