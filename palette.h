
#ifndef _LITH_PALETTE_H_
#define _LITH_PALETTE_H_

// #include <windows.h>
// #include <tchar.h>

#include "pixel.h"

#define INTENSITY_ACCURACY 64

typedef struct {
	pixel_t colors[256];
	pixel_t intensity[256][INTENSITY_ACCURACY];
} palette_t,*ppalette_t;

void PaletteInit(palette_t& p);
void PaletteInit(palette_t& p,const TCHAR *filename);
void PaletteBuildIntensities(palette_t& p);

extern const int g_palette[256];

#endif _LITH_PALETTE_H_
