
#ifndef _LITH_MATHS_H_
#define _LITH_MATHS_H_

#include "stdtypes.h"
#include "fixed.h"

#include <math.h>

#define RECIPROCAL_MAX	256

#define FPRECIP(num)	(g_fpRecip[num])
#define FPSIN(angle)	(g_fpSin[angle])
#define FPCOS(angle)	(g_fpCos[angle])

extern const int g_fpRecip[RECIPROCAL_MAX];
extern const int g_fpSin[361];
extern const int g_fpCos[361];

int isqrt(int value);

#endif // _LITH_MATHS_H_