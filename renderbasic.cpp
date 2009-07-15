
#include "renderbasic.h"
#include "utils.h"
#include "fixed.h"

void RenderClear(pframebuffer_t buffer,pixel_t color)
{
	u32 c=(color << 16) | color;
	pixel_t *pDest=buffer->pixels;
	int i=buffer->height;
	while(i>0) {
		MemSetDWord((u32*)pDest,c,buffer->width);
		pDest+=(buffer->pitch>>1);
		i--;
	}
}

void RenderDither(pframebuffer_t buffer)
{
	pixel_t *pDest=buffer->pixels;
	for (int y=0;y<(buffer->height>>1);y++) {
		for (int x=0;x<buffer->width;x+=3) {
			pDest[x+1]=RGB_BLEND(pDest[x],pDest[x+2]);
		}
		pDest+=buffer->pitch;
	}
}

void RenderDitherInterlace(pframebuffer_t buffer)
{
	u32 *pDest=(u32*)buffer->pixels+(buffer->pitch>>2);
	u32 *pSrc1=(u32*)buffer->pixels;
	u32 *pSrc2=(u32*)buffer->pixels+(buffer->pitch>>1);
	u32 c;
	for (int y=0;y<(buffer->height>>1);y++) {
		for (int x=0;x<(buffer->width>>1);x++) {
			c=RGB_BLEND((pSrc1[x]>>16),pSrc2[x]);
			pDest[x]=((c<<16) | c);
		}
		pDest+=(buffer->pitch>>1);
		pSrc1+=(buffer->pitch>>1);
		pSrc2+=(buffer->pitch>>1);
	}
}

void RenderFillInterlace(pframebuffer_t buffer)
{
	u32 *pDest=(u32*)buffer->pixels+(buffer->pitch>>2);
	u32 *pSrc=(u32*)buffer->pixels;
	u32 c;
	for (int y=0;y<(buffer->height>>1);y++) {
		for (int x=0;x<(buffer->width>>1);x++) {
			c=pSrc[x]>>16;
			pDest[x]=((c<<16) | c);
		}
		pDest+=(buffer->pitch>>1);
		pSrc+=(buffer->pitch>>1);
	}
}

pixel_t RenderGetPixel(pframebuffer_t buffer,int x,int y)
{
	if (x<0 || y<0 || x>=buffer->width || y>=buffer->height)
		return 0;

	pixel_t *pDest=(ppixel_t)(byte*)buffer->pixels  + ((x) + (y * buffer->pitch>>1));
	return *pDest;
}

void RenderPixel(pframebuffer_t buffer,int x,int y,pixel_t color)
{
	if (x<0 || y<0 || x>=buffer->width || y>=buffer->height)
		return;

	pixel_t *pDest=(ppixel_t)(byte*)buffer->pixels  + ((x) + (y * buffer->pitch>>1));
	*pDest=color;
}

void RenderLine(pframebuffer_t buffer,int x,int y,int x2,int y2,pixel_t color)
{
	int lx=FPABS((x-x2));
	int ly=FPABS((y-y2));

	int l=lx>ly ? lx : ly;
	int fl=(l<<FPP);
	if ((fl>>FPP)==0) fl=FPONE;

	int sx=x<<FPP;
	int sy=y<<FPP;
	int xx=(x2-x)<<FPP;
	int yy=(y2-y)<<FPP;

	xx=FPDIV(xx,fl);
	yy=FPDIV(yy,fl);

	while(l>0) {
		RenderPixel(buffer,(sx>>FPP),(sy>>FPP),color);
		sx+=xx;
		sy+=yy;
		l--;
	}
}

void RenderHLine(pframebuffer_t buffer,int x,int y,int w,pixel_t color)
{
	if (w<1 || x+w<0 || x>buffer->width || y>buffer->height || y<0)
		return;

	if (x<0) {
		w+=x;
		x=0;
	}

	if ((x+w)>buffer->width) {
		w=(buffer->width-x);
	}

	pixel_t *pTarget=(ppixel_t)(byte*)buffer->pixels  + ((x) + (y * buffer->pitch>>1));

	// byte align
	if (((u32)pTarget & 3) || ((u32)pTarget & 1)) {
		*pTarget++=color;
		w--;
	}

	// write dword
	u32 *pTarget32=(u32*)pTarget;	
	u32 cc=(color<<16) | color;
	while(w>0) {
		*pTarget32++=cc;
		w-=2;
	}
	
	// render last pixel
	if (w==0) {
		*(ppixel_t)pTarget32=color;
	}
}

void RenderVLine(pframebuffer_t buffer,int x,int y,int h,pixel_t color)
{
	if (h<1 || y+h<0 || x>buffer->width || y>buffer->height || x<0)
		return;

	if (y<0) {
		h+=y;
		y=0;
	}

	if ((y+h)>buffer->height) {
		h=(buffer->height-y);
	}

	pixel_t *pTarget=(ppixel_t)(byte*)buffer->pixels  + ((x) + (y * buffer->pitch>>1));

	while(h+1>0) {
		*pTarget=color;
		pTarget+=(buffer->pitch>>1);
		h--;
	}
}
