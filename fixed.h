
#ifndef _LITH_FIXED_H_
#define _LITH_FIXED_H_

#include "stdtypes.h"

typedef s32 fixed;

#define FPMUL(x,y)		((((x)>>6)*((y)>>6))>>4)	// multiply fixed by fixed. returns fixed
#define FPMULH(x,y)		((((x)>>2)*((y)>>2))>>12)	// higher precision
#define FPDIV(x,y)		((((x)<<6)/((y)>>6))<<4)	// divide fixed by fixed. returns fixed
#define FPONE			65536
#define FPP				16
#define FPI(x)			((x)<<FPP)					// convert int to fixed
#define FPFL(x)			((int)(x * FPONE))			// convert float to fixed
#define FPABS(n)		(n - ((n+n) & (n>>31)))
#define FEPSILON		1							// near zero fixed

#endif // _LITH_FIXED_H_