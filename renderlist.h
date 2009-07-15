
#ifndef _LITH_RENDER_LIST_H_
#define _LITH_RENDER_LIST_H_

#include "rasterizer.h"
#include "polygon.h"
#include "list.h"
#include "bucket.h"

#define MAX_RENDER_LIST	512

typedef struct {
	polygon_t  polygons[MAX_RENDER_LIST];
	node_t	   nodes[MAX_RENDER_LIST];
	list_t	   list;
	bucket_t   bucket;
	int index;
} renderlist_t,*prenderlist_t;

void RenderListInit(renderlist_t& r);
void RenderListAdd(renderlist_t& r,polygon_t& p);
void RenderListRasterize(prasterizer_t r,prenderlist_t l);

void RenderBucketInit(renderlist_t& r);
void RenderBucketAdd(renderlist_t& r,polygon_t& p);
void RenderBucketRasterize(prasterizer_t r,prenderlist_t l);

#endif // _LITH_RENDER_LIST_H_