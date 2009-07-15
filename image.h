
#ifndef _LITH_IMAGE_H_
#define _LITH_IMAGE_H_

#include "stdtypes.h"

#include <windows.h>
#include <tchar.h>

typedef struct {
	BITMAPFILEHEADER fileheader;	// this contains the bitmapfile header
	BITMAPINFOHEADER infoheader;	// this is all the info including the palette
	PALETTEENTRY     palette[256];  // we will store the palette here
	u8				 *buffer;       // this is a pointer to the data
} bitmapfile_t,*pbitmapfile_t;

void BitmapZero(bitmapfile_t& bitmap);
int  BitmapLoad(bitmapfile_t& bitmap,const TCHAR *filename);
void BitmapFree(bitmapfile_t& bitmap);

#endif // _LITH_IMAGE_H_