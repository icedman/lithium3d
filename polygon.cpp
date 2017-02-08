
#include "polygon.h"
#include "renderbasic.h"
#include "maths.h"

#include "trace.h"

#include <stdlib.h>

inline void EdgeCalculate(pedge_t e,pvertex_t v1,pvertex_t v2)
{
	e->length=(v2->screen.y - v1->screen.y);

	// calc x
	e->x=v1->screen.x;
	e->xx=(v2->screen.x - e->x);
	e->x=e->x<<FPP;	
	// calc y
	e->y=v1->screen.y;
	e->yy=(v2->screen.y - e->y);
	e->y=e->y<<FPP;

	// calc u
	e->u=v1->texture.x;
	e->uu=v2->texture.x - e->u;
	e->u=e->u<<FPP;	
	// calc v
	e->v=v1->texture.y;
	e->vv=v2->texture.y - e->v;
	e->v=e->v<<FPP;

	// light
	e->l=v1->light;
	e->ll=v2->light - e->l;
	e->l=e->l<<FPP;

	if (e->length!=0) {		
		s32 fl=e->length < RECIPROCAL_MAX ? FPRECIP(e->length): FPONE/e->length;
		e->xx=FPMUL((e->xx<<FPP),fl);
		e->yy=FPMUL((e->yy<<FPP),fl);
		e->uu=FPMUL((e->uu<<FPP),fl);
		e->vv=FPMUL((e->vv<<FPP),fl);
		e->ll=FPMUL((e->ll<<FPP),fl);		
		/*
		s32 fl=e->length<<FPP;
		e->xx=FPDIV((e->xx<<FPP),fl);
		e->yy=FPDIV((e->yy<<FPP),fl);
		e->uu=FPDIV((e->uu<<FPP),fl);
		e->vv=FPDIV((e->vv<<FPP),fl);
		e->ll=FPDIV((e->ll<<FPP),fl);
		*/
	} else {
		e->xx=0; e->yy=0; e->uu=0; e->vv=0; e->l=0;
	}
}

inline void EdgeStep(pedge_t e)
{
	e->length--;
	e->x+=e->xx;
	e->y+=e->yy;
	e->z+=e->zz;
	e->u+=e->uu;
	e->v+=e->vv;
	e->l+=e->ll;
}

void VertexClip(projection_t& p,vertex_t& v1,vertex_t& v2,vertex_t& vr)
{
	int d=(v1.world.z - v2.world.z);
	int dd=d!=0 ? ((v1.world.z - p.nearz)<<6) / (d) : 0;

	int xx = ((v2.world.x - v1.world.x) * dd)>>6;
	int yy = ((v2.world.y - v1.world.y) * dd)>>6;
	int zz = ((v2.world.z - v1.world.z) * dd)>>6;

	vr.world.x=v1.world.x + xx;
	vr.world.y=v1.world.y + yy;
	vr.world.z=v1.world.z + zz;

	// screen coord
	ProjectionVertex(p,vr.world,vr.screen);

	// texture coord
	int uu = ((v2.texture.x - v1.texture.x) * dd)>>6;
	int vv = ((v2.texture.y - v1.texture.y) * dd)>>6;

	vr.texture.x=v1.texture.x + uu;
	vr.texture.y=v1.texture.y + vv;

	// lighting
	int ll = ((v2.light - v1.light) * dd)>>6;
	vr.light=v1.light + ll;
}

void PolygonClip(polygon_t& p,projection_t& proj)
{
	// backface culling
	if (p.numVertices>2)
	if (PolygonBackFace(p)) {
		p.numVertices=0; 
		return;
	}

	int i=0;

	int maxx=0,minx=0;
	int maxy=0,miny=0;
	int maxz=0,minz=0;

	for(i=0;i<p.numVertices;i++) {
		if (p.vertices[i].world.x > maxx || maxx==0) 
			maxx=p.vertices[i].world.x;
		if (p.vertices[i].world.x < minx || minx==0) 
			minx=p.vertices[i].world.x;
		if (p.vertices[i].world.y > maxy || maxy==0) 
			maxx=p.vertices[i].world.y;
		if (p.vertices[i].world.y < miny || miny==0) 
			minx=p.vertices[i].world.y;
		if (p.vertices[i].world.z > maxz || maxz==0) 
			maxz=p.vertices[i].world.z;
		if (p.vertices[i].world.z < minz || minz==0) 
			minz=p.vertices[i].world.z;
	}

	// no clipping needed
	if (maxz<proj.farz && minz>proj.nearz) {
		return;
	}

	// drop, polygon too far
	if (minz>proj.farz) {
		p.numVertices=0;		
		return;
	}

	// drop, too near
	if (maxz<proj.nearz) {		
		p.numVertices=0;
		return;
	}

	// off screen horizontal
	if (maxx<0 || minx>proj.viewwidth) {
		p.numVertices=0;
		return;
	}

	// off screen vertical
	if (maxy<0 || miny>proj.viewheight) {		
		p.numVertices=0;		
		return;
	}

	// z-clip all other polygons
	polygon_t tmp;
	PolygonCopy(&tmp,&p);

	vertex_t nv;	// new rvertex

	PolygonInit(&p);

	pvertex_t vcurr=&tmp.vertices[tmp.numVertices-1];
	pvertex_t vprev=vcurr;

	for(i=0;i<tmp.numVertices;i++) {
		vprev=vcurr;
		vcurr=&tmp.vertices[i];

		if (vcurr->world.z > proj.nearz) {
			if (vprev->world.z <= proj.nearz) {
				VertexClip(proj,*vcurr,*vprev,nv);				
				nv.screen.y+=20;
				PolygonVertex(&p,&nv);
			}
			PolygonVertex(&p,vcurr);
		} else {
			if (vprev->world.z > proj.nearz) {
				VertexClip(proj,*vprev,*vcurr,nv);
				nv.screen.y+=20;
				PolygonVertex(&p,&nv);
			}
		}

	}	

	if (p.numVertices<3) {
		p.numVertices=0;
	}
}

void RenderPolygonPoints(pframebuffer_t buffer,ppolygon_t p)
{
	for(int i=0;i<p->numVertices;i++) {
		RenderPixel(buffer,
			p->vertices[i].screen.x,
			p->vertices[i].screen.y,
			RGB_SET(31,63,31));
	}
}

void RenderPolygonFrame(pframebuffer_t buffer,ppolygon_t p)
{
	pvertex_t p1=&p->vertices[p->numVertices-1];
	pvertex_t p2=p1;
	for(int i=0;i<p->numVertices;i++) {
		p2=p1;
		p1=&p->vertices[i];
		RenderLine(buffer,
			p1->screen.x,p1->screen.y,
			p2->screen.x,p2->screen.y,
			RGB_SET(31,63,31));

		//TRACE(p1->screen.x);
	}
}

void RenderPolygonLines(pframebuffer_t buffer,ppolygon_t p)
{
	if (p->numVertices<2)
		return;

	pvertex_t p1,p2;
	for(int i=0;i<p->numVertices-1;i++) {
		p1=&p->vertices[i];
		p2=p1+1;
		RenderLine(buffer,
			p1->screen.x,p1->screen.y,
			p2->screen.x,p2->screen.y,
			RGB_SET(31,63,31));
	}
}

#include <stdio.h>

#define RENDER_16BIT
void RenderPolygon16(pframebuffer_t buffer,ppolygon_t polygon,ptexture_t texture)
#include "renderpolyimp.h"

#define RENDER_8BIT
void RenderPolygon8(pframebuffer_t buffer,ppolygon_t polygon,ptexture_t texture)
#include "renderpolyimp.h"
