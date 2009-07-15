
#ifndef _LITH_PIXEL_H_
#define _LITH_PIXEL_H_

#include "stdtypes.h"

typedef u16 pixel_t,*ppixel_t;

#define RGB_SET(R,G,B)  (u16)(((R)<<11)|((G)<<5)|(B))
#define RGB_RED(C)		(u8)(((C)>>11)&31)
#define RGB_GREEN(C)	(u8)(((C)>> 5)&63)
#define RGB_BLUE(C)		(u8)(((C)>> 0)&31)
#define RGB_BLEND_MASK	0xF7DE
#define RGB_BLEND(A,B)	((((A) & RGB_BLEND_MASK) + ((B) & RGB_BLEND_MASK)) >> 1)

#include "fixed.h"
#define FPRGB(r,g,b)    (RGB_SET((r>>FPP),(g>>FPP),(b>>FPP)))

#endif // _LITH_PIXEL_H_