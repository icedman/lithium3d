
#ifndef _LITH_POLYGON_H_
#define _LITH_POLYGON_H_

#include "framebuffer.h"
#include "vertex.h"
#include "textures.h"

#include "camera.h"

#define MAX_POLYGON_VERTICES 6

typedef struct {
	vertex_t vertices[MAX_POLYGON_VERTICES];
	u8 numVertices;
} polygon_t,*ppolygon_t;

inline void PolygonInit(ppolygon_t p) { p->numVertices=0;}
inline void PolygonVertex(ppolygon_t p,pvertex_t r) {
	VertexCopy(&p->vertices[p->numVertices],r);
	p->numVertices++;
}
inline bool PolygonBackFace(polygon_t& p) {
	int x12=p.vertices[0].screen.x - p.vertices[1].screen.x;
	int y32=p.vertices[2].screen.y - p.vertices[1].screen.y;
	int y12=p.vertices[0].screen.y - p.vertices[1].screen.y;
	int x32=p.vertices[2].screen.x - p.vertices[1].screen.x;
	if (((x12 * y32) - (y12 * x32)) > 0)
		return 1;
	return 0;
}

typedef struct {
	s32	length;
	s32	x,y,z;	
	s32	u,v;	
	s32	l;
	s32	xx,yy,zz;
	s32	uu,vv;
	s32	ll;
	s32 reserved1;
	s32 reserved2;
	s32 reserved3;
} edge_t,*pedge_t;

#define PolygonCopy(pd,ps) { memcpy((void*)pd,(void*)ps,148); }
void VertexClip(projection_t& p,vertex_t& v1,vertex_t& v2,vertex_t& vr);
void PolygonClip(polygon_t& p,projection_t& proj);

typedef void (*FuncRenderPolygon) (pframebuffer_t buffer,ppolygon_t polygon,ptexture_t texture);
void RenderPolygon16(pframebuffer_t buffer,ppolygon_t polygon,ptexture_t texture);
void RenderPolygon8(pframebuffer_t buffer,ppolygon_t polygon,ptexture_t texture);

void RenderPolygonPoints(pframebuffer_t buffer,ppolygon_t p);
void RenderPolygonFrame(pframebuffer_t buffer,ppolygon_t p);
void RenderPolygonLines(pframebuffer_t buffer,ppolygon_t p);

#endif // _LITH_POLYGON_H_