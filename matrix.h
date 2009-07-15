
#ifndef _LITH_MATRIX_H_
#define _LITH_MATRIX_H_

#include "stdtypes.h"
#include "fixed.h"

#define MAX_MATRIX_STACK	32

typedef struct {
	union {
		int M[4][4];
		struct {
			int c00,c01,c02,c03;
			int c10,c11,c12,c13;
			int c20,c21,c22,c23;
			int c30,c31,c32,c33;
		};
	};
} matrix_t, *pmatrix_t;

typedef struct {
	matrix_t matrices[MAX_MATRIX_STACK];
	matrix_t *matrix;
} matrixStack_t, *pmatrixStack_t;

const matrix_t g_identity_matrix = {FPONE,0,0,0, 
                                    0,FPONE,0,0, 
                                    0,0,FPONE,0, 
                                    0,0,0,FPONE};

#define MatrixZero(m)		{memset((void *)(m), 0, sizeof(matrix_t));}
#define MatrixIdentity(m)	{memcpy((void *)(m), (void *)&g_identity_matrix, sizeof(matrix_t));}
#define MatrixCopy(m,src)	{memcpy((void *)(m), (void *)(src), sizeof(matrix_t)); }

void MatrixInit(matrix_t& m,
    int c00,int c01,int c02,int c03,
    int c10,int c11,int c12,int c13,
    int c20,int c21,int c22,int c23,
    int c30,int c31,int c32,int c33);
void MatrixAdd(matrix_t& ma,matrix_t& mb,matrix_t& mr);
void MatrixMultiply(matrix_t& ma,matrix_t& mb,matrix_t& mr);
void MatrixRotate(matrix_t& mrot,int ax,int ay,int az);
void MatrixTranslate(matrix_t& mtrans,int tx,int ty,int tz);
void MatrixScale(matrix_t& mscale,int sx,int sy,int sz);

void MatrixStackInit(matrixStack_t& stack);
bool MatrixStackPush(matrixStack_t& stack);
bool MatrixStackPop(matrixStack_t& stack);

void MatrixTrace(matrix_t& m);

#endif // _LITH_MATRIX_H_