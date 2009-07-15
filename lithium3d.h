
#ifndef _LITHIUM3D_H_
#define _LITHIUM3D_H_

#include "stdtypes.h"

#include "maths.h"
#include "vector.h"
#include "matrix.h"

#include "camera.h"

#include "vertex.h"
#include "polygon.h"

#include "renderbasic.h"
#include "renderlist.h"

#include "utils.h"

// defaults
#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	240

// rendering mode 
#define	POLYGON_FILLED		(1<<1)
#define	POLYGON_FRAMED		(1<<2)

#define TEXTURE_MAPPING		(1<<1)
#define LIGHT_SHADING		(1<<2)
#define VERTEX_CACHING		(1<<3)
#define Z_SORTING			(1<<4)

// drawing mode
#define DRAW_QUADS			4
#define DRAW_TRIS			3
#define DRAW_LINES			2
#define DRAW_POINTS			1

// clear bits
#define CLEAR_FRAME			(1<<1)
#define CLEAR_TEXTURES		(1<<2)
#define CLEAR_CACHE			(1<<3)
#define CLEAR_ALL			(CLEAR_FRAME | CLEAR_TEXTURES | CLEAR_CACHE)

typedef struct {
	int vertices;
	int verticesCalculated;
	int faces;
	int facesRendered;
} stats_t,*pstats_t;

typedef struct {

	// state
	int				drawMode;
	int				renderMode;
	int				polygonMode;
	coord_t			textureCoord;
	u8				intensity;
	pixel_t			color;
	pixel_t			clearColor;
	vector_t		normal;

	// data
	texture_cache_t	textures;
	vertexcache_t	vertexCache;
	palette_t		genericPalette;

	polygon_t		polygon;
	
	// matrices
	matrix_t		worldCamMatrix;
	matrixStack_t	model;
	camera_t		camera;
	projection_t	projection;

	// rasterizer
	renderlist_t	renderlist;
	pframebuffer_t	renderTarget;
	ptexture_t		textureSource;
	ppalette_t		palette;

	//
	stats_t			statistics;
} lithiumgl_t,*plithiumgl_t;

extern lithiumgl_t gl;

// state
void glInitialize(int w,int h);
void glShutdown();
void glEnable(int bit);
void glDisable(int bit);
void glColor(pixel_t c);
void glClearColor(pixel_t c);
void glIntensity(int intensity);
void glSetTarget(pframebuffer_t target);
void glPolygonMode(int bit);
void glViewport(int w,int h);

ppalette_t glGetPalette();
void glSetPalette(ppalette_t palette);

// camera
void glCamera(vector_t &pos,int heading,int elevation);
pcamera_t glGetCamera();

// matrix
void glPushMatrix();
void glPopMatrix();
void glIdentity();
void glLoadMatrix(matrix_t m);
void glRotate(int ax,int ay,int az);
void glTranslate(int tx,int ty,int tz);
void glScale(int sx,int sy,int sz);
pmatrix_t glGetMatrix();

// texture
int glAddTexture(const TCHAR* filename,int mode=TEXTURE_16BIT);
void glRemoveTexture(int id);
void glBindTexture(int id);
void glBindTexture(ptexture_t source);
void glTextureCoord(coord_t& c);
void glTextureCoord(int u,int v);

// vertex operation
void glVertex(int x,int y,int z);
void glVertex(int x,int y,int z,int index);
void glVertex(vector_t& v);
void glVertex(vector_t& v,int index);

void glBegin(int mode);
void glEnd();

// clear
void glClear(int bits);

void glResetStats();
pstats_t glGetStats();

#endif // _LITHIUM3D_H_