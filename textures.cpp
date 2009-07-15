
#include "textures.h"
#include "image.h"

void TextureInit(texture_t& t)
{
	t.palette=NULL;
	t.pixels=NULL;
	t.width=0;
	t.height=0;
	t.shift=0;
}

ptexture_t TextureImage(const TCHAR *filename,int mode)
{
	ptexture_t texture=new texture_t;	
	TextureImage(*texture, filename,mode);
	return texture;
}

void TextureImage(texture_t& t,const TCHAR *filename,int mode)
{
	TextureInit(t);

	bitmapfile_t b;
	if (!BitmapLoad(b,filename)) {
		return;
	}

	int size=b.infoheader.biWidth * b.infoheader.biHeight;
	t.width=(u16)b.infoheader.biWidth;
	t.height=(u16)b.infoheader.biHeight;

	if (b.infoheader.biBitCount==24) {
		t.pixels=(ppixel_t)b.buffer;
		t.mode=TEXTURE_16BIT;
	} else {
		t.mode=mode;
		if (t.mode==TEXTURE_8BIT) {
			t.pixels=b.buffer;
		} else {			
			// 8 bit. load and convert to 16 bit
			u8* temp_buffer=b.buffer;			
			int size=b.infoheader.biWidth*b.infoheader.biHeight;
			if (!(t.pixels = (u8 *)malloc(2*size))) {
				return;
			}
			// convert 8 bit to 16 bit		
			for(int index=0;index<size;index++) {
				u8 paletteindex=((u8 *)temp_buffer)[index];
				u8 red=b.palette[paletteindex].peRed		>> 3,
				   green=b.palette[paletteindex].peGreen	>> 2,
				   blue=b.palette[paletteindex].peBlue		>> 3;
				u16 c=RGB_SET(red,green,blue);
				((u16 *)t.pixels)[index] = c;
			}			
			free(temp_buffer);
		}
	}

	// calculate bit shift
	float w=t.width;
	while(w>1) {
		w/=2;
		t.shift++;
	}
}

void TextureFree(texture_t& t)
{
	if (t.palette) {
		t.palette=NULL;
	}
	if (t.pixels) {
		delete t.pixels;
		t.pixels=NULL;
	}
	t.width=0;
	t.height=0;
}

void TextureCacheInit(texture_cache_t& textures)
{
	for(int i=0;i<MAX_TEXTURE_CACHE;i++) {
		textures[i]=NULL;
	}
}

int TextureCacheAdd(texture_cache_t& textures,const TCHAR *filename,int mode)
{
	for(int i=0;i<MAX_TEXTURE_CACHE;i++) {
		if (textures[i]==NULL) {
			textures[i]=TextureImage(filename,mode);
			return i;
		}
	}
	return -1;
}

void TextureCacheFree(texture_cache_t& textures,int id)
{
	if (!textures[id])
		return;

	ptexture_t target=textures[id];
	TextureFree(*target);
	delete target;

	textures[id]=NULL;
}

void TextureCacheFree(texture_cache_t& textures)
{
	for(int i=0;i<MAX_TEXTURE_CACHE;i++) {
		TextureCacheFree(textures,i);
	}
}
