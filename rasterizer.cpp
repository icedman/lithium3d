
#include "rasterizer.h"

void RasterizerInit(rasterizer_t& r,pframebuffer_t target)
{
	r.renderTarget=target;
	r.textureSource=NULL;
	r.palette=NULL;	
}

