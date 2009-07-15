
#include "framework.h"

#include "md2.h"
#include "renderbasic.h"
#include "polygon.h"

#include "surface.h"
#include "fonttiles.h"
#include "sample.h"
#include "trace.h"

CComModule _Module;

using namespace PHAL;

class GameApp : public Game
{
public:
	GameApp() {
		m_config.parameters.m_orientation=ORIENTATION_NORMAL;	
	}

	~GameApp() {
	}

	bool GameInit() {
		uint16_t *pixels;
		Surface *buffer;
		if (!(buffer = m_display->GetBackBuffer()))
			return false;
		if (!(pixels = buffer->GetPixels()))
			return false;

		m_buffer.pixels=(ppixel_t)pixels;
		m_buffer.pitch=buffer->GetPitch();
		m_buffer.width=buffer->GetWidth();
		m_buffer.height=buffer->GetHeight();

		glInitialize(m_buffer.width,m_buffer.height);		
		glSetTarget(&m_buffer);

		TCHAR pathname[MAX_PATH];		
		FullPathName(_T("texture2.bmp"),pathname);
		glAddTexture(pathname,TEXTURE_16BIT);		

		FullPathName(_T("orgo.bmp"),pathname);
		glAddTexture(pathname,TEXTURE_16BIT);
		//glAddTexture(pathname,TEXTURE_8BIT);
		//PaletteInit(*glGetPalette(),pathname);
		
		FullPathName(_T("orgo.md2"),pathname);
		m_model.LoadModel(pathname);
		m_model.SetState(MD2_IDLE);
		//m_model.SetState(MD2_RUN);
		m_model.Update(0);	

		FullPathName(_T("font.bmp"),pathname);
		SurfaceImage(m_fonts,pathname);
		m_text.SetTiles(&m_fonts,8,8,true);

		VectorInit(m_pos,0,0,-2<<8);

		ObjectCreateCube(m_cube);

		return true;
	}

	void GameEnd() {
		ObjectDestroy(m_cube);
		glShutdown();
		SurfaceFree(m_fonts);
	}

	void GameLoop() {	
		static int i=220;
		static int l=0;
		static int ll=1;

		l+=ll;
		if (l>62) ll=-1;
		if (l<1) ll=1;

		glClear(CLEAR_FRAME);

		glCamera(m_pos,0,90);

		//glPolygonMode(POLYGON_FRAMED);
		glEnable(TEXTURE_MAPPING);
		glEnable(LIGHT_SHADING);
		glEnable(VERTEX_CACHING);
		glEnable(Z_SORTING);

		glIdentity();
		glBindTexture(0);
		glRotate(0,i,0);
		//ObjectDraw(m_cube);

		glIdentity();
		glBindTexture(1);
		//glIntensity(63);
		glIntensity(l);
		glScale(FPRECIP(14),FPRECIP(14),FPRECIP(14));
		glRotate(i,0,270);
		glTranslate(0,256,0);
	
		m_model.Render();
		m_model.Update(5126);


		static TCHAR sfps[128]=_T("");
		static int      m_FPSCounter;      // FPS counter
		static uint32_t m_FPSTicks[16];    // Ticks for last 16 frames
		m_FPSTicks[ m_FPSCounter & 15 ] = GetTickCount();
		if (m_FPSCounter > 15) {
			uint32_t totalTime = m_FPSTicks[ m_FPSCounter & 15 ] - m_FPSTicks[ (m_FPSCounter+1) & 15 ];
			if (totalTime == 0) totalTime = 1;
			uint32_t fps  = 16000 / totalTime;
			_stprintf(sfps,_T("%4d"),fps);
			m_text.DrawText(m_buffer,sfps,10,10,2);
		}
		++m_FPSCounter;

		pstats_t stats=glGetStats();
		_stprintf(sfps,_T("%4d\n%4d\n%4d\n%4d"),
				stats->vertices,
				stats->verticesCalculated,
				stats->faces,
				stats->facesRendered);
		m_text.DrawText(m_buffer,sfps,280,10,2);
		glResetStats();


		m_display->Swap();

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
	}

	void ButtonDown( int button ) {
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

	void ButtonUp( int button ) {
		m_keys=0;
	}

	int m_keys;
	vector_t m_pos;	
	framebuffer_t m_buffer;

	FontTiles m_text;
	surface_t m_fonts;

	object_t m_cube;
	CMD2Model m_model;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	_Module.Init(0,hInstance);

	GameApp app;
	app.Run();

    return 0;
}
