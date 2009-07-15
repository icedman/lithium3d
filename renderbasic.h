
#ifndef _LITH_RENDER_BASIC_H_
#define _LITH_RENDER_BASIC_H_

#include "framebuffer.h"

void RenderClear(pframebuffer_t buffer,pixel_t color);
void RenderDither(pframebuffer_t buffer);
void RenderDitherInterlace(pframebuffer_t buffer);
void RenderFillInterlace(pframebuffer_t buffer);

pixel_t RenderGetPixel(pframebuffer_t buffer,int x,int y);
void RenderPixel(pframebuffer_t buffer,int x,int y,pixel_t color);
void RenderLine(pframebuffer_t buffer,int x,int y,int x2,int y2,pixel_t color);
void RenderHLine(pframebuffer_t buffer,int x,int y,int w,pixel_t color);
void RenderVLine(pframebuffer_t buffer,int x,int y,int h,pixel_t color);

#endif // _LITH_RENDER_BASIC_H_