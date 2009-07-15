
#ifndef _LITH_RASTERIZER_H_
#define _LITH_RASTERIZER_H_

#include "framebuffer.h"
#include "textures.h"

typedef struct {	
	pframebuffer_t renderTarget;
	ptexture_t	textureSource;
	ppalette_t	palette;
} rasterizer_t, *prasterizer_t;

void RasterizerInit(rasterizer_t& r,pframebuffer_t target);

#endif // _LITH_RASTERIZER_H_