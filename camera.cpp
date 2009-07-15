
#include "camera.h"
#include "maths.h"
#include "trace.h"

void CameraInit(camera_t& cam,vector_t& pos,vector_t& u,vector_t& v,vector_t& n)
{
	cam.pos=pos;
	cam.u=u;
	cam.v=v;
	cam.n=n;
	CameraBuildMatrix(cam);
}

void CameraInit(camera_t& cam,int x,int y,int z,int heading,int elevation)
{
	vector_t v;
	VectorInit(v,x,y,z);
	CameraInit(cam,v,heading,elevation);
}

void CameraInit(camera_t& cam,vector_t& pos,int heading,int elevation)
{
	cam.pos=pos;
	cam.heading=heading;
	cam.elevation=elevation;

	int sinPhi=FPSIN(cam.elevation);
	int cosPhi=FPCOS(cam.elevation);
	int sinTheta=FPSIN(cam.heading);
	int cosTheta=FPCOS(cam.heading);

	// compute look target on a unit sphere
	cam.target.x=FPMUL( FPMUL(-(FPONE),sinPhi) , sinTheta );
	cam.target.y=FPMUL( FPONE,cosPhi );
	cam.target.z=FPMUL( FPMUL(FPONE,sinPhi) , cosTheta );

	// compute n; n=target-pos
	VectorSubtract(cam.target,cam.pos,cam.n);

	// init v; v={0,1,0}
	VectorInit(cam.v,0,FPONE,0);

	// compute u; u=(v*n)
	VectorCross(cam.v,cam.n,cam.u);

	// re-compute v; v=(n*u)
	VectorCross(cam.n,cam.u,cam.v);

	// normalize
	VectorNormalize(cam.u);
	VectorNormalize(cam.v);
	VectorNormalize(cam.n);

	CameraBuildMatrix(cam);
}

// Build camera matrix
void CameraBuildMatrix(camera_t& cam)
{
	matrix_t inv;
	// step 1. inverse matrix
	MatrixInit(inv,
		FPONE,	0,	0,	0,
		0,	FPONE,	0,	0,
		0,	0,	FPONE,	0,
		-cam.pos.x,	-cam.pos.y,	-cam.pos.z,	FPONE);

	// step 2. uvn matrix
	matrix_t uvn;
	MatrixInit(uvn,
		cam.u.x,	cam.v.x,	cam.n.x,	0,
		cam.u.y,	cam.v.y,	cam.n.y,	0,
		cam.u.z,	cam.v.z,	cam.n.z,	0,
		0,			0,			0,			FPONE);

	//MatrixTrace(uvn);

	// step 3. mcam=inv*uvn
	MatrixMultiply(inv, uvn, cam.matrix);
}

void ProjectionInit(projection_t& p,int distance,int aspect,int nearz,int farz)
{
	p.nearz=nearz;
	p.farz=farz;
	p.distance=distance;
	p.aspect=aspect;
	p.dx=distance;
	p.dy=(FPMUL(distance<<FPP,aspect))>>FPP;
	p.viewwidth=320;
	p.viewheight=240;
}

void ProjectionViewport(projection_t& p,int width,int height)
{
	p.viewwidth=width;
	p.viewheight=height;
}

void ProjectionVertex(projection_t& p,vector_t& v,coord_t&vr)
{
	if (v.z<=0) {
		vr.x=0;
		vr.y=0;
		return;
	}
	vr.x =  ((int)(v.x*p.dx)/(int)v.z) + (p.viewwidth>>1);
	vr.y =  ((int)(v.y*p.dy)/(int)v.z) + (p.viewheight>>1) + 20;
}
