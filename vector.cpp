
#include "vector.h"
#include "fixed.h"
#include "maths.h"

#include "trace.h"

void CoordInit(coord_t& c,int x,int y)
{
	c.x=x;
	c.y=y;
}

void VectorInit(vector_t& v,int x,int y,int z)
{
	v.x=x;
	v.y=y;
	v.z=z;
}

void VectorAdd(vector_t& va,vector_t& vb,vector_t& vr)
{
	vr.x=va.x+vb.x;
	vr.y=va.y+vb.y;
	vr.z=va.z+vb.z;
}

vector_t VectorAdd(vector_t& va,vector_t& vb)
{
	vector_t vr;
	vr.x=va.x+vb.x;
	vr.y=va.y+vb.y;
	vr.z=va.z+vb.z;
	return (vr);
}

void VectorSubtract(vector_t& va,vector_t& vb,vector_t& vr)
{
	vr.x=va.x-vb.x;
	vr.y=va.y-vb.y;
	vr.z=va.z-vb.z;
}

vector_t VectorSubtract(vector_t& va,vector_t& vb)
{
	vector_t vr;
	vr.x=va.x-vb.x;
	vr.y=va.y-vb.y;
	vr.z=va.z-vb.z;
	return (vr);
}

// s - is a fixed point number
void VectorScale(vector_t& v,vector_t& vr,int s)
{
	vr.x=FPMUL(v.x,s);
	vr.y=FPMUL(v.y,s);
	vr.z=FPMUL(v.z,s);
}

vector_t VectorScale(vector_t& v,int s)
{
	vector_t vr;
	vr.x=FPMUL(v.x,s);
	vr.y=FPMUL(v.y,s);
	vr.z=FPMUL(v.z,s);
	return (vr);
}

int VectorDot(vector_t& va,vector_t& vb)
{
	return FPMUL( vb.x, va.x ) + FPMUL( vb.y, va.y ) + FPMUL( vb.z, va.z );
}

void VectorCross(vector_t& va,vector_t& vb,vector_t& vr)
{
	vr.x = FPMUL( va.y, vb.z ) - FPMUL( va.z, vb.y );
	vr.y = FPMUL( va.z, vb.x ) - FPMUL( va.x, vb.z ); 
	vr.z = FPMUL( va.x, vb.y ) - FPMUL( va.y, vb.x );
}

vector_t VectorCross(vector_t& va,vector_t& vb)
{
	vector_t vr;
	vr.x = FPMUL( va.y, vb.z ) - FPMUL( va.z, vb.y );
	vr.y = FPMUL( va.z, vb.x ) - FPMUL( va.x, vb.z ); 
	vr.z = FPMUL( va.x, vb.y ) - FPMUL( va.y, vb.x );
	return (vr);
}

void VectorNormalize(vector_t& v)
{
	double l = (double)VectorLength(v) / 65536.0f; 
	v.x = (int)((float)v.x / l);
	v.y = (int)((float)v.y / l);
	v.z = (int)((float)v.z / l);
}

int VectorLength(vector_t& v)
{
	double fx = (double)v.x, fy = (double)v.y, fz = (double)v.z;
	return (int)sqrt( fx * fx + fy * fy + fz * fz);
}

void VectorTransform(vector_t& v, matrix_t& m,vector_t& vr)
{	
    for (int col=0; col < 3; col++) {
		int sum=0;
        for (int row=0; row<3; row++) {
             sum+=FPMUL(v.M[row],m.M[row][col]);
		}
        // add in last element in column or w*m[3][col]; (w=1)
        sum+=m.M[3][col];
        vr.M[col] = sum;		
	}
}

vector_t VectorTransform(vector_t& v, matrix_t& m)
{
	vector_t vr;
    for (int col=0; col < 3; col++) {
		int sum=0;
        for (int row=0; row<3; row++) {
             sum+=(v.M[row]*m.M[row][col]);
		}
        // add in last element in column or w*m[3][col]; (w=1)
        sum+=m.M[3][col];
        vr.M[col] = sum;
	}
	return (vr);
}