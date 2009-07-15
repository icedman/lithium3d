#include "md2.h"
#include <windows.h>
#include <stdio.h>

#include "trace.h"

CMD2Model::CMD2Model()
{
     numVertices = 0;
     numTriangles = 0;
     numFrames = 0;
     numST = 0;
     frameSize = 0;
     currentFrame = 0;
     nextFrame = 1;
     interpol = 0;
     triIndex = NULL;
     st = NULL;
     vertexList = NULL;
	 interpolList = NULL;
	 modelState = MD2_IDLE;
}    

CMD2Model::~CMD2Model()
{
	Unload();
}

int CMD2Model::LoadModel(TCHAR *modelFile)
{
	FILE *filePtr;
	int fileLen;
	char *buffer;
     
	modelHeader_t *modelHeader;
     
	stIndex_t *stPtr;
	frame_t   *frame;
	vector_t  *vertexListPtr;
	mesh_t	  *bufIndexPtr;

	int i, j;

	// open the model file
	filePtr = _tfopen(modelFile, _T("rb"));
	if (filePtr == NULL)
		return false;
     
	// find length of file
	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);
     
	// read entire file into buffer
	buffer = new char [fileLen+1];
	fread(buffer, sizeof(char), fileLen, filePtr);
     
	// extract model file header from buffer
	modelHeader = (modelHeader_t*)buffer;
     
	// allocate vertex list
	vertexList = new vector_t [modelHeader->numXYZ * modelHeader->numFrames];
     
	numVertices = modelHeader->numXYZ;
	numFrames = modelHeader->numFrames;
	frameSize = modelHeader->framesize;

	if (numFrames>1)
		interpolList = new vector_t [modelHeader->numXYZ * modelHeader->numFrames];
	else
		interpolList = &vertexList[0];

	int scale=500;

	int maxx=0;
	int maxy=0;
	int maxz=0;

	for (j = 0; j < numFrames; j++) {
		frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];
		vertexListPtr = (vector_t*)&vertexList[numVertices * j];
		maxx=maxy=maxz=0;
		for (i = 0; i < numVertices; i++) {
			if (maxx==0 || maxx < frame->fp[i].v[0])
				maxx=frame->fp[i].v[0];
			if (maxy==0 || maxy < frame->fp[i].v[1])
				maxy=frame->fp[i].v[1];
			if (maxz==0 || maxz < frame->fp[i].v[2])
				maxz=frame->fp[i].v[2];
		}
		// center
		maxx=maxx>>1;
		maxy=maxy>>1;
		maxz=maxz>>1;

		//maxx=0;//-24;
		maxx=-24;

		for (i = 0; i < numVertices; i++) {
			vertexListPtr[i].z=FPFL(frame->scale[0] * (frame->fp[i].v[0] + frame->translate[0] - maxz))/scale;
			vertexListPtr[i].y=FPFL(frame->scale[1] * (frame->fp[i].v[1] + frame->translate[1] - maxy))/scale;
			vertexListPtr[i].x=FPFL(frame->scale[2] * (frame->fp[i].v[2] + frame->translate[2] - maxx))/scale;
		}
	}
     
	numST = modelHeader->numST;     
	st = new coord_t [numST];
     
	stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];
	for (i = 0; i < numST; i++) {
		// convert to 128x128
		st[i].x =(int)(128*(float)stPtr[i].s/modelHeader->skinwidth);
		st[i].y =(int)(128*(float)stPtr[i].t/modelHeader->skinheight);
	}
     
	numTriangles = modelHeader->numTris;
	triIndex = new mesh_t [numTriangles];

	// point to triangle indexes in buffer
	bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];

	for(i = 0; i < numTriangles; i++) {
		triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
		triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
		triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
		triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
		triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
		triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
	}

	// close file and free memory
	fclose(filePtr);
     
	currentFrame = 0;
	nextFrame = 1;
	interpol = 0;

	delete [] buffer;
   
	return 0;
}

void CMD2Model::Unload()
{
     if (triIndex != NULL)
		delete [] triIndex;
     if (vertexList != NULL)
		delete [] vertexList;
	 if (interpolList != NULL)
		delete [] interpolList;
     if (st != NULL)
		delete [] st;

	 triIndex=NULL;
	 vertexList=NULL;
	 interpolList=NULL;
	 st=NULL;
}

void CMD2Model::SetState(md2state_t state)
{
	modelState = state;
}

int CMD2Model::GetState()
{
	return modelState;
}

void CMD2Model::Render()
{
	vector_t *vList;
	int i;
     
	vList = interpolList;
	 
	glBegin(DRAW_TRIS);
	for(i = 0; i < numTriangles; i++) {
		
		glTextureCoord(st[triIndex[i].stIndex[0]]);
		glVertex(vList[triIndex[i].meshIndex[0]],
					triIndex[i].meshIndex[0]);

		glTextureCoord(st[triIndex[i].stIndex[2]]);
		glVertex(vList[triIndex[i].meshIndex[2]],
					triIndex[i].meshIndex[2]);

		glTextureCoord(st[triIndex[i].stIndex[1]]);
		glVertex(vList[triIndex[i].meshIndex[1]],
					triIndex[i].meshIndex[1]);

	}
	glEnd();
}

void CMD2Model::Update(int delta)
{
	interpol+=delta;
	Animate();
}

void CMD2Model::Animate()
{
	int frameStart=g_md2sequence[modelState].frameStart;
	int frameEnd=g_md2sequence[modelState].frameEnd;

	if (currentFrame < frameStart) {
		currentFrame=frameStart;
		nextFrame=currentFrame+1;
	}	

	if (interpol >= FPONE) {
		interpol=0;

		if (currentFrame==frameEnd) {
			currentFrame=frameStart;
			nextFrame=currentFrame+1;
		} else if (nextFrame==frameEnd) {
			currentFrame=nextFrame;
			nextFrame=frameStart;
		} else {
			currentFrame=nextFrame;
			nextFrame=currentFrame+1;
		}

	}

	pvector_t vlist1=&vertexList[numVertices * currentFrame];
	pvector_t vlist2=&vertexList[numVertices * nextFrame];
	pvector_t vinterpol=interpolList;

	int xx,yy,zz;
	
	// interpolate vertices
	for (int i = 0; i < numVertices; i++) {
		xx = ((vlist2[i].x - vlist1[i].x) * interpol)>>FPP;
		yy = ((vlist2[i].y - vlist1[i].y) * interpol)>>FPP;
		zz = ((vlist2[i].z - vlist1[i].z) * interpol)>>FPP;

		vinterpol[i].x=vlist1[i].x + xx;
		vinterpol[i].y=vlist1[i].y + yy;
		vinterpol[i].z=vlist1[i].z + zz;
	}
}