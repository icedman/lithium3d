
#ifndef _LITH_SURFACE_H_
#define _LITH_SURFACE_H_

#include <windows.h>
#include <tchar.h>

#include "stdtypes.h"
#include "framebuffer.h"
#include "pixel.h"
#include "utils.h"

typedef framebuffer_t surface_t, *psurface_t;

void SurfaceInit(surface_t& target,const surface_t& source);
psurface_t SurfaceInit(const surface_t& source);
void SurfaceInit(surface_t& target,const TCHAR *filename);
void SurfaceZero(surface_t& target);
void SurfaceFree(surface_t& target);
void SurfaceImage(surface_t& target,const TCHAR *filename);
psurface_t SurfaceImage(const TCHAR *filename);

#endif // _LITH_SURFACE_H_