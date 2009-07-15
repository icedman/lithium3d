
#include "surface.h"
#include "image.h"

void SurfaceInit(surface_t& target,const surface_t& source)
{
	target.width=source.width;
	target.height=source.height;
	target.pitch=source.width * sizeof(pixel_t);
	
	size_t size=sizeof(pixel_t)*(source.width * source.height);
	target.pixels=(ppixel_t)malloc(size);
	memcpy((ppixel_t)target.pixels,(ppixel_t)source.pixels,size);
}

psurface_t SurfaceInit(const surface_t& source)
{
	psurface_t target=new surface_t;
	SurfaceInit(*target,source);
	return target;
}

void SurfaceFree(surface_t& target)
{
	if (target.width && target.height) {
		free(target.pixels);
	}
	SurfaceZero(target);
}

void SurfaceZero(surface_t& target)
{
	target.width=0; 
	target.height=0;
	target.pixels=NULL;
}

void SurfaceImage(surface_t& target,const TCHAR *filename)
{
	SurfaceZero(target);

	bitmapfile_t b;
	if (!BitmapLoad(b,filename)) {
		return;
	}
	
	int size=b.infoheader.biWidth * b.infoheader.biHeight;
	target.width=(u16)b.infoheader.biWidth;
	target.height=(u16)b.infoheader.biHeight;
	target.pitch=(b.infoheader.biWidth*sizeof(pixel_t));
	target.pixels=(ppixel_t)b.buffer;
}

psurface_t SurfaceImage(const TCHAR *filename)
{
	psurface_t surface=new surface_t;
	
	SurfaceImage(*surface, filename);

	return surface;
}

