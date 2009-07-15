
#include "sample.h"

void ObjectCreateCube(object_t& object)
{
	object.vertexList=new vector_t[8];
	object.numVertices=1;
	object.meshList=new mesh_t[6];
	object.numMesh=6;
	object.uvList=new coord_t[4];
	object.numTextureCoord=4;

	// quad 1
	object.vertexList[0].x= -128;	
	object.vertexList[0].y= -128;
	object.vertexList[0].z= -128;

	object.vertexList[1].x=  128;
	object.vertexList[1].y= -128;
	object.vertexList[1].z= -128;

	object.vertexList[2].x=  128;
	object.vertexList[2].y=  128;
	object.vertexList[2].z= -128;

	object.vertexList[3].x= -128;
	object.vertexList[3].y=  128;
	object.vertexList[3].z= -128;

	// quad 2
	object.vertexList[4].x= -128;	
	object.vertexList[4].y= -128;
	object.vertexList[4].z=  128;

	object.vertexList[5].x=  128;
	object.vertexList[5].y= -128;
	object.vertexList[5].z=  128;

	object.vertexList[6].x=  128;
	object.vertexList[6].y=  128;
	object.vertexList[6].z=  128;

	object.vertexList[7].x= -128;
	object.vertexList[7].y=  128;
	object.vertexList[7].z=  128;

	// face 1 (front)
	object.meshList[0].vertexIndex[0]=0;
	object.meshList[0].vertexIndex[1]=1;
	object.meshList[0].vertexIndex[2]=2;
	object.meshList[0].vertexIndex[3]=3;

	object.meshList[0].uvIndex[0]=0;
	object.meshList[0].uvIndex[1]=1;
	object.meshList[0].uvIndex[2]=2;
	object.meshList[0].uvIndex[3]=3;

	// face 2 (top)
	object.meshList[1].vertexIndex[0]=0;
	object.meshList[1].vertexIndex[1]=4;
	object.meshList[1].vertexIndex[2]=5;
	object.meshList[1].vertexIndex[3]=1;

	object.meshList[1].uvIndex[0]=0;
	object.meshList[1].uvIndex[1]=1;
	object.meshList[1].uvIndex[2]=2;
	object.meshList[1].uvIndex[3]=3;

	// face 3 (back)
	object.meshList[2].vertexIndex[0]=5;
	object.meshList[2].vertexIndex[1]=4;
	object.meshList[2].vertexIndex[2]=7;
	object.meshList[2].vertexIndex[3]=6;

	object.meshList[2].uvIndex[0]=0;
	object.meshList[2].uvIndex[1]=1;
	object.meshList[2].uvIndex[2]=2;
	object.meshList[2].uvIndex[3]=3;

	// face 4 (bottom)
	object.meshList[3].vertexIndex[0]=3;
	object.meshList[3].vertexIndex[1]=2;
	object.meshList[3].vertexIndex[2]=6;
	object.meshList[3].vertexIndex[3]=7;

	object.meshList[3].uvIndex[0]=0;
	object.meshList[3].uvIndex[1]=1;
	object.meshList[3].uvIndex[2]=2;
	object.meshList[3].uvIndex[3]=3;

	// face 5 (left)
	object.meshList[4].vertexIndex[0]=4;
	object.meshList[4].vertexIndex[1]=0;
	object.meshList[4].vertexIndex[2]=3;
	object.meshList[4].vertexIndex[3]=7;

	object.meshList[4].uvIndex[0]=0;
	object.meshList[4].uvIndex[1]=1;
	object.meshList[4].uvIndex[2]=2;
	object.meshList[4].uvIndex[3]=3;

	// face 6 (right)
	object.meshList[5].vertexIndex[0]=1;
	object.meshList[5].vertexIndex[1]=5;
	object.meshList[5].vertexIndex[2]=6;
	object.meshList[5].vertexIndex[3]=2;

	object.meshList[5].uvIndex[0]=0;
	object.meshList[5].uvIndex[1]=1;
	object.meshList[5].uvIndex[2]=2;
	object.meshList[5].uvIndex[3]=3;

	// texture coordinates
	object.uvList[0].x=0;
	object.uvList[0].y=0;
	object.uvList[1].x=31;
	object.uvList[1].y=0;
	object.uvList[2].x=31;
	object.uvList[2].y=31;
	object.uvList[3].x=0;
	object.uvList[3].y=31;
}

void ObjectDestroy(object_t& object)
{
	delete [] object.meshList;
	delete [] object.vertexList;
	delete [] object.uvList;
}

void ObjectDraw(object_t& object)
{
	int i,j;	
	int index;
	int tindex;
	pixel_t colors[8]={
		RGB_SET(31,0,0),
		RGB_SET(0,63,0),
		RGB_SET(0,0,31),
		RGB_SET(31,63,0),
		RGB_SET(0,63,31),
		RGB_SET(31,0,0),
		RGB_SET(0,31,0),
		RGB_SET(0,0,31)
	};

	u8 intensity[4]={ 63,32,16,8 };

	glBegin(DRAW_QUADS);
		for (i=0;i<object.numMesh;i++) {
			glIntensity(intensity[i%4]);
			for(j=0;j<4;j++) {				
				index=object.meshList[i].vertexIndex[j];
				tindex=object.meshList[i].uvIndex[j];				
				glTextureCoord(object.uvList[tindex]);
				glColor(colors[index]);
				glVertex(object.vertexList[index],index);
			}			
		}	
	glEnd();

}

