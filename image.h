
#ifndef _LITH_IMAGE_H_
#define _LITH_IMAGE_H_

#include "stdtypes.h"

// #include <windows.h>
// #include <tchar.h>

typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef BITMAPFILEHEADER* PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER; 

typedef BITMAPINFOHEADER* PBITMAPINFOHEADER;

typedef struct tagPALETTEENTRY {
  BYTE peRed;
  BYTE peGreen;
  BYTE peBlue;
  BYTE peFlags;
} PALETTEENTRY;

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