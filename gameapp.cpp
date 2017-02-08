
// #include "framework.h"

#include "gameapp.h"
#include <stdlib.h>

#include "renderbasic.h"

GameApp::GameApp(QWidget *parent) : QMainWindow(parent) {
}

GameApp::~GameApp() {
}

bool GameApp::GameInit() {

    resize(800,600);

    buffer = QImage(320*3, 240*3, QImage::Format_RGB16);
    m_buffer.pitch=buffer.width();
    m_buffer.width=buffer.width();
    m_buffer.height=buffer.height();
    m_buffer.pixels = (ppixel_t)buffer.bits();
    // m_buffer.pixels = (ppixel_t) malloc(sizeof(pixel_t)* m_buffer.pitch*m_buffer.height);

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
    // m_model.SetState(MD2_IDLE);
    m_model.SetState(MD2_RUN);
    m_model.Update(0);  

    FullPathName(_T("font.bmp"),pathname);
    SurfaceImage(m_fonts,pathname);
    m_text.SetTiles(&m_fonts,8,8,true);

    VectorInit(m_pos,0,0,-2<<8);

    ObjectCreateCube(m_cube);

    setCentralWidget(&label);
    
    timer.setInterval(0);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));

    return true;
}

void GameApp::GameEnd() {
    ObjectDestroy(m_cube);
    glShutdown();
}
// 
void GameApp::GameLoop() {   
    static int i=220;
    static int l=0;
    static int ll=1;

    l+=ll;
    if (l>62) ll=-1;
    if (l<1) ll=1;

    glClear(CLEAR_FRAME);

    glCamera(m_pos,0,90);

    // glPolygonMode(POLYGON_FRAMED);
    glEnable(TEXTURE_MAPPING);
    // glEnable(LIGHT_SHADING);
    glEnable(VERTEX_CACHING);
    glEnable(Z_SORTING);

    glIdentity();
    glBindTexture(0);
    glRotate(0,i,0);
    // ObjectDraw(m_cube);

    glIdentity();
    glBindTexture(1);
    glIntensity(63);
    // glIntensity(l);
    glScale(FPRECIP(14),FPRECIP(14),FPRECIP(14));
    glRotate(i,0,270);
    glTranslate(0,256,0);

    m_model.Render();
    m_model.Update(5126);

    RenderLine(&m_buffer,
        10,10,80,80,
        RGB_SET(31,63,31));

    #if 0
    static TCHAR sfps[128]=_T("");
    static int      m_FPSCounter;      // FPS counter
    static u32 m_FPSTicks[16];    // Ticks for last 16 frames
    m_FPSTicks[ m_FPSCounter & 15 ] = 0; // GetTickCount();
    if (m_FPSCounter > 15) {
        u32 totalTime = m_FPSTicks[ m_FPSCounter & 15 ] - m_FPSTicks[ (m_FPSCounter+1) & 15 ];
        if (totalTime == 0) totalTime = 1;
        u32 fps  = 16000 / totalTime;
        sprintf(sfps,_T("%4d"),fps);
        // m_text.DisplayText(m_buffer,sfps,10,10,2);
    }
    ++m_FPSCounter;

    pstats_t stats=glGetStats();
    sprintf(sfps,_T("%4d\n%4d\n%4d\n%4d"),
            stats->vertices,
            stats->verticesCalculated,
            stats->faces,
            stats->facesRendered);

    // m_text.DisplayText(m_buffer,sfps,280,10,2);

    if (stats->facesRendered>0)
        TRACES(sfps);
    #endif 

    // m_display->Swap();

    pstats_t stats=glGetStats();
    DbgTrace("(%d %d %d) %d %d %d\n", m_pos.x, m_pos.y, m_pos.z, i, stats->vertices, stats->verticesCalculated);

    pcamera_t cam=glGetCamera();
    vector_t t=cam->target;
    t.x=t.x>>12;    
    t.y=t.y>>12;
    t.z=t.z>>12;

    if (m_keys == 19) {
       m_pos=VectorAdd(m_pos,t);
   }
   if (m_keys == 21) {         
       m_pos=VectorSubtract(m_pos,t);
   }
   if (m_keys == 18) {
       i++;
       if (i>358) i-=360;          
   }
   if (m_keys == 20) {
       i--;
       if (i<0) i+=360;    
   }

   glResetStats();

   label.setPixmap(QPixmap::fromImage(buffer));

}

void GameApp::keyPressEvent(QKeyEvent* ke)
{
    m_keys = ke->key() & 0xff;
    GameLoop();

    QMainWindow::keyPressEvent(ke);
}

void GameApp::keyReleaseEvent(QKeyEvent* ke)
{
    m_keys=0;
    QMainWindow::keyReleaseEvent(ke);
}

void GameApp::timeout()
{
    GameLoop();
}

