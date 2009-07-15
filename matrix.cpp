
#include "matrix.h"
#include "maths.h"
#include "utils.h"

#include "trace.h"

void MatrixInit(matrix_t& m,
    int c00,int c01,int c02,int c03,
    int c10,int c11,int c12,int c13,
    int c20,int c21,int c22,int c23,
    int c30,int c31,int c32,int c33)
{
	m.c00=c00;	m.c01=c01;	m.c02=c02;	m.c03=c03;
	m.c10=c10;	m.c11=c11;	m.c12=c12;	m.c13=c13;
	m.c20=c20;	m.c21=c21;	m.c22=c22;	m.c23=c23;
	m.c30=c30;	m.c31=c31;	m.c32=c32;	m.c33=c33;
}

void MatrixAdd(matrix_t& ma,matrix_t& mb,matrix_t& mr)
{
	for (int row=0; row<4; row++) {
		for (int col=0; col<4; col++) {        
			mr.M[row][col] = ma.M[row][col] + mb.M[row][col];
        }
    } 
}

void MatrixMultiply(matrix_t& ma,matrix_t& mb,matrix_t& mr)
{
	for (int row=0; row<4; row++) {		
		for (int col=0; col<4; col++) {
			int sum=0;
			for (int index=0; index<4; index++) {
				sum+=( FPMULH(ma.M[row][index],mb.M[index][col]) );
			}
			mr.M[row][col]=sum;
        }
    } 

}

#define ROTSEQX (1<<1)
#define ROTSEQY (1<<2)
#define ROTSEQZ (1<<3)
void MatrixRotate(matrix_t& mrot,int ax,int ay,int az)
{
	matrix_t mx,my,mz,mtmp;
	int sinTheta=0;
	int cosTheta=0;
	int rotSeq = 0;
	
	MatrixIdentity(&mrot);

	if (ax > 0)
	   rotSeq = rotSeq | ROTSEQX;

	if (ay > 0)
	   rotSeq = rotSeq | ROTSEQY;

	if (az > 0)
	   rotSeq = rotSeq | ROTSEQZ;

	if (rotSeq==0) return;

	if (rotSeq & ROTSEQX) {

		cosTheta = FPCOS(ax);
		sinTheta = FPSIN(ax);

		MatrixInit(mx, 
				FPONE,	0,		0,		0,
				0,    cosTheta,  sinTheta,	0,
				0,   -sinTheta, cosTheta,	0,
				0,		0,		0,		FPONE);

		if (rotSeq==ROTSEQX) {
			MatrixCopy(&mrot,&mx);
			return;
		}
	}

	if (rotSeq & ROTSEQY) {

		cosTheta = FPCOS(ay);
		sinTheta = FPSIN(ay);

		MatrixInit(my,
				cosTheta, 0, -sinTheta, 0,  
				0,		FPONE,	0,		0,
				sinTheta, 0, cosTheta,  0,
				0,		0,		0,		FPONE);

		if (rotSeq==ROTSEQY) {
			MatrixCopy(&mrot,&my);
			return;
		}
	}

	if (rotSeq & ROTSEQZ) {
		
		cosTheta = FPCOS(az);
		sinTheta = FPSIN(az);

		MatrixInit(mz,
				cosTheta, sinTheta,		0, 0,  
				-sinTheta, cosTheta,	0, 0,
				0,		0,		FPONE,	0,
				0,		0,		0,		FPONE);

		if (rotSeq==ROTSEQZ) {
			MatrixCopy(&mrot,&mz);
			return;
		}
	}

	if (rotSeq & ROTSEQX) {
		if (rotSeq & ROTSEQY) {
			if (rotSeq & ROTSEQZ) {
				MatrixMultiply(mx,my,mtmp);
				MatrixMultiply(mtmp,mz,mrot);
				return;
			}
			MatrixMultiply(mx,my,mrot);
			return;			
		}
	}

	if (rotSeq & ROTSEQZ) {
		if (rotSeq & ROTSEQX) {
			MatrixMultiply(mx,mz,mrot);
			return;
		}
		MatrixMultiply(my,mz,mrot);
		return;
	}
}

void MatrixTranslate(matrix_t& mtrans,int tx,int ty,int tz)
{
	MatrixInit(mtrans,
		FPONE,	0,	0,	0,
		0,	FPONE,	0,	0,
		0,	0,	FPONE,	0,
		tx,	ty,tz,	FPONE);
}

void MatrixScale(matrix_t& mscale,int sx,int sy,int sz)
{
	MatrixInit(mscale,
		sz,	0,	0,	0,
		0,	sy,	0,	0,
		0,	0,	sz,	0,
		0,	0,	0,	FPONE);
}

void MatrixStackInit(matrixStack_t& stack)
{
	stack.matrix=&stack.matrices[0];
	MatrixIdentity(stack.matrix);
}

bool MatrixStackPush(matrixStack_t& stack)
{
	if (stack.matrix==&stack.matrices[MAX_MATRIX_STACK-1])
		return 0;

	MatrixCopy(stack.matrix+1,stack.matrix);
	stack.matrix++;

	return 1;
}

bool MatrixStackPop(matrixStack_t& stack)
{
	if (stack.matrix==&stack.matrices[0])
		return 0;

	stack.matrix--;

	return 1;
}

void MatrixTrace(matrix_t& m)
{
	// combine world and camera matrix
	TRACES(_T("-------------"));
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			DbgTrace(_T("%4d "),m.M[i][j]);
		}
		DbgTrace(_T("\n"));
	}
}