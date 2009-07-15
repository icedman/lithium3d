
#ifndef _LITH_TEXTURES_H_
#define _LITH_TEXTURES_H_

#include "palette.h"
#include "vector.h"

#define MAX_TEXTURE_CACHE 64

#define TEXTURE_8BIT	0
#define TEXTURE_16BIT	1

typedef struct {
	void *pixels;	//u8* or u16*
	ppalette_t palette;
	u16 width;
	u16 height;
	u8  shift;	
	int mode;
} texture_t,*ptexture_t;

typedef ptexture_t texture_cache_t[MAX_TEXTURE_CACHE];

void TextureInit(texture_t& t);
ptexture_t TextureImage(const TCHAR *filename,int mode=TEXTURE_16BIT);
void TextureImage(texture_t& t,const TCHAR *filename,int mode=TEXTURE_16BIT);
void TextureFree(texture_t& t);

void TextureCacheInit(texture_cache_t& textures);
int TextureCacheAdd(texture_cache_t& textures,const TCHAR *filename,int mode=TEXTURE_16BIT);
void TextureCacheFree(texture_cache_t& textures,int id);
void TextureCacheFree(texture_cache_t& textures);

inline void TextureWrap(ptexture_t t,int& su,int& sv) {
	if ((su>>FPP)+1>t->width) su=su & ~(t->width<<FPP);
	if ((sv>>FPP)+1>t->height) sv=sv & ~(t->height<<FPP);
}

#endif // _LITH_TEXTURES_H_