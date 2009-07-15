//////////////////////////////////////////////////////////////////////////////
//
// Minimal
// Copyright 2004 by Thierry Tremblay
//
// Minimal Sample for PocketHAL
// For more info: http://www.droneship.com
//
//////////////////////////////////////////////////////////////////////////////

#include "l3d.h"
#include "../common/utility.h"



//////////////////////////////////////////////////////////////////////////////
//
// Declare the program's entry point
//
//////////////////////////////////////////////////////////////////////////////

PHAL_DECLARE_ENTRY_POINT( MinimalGame );



//////////////////////////////////////////////////////////////////////////////
//
// MinimalGame
//
//////////////////////////////////////////////////////////////////////////////

MinimalGame::MinimalGame()
{
	m_config.m_appName     = TEXT("Minimal");
	m_config.m_orientation = ORIENTATION_ROTATE90CW;//ORIENTATION_NORMAL;
}



bool MinimalGame::OnInitialize()
{
	if (!Game::OnInitialize())
		return false;


	Display* display = GetDisplay();


	m_buffer.width=display->GetParameters().m_width;
	m_buffer.height=display->GetParameters().m_height;
	glInitialize(m_buffer.width,m_buffer.height);		
	glSetTarget(&m_buffer);


	TCHAR pathname[MAX_PATH];		
	//FullPathName(_T("texture2.bmp"),pathname);
	//glAddTexture(pathname,TEXTURE_16BIT);		

	FullPathName(_T("orgo.bmp"),pathname);
	glAddTexture(pathname,TEXTURE_16BIT);
	//glAddTexture(pathname,TEXTURE_8BIT);
	PaletteInit(*glGetPalette(),pathname);

	FullPathName(_T("orgo.md2"),pathname);
	m_model.LoadModel(pathname);
	m_model.SetState(MD2_IDLE);
	m_model.SetState(MD2_RUN);
	m_model.Update(0);	

	FullPathName(_T("baul.md2"),pathname);
	m_model2.LoadModel(pathname);
	m_model2.SetState(MD2_RUN);
	m_model2.Update(0);	

	FullPathName(_T("font.bmp"),pathname);
	SurfaceImage(m_fonts,pathname);
	m_text.SetTiles(&m_fonts,8,8,true);

	VectorInit(m_pos,0,-256,-2<<8);

	ObjectCreateCube(m_cube);


	return true;
}



bool MinimalGame::OnGameLoop()
{
	Display* display = GetDisplay();

	if (display->BeginScene())
	{

		Surface* buffer = display->GetBackBuffer();
		m_buffer.pixels=(ppixel_t)buffer->GetPixels();
		m_buffer.pitch=buffer->GetPitch();


		static int i=220;
		static int l=0;
		static int ll=1;

		l+=ll;
		if (l>62) ll=-1;
		if (l<10) ll=1;

		glClear(CLEAR_FRAME);

		glCamera(m_pos,0,60);

		//glPolygonMode(POLYGON_FRAMED);
		//glEnable(TEXTURE_MAPPING);
		//glEnable(LIGHT_SHADING);
		glEnable(VERTEX_CACHING);
		glEnable(Z_SORTING);

		glIdentity();
		glBindTexture(0);
		glRotate(0,i,0);
		//ObjectDraw(m_cube);

		glIdentity();
		glBindTexture(1);
		glIntensity(63);
		//glIntensity(l);
		glScale(FPRECIP(14),FPRECIP(14),FPRECIP(14));
		glRotate(i,0,270);


		glTranslate(0,256,0);	
		m_model.Render();

		glTranslate(256, 0,0);	
		//m_model2.Render();

		m_model.Update(3200);
		m_model2.Update(3200);


		m_text.DisplayText(m_buffer,GetFPSString(),10,10,2);

		static TCHAR sfps[128]=_T("");
		pstats_t stats=glGetStats();
		_stprintf(sfps,_T("%4d\n%4d\n%4d\n%4d"),
			stats->vertices,
			stats->verticesCalculated,
			stats->faces,
			stats->facesRendered);
		m_text.DisplayText(m_buffer,sfps,280,10,2);
		glResetStats();

		pcamera_t cam=glGetCamera();
		vector_t t=cam->target;
		t.x=t.x>>12;	
		t.y=t.y>>12;
		t.z=t.z>>12;

		if (m_keys == VK_UP) {
			m_pos=VectorAdd(m_pos,t);
		}
		if (m_keys == VK_DOWN) {			
			m_pos=VectorSubtract(m_pos,t);
		}
		if (m_keys == VK_LEFT) {
			i++;
			if (i>358) i-=360;			
		}
		if (m_keys == VK_RIGHT) {
			i--;
			if (i<0) i+=360;			
		}


		display->Swap();

	}

	return Game::OnGameLoop();
}

void MinimalGame::OnKeyDown( int button ) {
	if (button==VK_UP) {
		m_keys=VK_UP;
	}
	if (button==VK_DOWN) {
		m_keys=VK_DOWN;
	}
	if (button==VK_LEFT) {
		m_keys=VK_LEFT;
	}
	if (button==VK_RIGHT) {
		m_keys=VK_RIGHT;
	}
}

void MinimalGame::OnKeyUp( int button ) {
	m_keys=0;
}

void MinimalGame::OnShutdown() {
	ObjectDestroy(m_cube);
	glShutdown();
	SurfaceFree(m_fonts);
}