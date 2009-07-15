
#ifndef _LITH_FRAMEBUFFER_H_
#define _LITH_FRAMEBUFFER_H_

#include "stdtypes.h"
#include "pixel.h"

typedef struct {
    ppixel_t pixels;		// pixel linear data
    u16 pitch;				// pitch (y-increment)
    u16 width;
    u16 height;
} framebuffer_t, *pframebuffer_t;

#endif // _LITH_FRAMEBUFFER_H_