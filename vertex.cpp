
#include "vertex.h"

void VertexCacheInit(vertexcache_t& vc)
{
	for(int i=0;i<MAX_VERTEX_CACHE;i++) {
		vc.vertices[i].update=0;
	}
	vc.update=0;
}

bool VertexCacheGet(vertexcache_t& vc,vertex_t&v,u16 id)
{
	if (id>=MAX_VERTEX_CACHE) return 0;
	
	if (vc.vertices[id].update==vc.update) {
		VectorCopy(&v.world,&vc.vertices[id].world);
		CoordCopy(&v.screen,&vc.vertices[id].screen);
		return 1;
	}

	return 0;
}

bool VertexCacheSet(vertexcache_t& vc,vertex_t&v,u16 id)
{
	if (id>=MAX_VERTEX_CACHE) return 0;

	VectorCopy(&vc.vertices[id].world,&v.world);
	CoordCopy(&vc.vertices[id].screen,&v.screen);	
	vc.vertices[id].update=vc.update;
	return 1;
}

void VertexCacheUpdate(vertexcache_t& vc)
{
	if (vc.update++>=65536) vc.update=0;
}