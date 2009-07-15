
#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include "lithium3d.h"

// holds a quad or a tri
typedef struct {
    u16		vertexIndex[4];
    u16		uvIndex[4];
	u16		numVertices;
} mesh_t, *pmesh_t;

// 3d object
typedef struct {
	pmesh_t		meshList;
	pvector_t	vertexList;
	pcoord_t	uvList;
	u16 numMesh;
	u16 numVertices;
	u16 numTextureCoord;
	texture_t*	texture;
} object_t, *pobject_t;

void ObjectCreateCube(object_t& object);
void ObjectDraw(object_t& object);
void ObjectDestroy(object_t& object);

#endif // _SAMPLE_H_