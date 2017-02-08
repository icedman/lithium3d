
#include "image.h"
#include "pixel.h"

#include <stdio.h>
#include <stdlib.h>

void BitmapZero(bitmapfile_t& bitmap)
{
	bitmap.buffer=NULL;
}

// bitmap should be empty
int BitmapLoad(bitmapfile_t& bitmap,const TCHAR *filename)
{
	// reset bitmap
	BitmapZero(bitmap);	

	FILE *filePtr;
	int index;

	// open bitmap file
	filePtr = fopen(filename, _T("rb"));
	if (filePtr == NULL)
		return 0;

	// read the file header
	fread(&bitmap.fileheader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	if (bitmap.fileheader.bfType!=0x4D42) {
		fclose(filePtr);
		return 0;
	}

	// info header
	fread(&bitmap.infoheader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	if (!bitmap.infoheader.biSizeImage)
		bitmap.infoheader.biSizeImage=bitmap.infoheader.biWidth * bitmap.infoheader.biHeight;

	if (!bitmap.infoheader.biClrUsed)
		bitmap.infoheader.biClrUsed=256;

	// load palette if present
	if (bitmap.infoheader.biBitCount == 4 || bitmap.infoheader.biBitCount == 8) {
		fread(bitmap.palette, sizeof(PALETTEENTRY), bitmap.infoheader.biClrUsed, filePtr);
	
	   // now set all the flags in the palette correctly and fix the reversed 
	   // BGR RGBQUAD data format

	   for (index=0; index < 256; index++) {
		   // reverse the red and green fields
		   int temp_color               = bitmap.palette[index].peRed;
		   bitmap.palette[index].peRed  = bitmap.palette[index].peBlue;
		   bitmap.palette[index].peBlue = temp_color;
		   // always set the flags word to this
		   bitmap.palette[index].peFlags = 0;
	   }
	}

	// load image data
	if (bitmap.infoheader.biBitCount==4 || bitmap.infoheader.biBitCount==8 || bitmap.infoheader.biBitCount==16) {
		
		// allocate the memory for the image
		if (!(bitmap.buffer = (u8 *)malloc(bitmap.infoheader.biSizeImage))) {
			fclose(filePtr);
			return 0;
		}

		fread(bitmap.buffer, bitmap.infoheader.biSizeImage, 1, filePtr);

	} else if (bitmap.infoheader.biBitCount==24) {

		// 24 bit. load and convert to 16 bit
		u8* temp_buffer=NULL;
		
		if (!(temp_buffer = (u8 *)malloc(bitmap.infoheader.biSizeImage))) {
			fclose(filePtr);
			return 0;
		}

		fread(temp_buffer, sizeof(u8),bitmap.infoheader.biSizeImage, filePtr);

		// allocate the memory for the 16 bit image
		int size=bitmap.infoheader.biWidth*bitmap.infoheader.biHeight;
		if (!(bitmap.buffer = (u8 *)malloc(sizeof(u16)*size))) {
			fclose(filePtr);
			free(temp_buffer);
			return 0;
		}

		// convert 24 to 16
		for(index=0;index<size;index++) {
			// 16 bit color
			u16 c;
			u8 blue  = (temp_buffer[index*3 + 0] >> 3),
			   green = (temp_buffer[index*3 + 1] >> 2),
			   red   = (temp_buffer[index*3 + 2] >> 3);
			c=RGB_SET(red,green,blue);
			((u16 *)bitmap.buffer)[index] = c;
		}

		bitmap.infoheader.biBitCount=16;
		free(temp_buffer);
	}

	// close file
	fclose(filePtr);

	return 1;
}

void BitmapFree(bitmapfile_t& bitmap)
{
	if (bitmap.buffer) {
		// free(bitmap.buffer);
	}
}
