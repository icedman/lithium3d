
#include "renderlist.h"
#include "trace.h"

void RenderListInit(renderlist_t& r)
{	
	ListInit(r.list);
	r.index=0;
}

void RenderListAdd(renderlist_t& r,polygon_t& p)
{
	if (r.index+1>MAX_RENDER_LIST)
		return;

	pnode_t node=&r.nodes[r.index];
	PolygonCopy(&r.polygons[r.index],&p);

	NodeInit(*node,(void*)&r.polygons[r.index]);
	r.index++;

	ListAppend(r.list,*node);
}

void RenderListRasterize(prasterizer_t r,prenderlist_t l)
{
	FuncRenderPolygon RenderPolygon=RenderPolygon8;
	if (r->textureSource->mode==TEXTURE_16BIT)
		RenderPolygon=RenderPolygon16;

	pnode_t n=l->list.first;
	ppolygon_t p=NULL;
	while(n) {
		p=(ppolygon_t)n->data;		
		RenderPolygon(r->renderTarget,p,r->textureSource);
		n=n->next;
	}
	RenderListInit(*l);
}

void RenderBucketInit(renderlist_t& r)
{
	BucketInit(r.bucket);
	r.index=0;
}

void RenderBucketAdd(renderlist_t& r,polygon_t& p)
{
	if (r.index+1>MAX_RENDER_LIST)
		return;

	pnode_t node=&r.nodes[r.index];
	PolygonCopy(&r.polygons[r.index],&p);

	int z=(p.vertices[0].world.z + p.vertices[1].world.z + p.vertices[2].world.z);
	int zi;		

	zi=z>>5;

	NodeInit(*node,(void*)&r.polygons[r.index]);
	r.index++;

	plist_t list=&r.bucket.buckets[zi];

	pnode_t nhead=list->first;
	pnode_t ntail=list->last;
	ppolygon_t pp=NULL;

	while(nhead && ntail) {
		pp=(ppolygon_t)nhead->data;
		if ((pp->vertices[0].world.z + pp->vertices[1].world.z + pp->vertices[2].world.z)<=z) {
			ListInsertBefore(*list,*node,*nhead);
			return;
		}
		pp=(ppolygon_t)ntail->data;
		if ((pp->vertices[0].world.z + pp->vertices[1].world.z + pp->vertices[2].world.z)>=z) {			
			ListInsertAfter(*list,*node,*ntail);
			return;
		}
		nhead=nhead->next;
		ntail=ntail->prev;
	}

	ListAppend(*list,*node);
}

void RenderBucketRasterize(prasterizer_t r,prenderlist_t l)
{
	FuncRenderPolygon RenderPolygon=RenderPolygon8;
	if (r->textureSource->mode==TEXTURE_16BIT)
		RenderPolygon=RenderPolygon16;

	plist_t list;
	pnode_t n;
	ppolygon_t p;
	for(int i=MAX_BUCKETS-1;i!=0;i--) {
		list=&l->bucket.buckets[i];
		n=list->first;
		if (n) {
			while(n) {
				p=(ppolygon_t)n->data;
				RenderPolygon(r->renderTarget,p,r->textureSource);
				n=n->next;
			}
			ListInit(*list);
		}
	}
	l->index=0;
}
