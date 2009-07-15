
#ifndef _LITH_VERTEX_H_
#define _LITH_VERTEX_H_

#include "vector.h"

#define MAX_VERTEX_CACHE 256

typedef struct {
	vector_t	world;		// world pos
	coord_t		screen;		// screen pos
	coord_t		texture;
	u16			light;
} vertex_t,*pvertex_t;

typedef struct {
	vector_t	world;
	coord_t		screen;
	u16			update;
} vcache_t,*pcache_t;

typedef struct {
	vcache_t vertices[MAX_VERTEX_CACHE];
	u16		 update;
} vertexcache_t,*pvertexcache_t;

inline void VertexInit(vertex_t& vr,vector_t w,coord_t s,u16 l) {
	VectorCopy(&vr.world,&w);
	CoordCopy(&vr.screen,&s);
	vr.light=l;
}

#define VertexCopy(v,src)	{memcpy((void *)(v), (void *)(src), 24); }

void VertexCacheInit(vertexcache_t& vc);
bool VertexCacheSet(vertexcache_t& vc,vertex_t&v,u16 id);
bool VertexCacheGet(vertexcache_t& vc,vertex_t&v,u16 id);
void VertexCacheUpdate(vertexcache_t& vc);

#endif // _LITH_VERTEX_H_


