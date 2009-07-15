
#ifndef _LITH_VECTOR_H_
#define _LITH_VECTOR_H_

#include "stdtypes.h"
#include "matrix.h"
#include "utils.h"

typedef struct {
    union {
        s32 M[3];
        struct {
	        s32 x,y,z;
        };
    };
} vector_t, *pvector_t;

typedef struct {
	s16 x,y;
} coord_t, *pcoord_t;

void CoordInit(coord_t& c,int x,int y);

#define VectorZero(v) {v.x=0;v.y=0;v.z=0;}
#define VectorCopy(v,src)	{memcpy((void *)(v), (void *)(src), 12); }
#define CoordCopy(v,src)	{memcpy((void *)(v), (void *)(src), 4); }

void VectorInit(vector_t& v,int x,int y,int z);
void VectorAdd(vector_t& va,vector_t& vb,vector_t& vr);
void VectorSubtract(vector_t& va,vector_t& vb,vector_t& vr);
void VectorScale(vector_t& v,vector_t& vr,int s);
void VectorCross(vector_t& va,vector_t& vb,vector_t& vr);

vector_t VectorAdd(vector_t& va,vector_t& vb);
vector_t VectorSubtract(vector_t& va,vector_t& vb);
vector_t VectorScale(vector_t& v,int s);
vector_t VectorCross(vector_t& va,vector_t& vb);

void VectorNormalize(vector_t& v);
int VectorLength(vector_t& v);
int VectorDot(vector_t& va,vector_t& vb);

void VectorTransform(vector_t& v, matrix_t& m,vector_t& vr);
vector_t VectorTransform(vector_t& v, matrix_t& m);

#endif // _LITH_VECTOR_H_