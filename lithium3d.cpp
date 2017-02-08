
#include "lithium3d.h"
#include "trace.h"

lithiumgl_t gl;

// statistics
#define LITHIUM_STATS

void glInitialize(int w,int h)
{
	TextureCacheInit(gl.textures);
	VertexCacheInit(gl.vertexCache);
	MatrixStackInit(gl.model);
	ProjectionInit(gl.projection,h,FPONE,1<<8,24<<8);
	CameraInit(gl.camera,0,0,0,0,0);
	
	RenderListInit(gl.renderlist);
	RenderBucketInit(gl.renderlist);

	gl.renderMode=0;
	gl.palette=&gl.genericPalette;
	PaletteInit(gl.genericPalette);

	glViewport(w,h);
	glPolygonMode(POLYGON_FILLED);
	glColor(RGB_SET(31,63,0));
	glClearColor(0);
	glIntensity(7);

	#ifdef LITHIUM_STATS
	glResetStats();
	#endif
}

ppalette_t glGetPalette()
{
	return gl.palette;
}

void glSetPalette(ppalette_t palette)
{
	if (palette)
		gl.palette=palette;
	else
		gl.palette=&gl.genericPalette;
}

void glShutdown()
{
	TextureCacheFree(gl.textures);
}

void glViewport(int w,int h)
{
	ProjectionViewport(gl.projection,w,h);
}

void glEnable(int bit)
{
	gl.renderMode=gl.renderMode | (bit);	
}

void glDisable(int bit)
{
	gl.renderMode=gl.renderMode & ~(bit);
}

void glPolygonMode(int bit)
{
	gl.polygonMode=bit;
}

void glSetTarget(pframebuffer_t target)
{
	gl.renderTarget=target;
}

void glColor(pixel_t c)
{
	gl.color=c;
}

void glClearColor(pixel_t c)
{
	gl.clearColor=c;
}

void glIntensity(int intensity)
{
	gl.intensity=intensity;
}

void glCamera(vector_t &pos,int heading,int elevation)
{
	CameraInit(gl.camera,pos,heading,elevation);
}

pcamera_t glGetCamera()
{
	return &gl.camera;
}

void glPushMatrix()
{
	MatrixStackPush(gl.model);
}

void glPopMatrix()
{
	MatrixStackPop(gl.model);
}

void glIdentity()
{
	MatrixIdentity(gl.model.matrix);	
}

void glLoadMatrix(matrix_t m)
{
	MatrixCopy(gl.model.matrix,&m);
}

void glRotate(int ax,int ay,int az)
{
	matrix_t mrot,mtmp;
	MatrixCopy(&mtmp,gl.model.matrix);
	MatrixRotate(mrot,ax,ay,az);
	MatrixMultiply(mtmp,mrot,*gl.model.matrix);
}

void glTranslate(int tx,int ty,int tz)
{
	matrix_t mtrans,mtmp;
	MatrixCopy(&mtmp,gl.model.matrix);
	MatrixTranslate(mtrans,tx,ty,tz);
	MatrixMultiply(mtmp,mtrans,*gl.model.matrix);
}

void glScale(int sx,int sy,int sz)
{	
	matrix_t mscal,mtmp;
	MatrixCopy(&mtmp,gl.model.matrix);
	MatrixScale(mscal,sx,sy,sz);
	MatrixMultiply(mtmp,mscal,*gl.model.matrix);
}

pmatrix_t glGetMatrix()
{
	return gl.model.matrix;
}

int glAddTexture(const TCHAR* filename,int mode)
{
	int i=TextureCacheAdd(gl.textures,filename,mode);
	return i;
}

void glRemoveTexture(int id)
{
	TextureCacheFree(gl.textures,id);
}

void glBindTexture(ptexture_t source)
{
	gl.textureSource=source;
}

void glBindTexture(int id)
{
	if (id==-1) {
		gl.textureSource=NULL;
		return;
	}

	if (gl.textures[id]) {
		gl.textureSource=gl.textures[id];
		gl.textureSource->palette=glGetPalette();
	}
}

void glTextureCoord(coord_t& c)
{
	gl.textureCoord=c;
}

void glTextureCoord(int u,int v)
{
	gl.textureCoord.x=u;
	gl.textureCoord.y=v;
}

void glVertex(int x,int y,int z)
{
	vector_t v;
	VectorInit(v,x,y,z);
	glVertex(v,-1);
}

void glVertex(int x,int y,int z,int index)
{
	vector_t v;
	VectorInit(v,x,y,z);
	glVertex(v,index);
}

void glVertex(vector_t& v)
{
	glVertex(v,-1);
}

void glVertex(vector_t& v,int index)
{
	vertex_t vr;

	#ifdef LITHIUM_STATS
	gl.statistics.vertices++;
	#endif
	
	if (!(gl.renderMode & VERTEX_CACHING) || !VertexCacheGet(gl.vertexCache,vr,index)) {

		#ifdef LITHIUM_STATS
		gl.statistics.verticesCalculated++;
		#endif

		// world-camera transform		
		vector_t vc;
		VectorTransform(v,gl.worldCamMatrix,vc);

		// screen/perspective transform		
		coord_t vp;
		ProjectionVertex(gl.projection,vc,vp);

		// save rvertex to cache
		VertexInit(vr,vc,vp,2);
		VertexCacheSet(gl.vertexCache,vr,index);
	}

	// build up polygon
	vr.texture=gl.textureCoord;
	vr.light=gl.intensity;

	PolygonVertex(&gl.polygon,&vr);

	if (gl.polygon.numVertices!=gl.drawMode) 
		return;
	
	#ifdef LITHIUM_STATS
	gl.statistics.faces++;
	#endif

	// cull/clip
	// PolygonClip(gl.polygon,gl.projection);

	// render
	if (gl.polygon.numVertices>2) {

		#ifdef LITHIUM_STATS
		gl.statistics.facesRendered++;
		#endif

		if (gl.polygonMode & POLYGON_FRAMED) {
			RenderPolygonFrame(gl.renderTarget,&gl.polygon);
			PolygonInit(&gl.polygon);
			return;
		}

		if (gl.renderMode & Z_SORTING) {
			RenderBucketAdd(gl.renderlist,gl.polygon);
		} else {			
			RenderListAdd(gl.renderlist,gl.polygon);
		}

	}

	// clear polygon
	PolygonInit(&gl.polygon);
}

void glBegin(int mode)
{
	gl.drawMode=mode;

	// clear some data
	glClear(CLEAR_CACHE);
	PolygonInit(&gl.polygon);

	MatrixMultiply(*gl.model.matrix, gl.camera.matrix, gl.worldCamMatrix);	
}

void glEnd()
{
	rasterizer_t r;
	r.renderTarget=gl.renderTarget;
	r.textureSource=gl.textureSource;

	if (gl.renderMode & Z_SORTING) {		
		RenderBucketRasterize(&r,&gl.renderlist);
	} else {
		RenderListRasterize(&r,&gl.renderlist);
	}
}

void glClear(int bits)
{
	if (bits & CLEAR_FRAME) {
		RenderClear(gl.renderTarget,gl.clearColor);
	}
	if (bits & CLEAR_TEXTURES && (gl.renderMode & TEXTURE_MAPPING)) {
		gl.textureSource=NULL;
		TextureCacheFree(gl.textures);
	}
	if (bits & CLEAR_CACHE && (gl.renderMode & VERTEX_CACHING)) {
		VertexCacheUpdate(gl.vertexCache);	
	}
}

void glResetStats()
{
	gl.statistics.faces=0;
	gl.statistics.facesRendered=0;
	gl.statistics.vertices=0;
	gl.statistics.verticesCalculated=0;
}

pstats_t glGetStats()
{
	return &gl.statistics;
}