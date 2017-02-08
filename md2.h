#ifndef __MD2_H
#define __MD2_H

#include "lithium3d.h"

// #include <windows.h>
// #include <tchar.h>

#define MAX_FRAMES 512

typedef struct {
	int frameStart;
	int frameEnd;
	int fps;
} md2anim_t;

enum md2state_t {
    MD2_IDLE,
    MD2_RUN,
    MD2_ATTACK,
    MD2_PAIN_A,
    MD2_PAIN_B,
    MD2_PAIN_C,
    MD2_JUMP,
    MD2_FLIP,
    MD2_SALUTE,
    MD2_FALLBACK,
    MD2_WAVE,
    MD2_POINT,
    MD2_CROUCH_STAND,
    MD2_CROUCH_WALK,
    MD2_CROUCH_ATTACK,
    MD2_CROUCH_PAIN,
    MD2_CROUCH_DEATH, 
    MD2_DEATH_FALLBACK,
    MD2_DEATH_FALLFORWARD,
    MD2_DEATH_FALLBACKSLOW,
    MD2_BOOM
};

const md2anim_t g_md2sequence[21]={
    // first, last, fps
    {   0,  39,  9 },   // IDLE
    {  40,  45, 10 },   // RUN
    {  46,  53, 10 },   // ATTACK
    {  54,  57,  7 },   // PAIN_A
    {  58,  61,  7 },   // PAIN_B
    {  62,  65,  7 },   // PAIN_C
    {  66,  71,  7 },   // JUMP
    {  72,  83,  7 },   // FLIP
    {  84,  94,  7 },   // SALUTE
    {  95, 111, 10 },   // FALLBACK
    { 112, 122,  7 },   // WAVE
    { 123, 134,  6 },   // POINT
    { 135, 153, 10 },   // CROUCH_STAND
    { 154, 159,  7 },   // CROUCH_WALK
    { 160, 168, 10 },   // CROUCH_ATTACK
    { 196, 172,  7 },   // CROUCH_PAIN
    { 173, 177,  5 },   // CROUCH_DEATH
    { 178, 183,  7 },   // DEATH_FALLBACK
    { 184, 189,  7 },   // DEATH_FALLFORWARD
    { 190, 197,  7 },   // DEATH_FALLBACKSLOW
    { 198, 198,  5 },   // BOOM
};


class CMD2Model
{
private:

	// texture coordinate index
	typedef struct
	{
	   short s;
	   short t;
	} stIndex_t;

	// info for a single frame point
	typedef struct
	{
	   unsigned char v[3];
	   unsigned char normalIndex;
	} framePoint_t;

	// information for a single frame
	typedef struct
	{
	   float scale[3];
	   float translate[3];
	   char name[16];
	   framePoint_t fp[1];
	} frame_t;

	// data for a single triangle
	typedef struct
	{
	   unsigned short meshIndex[3];		// vertex indices
	   unsigned short stIndex[3];		// texture coordinate indices
	} mesh_t;

	typedef struct
	{
	   int ident;			// identifies as MD2 file "IDP2"
	   int version;			// mine is 8
	   int skinwidth;		// width of texture
	   int skinheight;		// height of texture
	   int framesize;		// number of bytes per frame
	   int numSkins;		// number of textures
	   int numXYZ;			// number of points
	   int numST;			// number of texture
	   int numTris;			// number of triangles
	   int numGLcmds;
	   int numFrames;		// total number of frames
	   int offsetSkins;		// offset to skin names (64 bytes each)
	   int offsetST;		// offset of texture s-t values
	   int offsetTris;		// offset of triangle mesh
	   int offsetFrames;	// offset of frame data (points)
	   int offsetGLcmds;	// type of OpenGL commands to use
	   int offsetEnd;		// end of file
	} modelHeader_t;
private:

	int numFrames;			// number of model frames
	int numVertices;		// number of vertices
	int numTriangles;		// number of triangles
	int numST;				// number of skins
	int frameSize;			// size of each frame in bytes
	int currentFrame;		// current frame # in animation
	int nextFrame;			// next frame # in animation
	int interpol;			// percent through current frame
	mesh_t		*triIndex;	// triangle list
	coord_t		*st;			// texture coordinate list
	vector_t	*vertexList;
	vector_t	*interpolList;	// hold animated/interpolated vertices

	md2state_t modelState;		// current model animation state

public:

    CMD2Model();
    ~CMD2Model();

    int  LoadModel(TCHAR *modelFile);
	void Unload();

    void Render();
	void Update(int delta);
	void Animate();

	void SetState(md2state_t state);
	int GetState();
};

#endif