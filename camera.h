
#ifndef _LITH_CAMERA_H_
#define _LITH_CAMERA_H_

#include "stdtypes.h"
#include "vector.h"
#include "matrix.h"

typedef struct {
	vector_t u;			// right
	vector_t v;			// up
	vector_t n;			// look at
	vector_t pos;		// position
	vector_t target;	// spherical
	int elevation;
	int heading;
	matrix_t matrix;	// uvn camera matrix
} camera_t, *pcamera_t;

typedef struct {	
	s32 distance;
	s32	aspect;
	s32 nearz;
	s32 farz;
	s32 viewwidth;
	s32 viewheight;
	s32 dx;
	s32 dy;
	matrix_t matrix;
} projection_t, *pprojection_t;

void CameraInit(camera_t& cam,vector_t& pos,vector_t& u,vector_t& v,vector_t& n);
void CameraInit(camera_t& cam,vector_t& pos,int heading,int elevation);
void CameraInit(camera_t& cam,int x,int y,int z,int heading,int elevation);
void CameraBuildMatrix(camera_t& cam);

void ProjectionInit(projection_t& p,int distance,int aspect,int nearz,int farz);
void ProjectionViewport(projection_t& p,int width,int height);
void ProjectionVertex(projection_t& p,vector_t& v,coord_t &vr);

#endif // _LITH_CAMERA_H_