
#include "tiles.h"
#include "renderbasic.h"
#include "trace.h"

inline void SetRect(rect_t *r, int lt, int tp, int rt, int bt)
{ r->left=lt; r->right=rt; r->top=tp; r->bottom=bt; }

Tiles::Tiles()
{
	m_surface=NULL;
}

Tiles::~Tiles()
{
	if (m_surface && !m_shared)
		delete m_surface;
}

bool Tiles::SetTiles(pframebuffer_t surface, int width, int height, bool shared)
{
	if (m_surface)
		delete m_surface;

	m_tileWidth=width;
	m_tileHeight=height;
	m_offsetX=width>>1;
	m_offsetY=height>>1;

	m_shared=shared;

	m_surface=surface;
	//m_surface->SetColorMask(Color(255,0,255));
	m_width=m_surface->width;
	m_height=m_surface->height;

	return (m_surface!=NULL);
}

void Tiles::SetColorMask(pixel_t p)
{
	if (!m_surface)
		return;

	//m_surface->SetColorMask(p);
}

bool Tiles::GetRect(int tx,int ty,rect_t &rect_t)
{
	rect_t.left=(tx * m_tileWidth);
	rect_t.top =(ty * m_tileHeight);
	rect_t.right=rect_t.left + m_tileWidth;
	rect_t.bottom=rect_t.top + m_tileHeight;
	
	if (rect_t.left < 0 || rect_t.top < 0)
		return false;

	if ((int)rect_t.right > m_width || (int)rect_t.bottom > m_height)
		return false;

	return true;
}

void Tiles::DrawTile(framebuffer_t& buffer, int tx, int ty, int x,int y)
{
	if (!m_surface)
		return;

	rect_t rc;
	pixel_t c;
	if (GetRect(tx,ty,rc)) {
		for(int j=0;j<rc.bottom-rc.top;j++) {			
			for(int i=0;i<rc.right-rc.left;i++) {			
				c=m_surface->pixels[(rc.left+i)+((rc.top+j)*m_surface->width)];
				if (c!=63519)					
				RenderPixel(&buffer,x-m_offsetX+i,y-m_offsetY+j,c);
			}
		}
	}
}

void Tiles::DrawTile(framebuffer_t& buffer, int tx, int ty, int x, int y, double scale)
{
	if (!m_surface)
		return;

	rect_t rc;
	if (GetRect(tx,ty,rc)) {
		if (scale<0.5)
			scale=0.5;
		x-=(int)(m_offsetX * scale);
		y-=(int)(m_offsetY * scale);
		SetRect(&rc,x,y,x + (int)(m_tileWidth*scale),y + (int)(m_tileHeight*scale));
		DrawTile(buffer,tx,ty,rc);
	}
}

void Tiles::DrawTile(framebuffer_t& buffer, int tx, int ty, int x, int y, double scale, float angle)
{
	if (!m_surface)
		return;

	rect_t rc;
	if (GetRect(tx,ty,rc)) {
		if (scale<0.5)
			scale=0.5;

		SetRect(&rc,0,0,(int)(m_tileWidth*scale),(int)(m_tileHeight*scale));

	//	Surface *s=buffer->CreateSurface(m_tileWidth*scale,m_tileHeight*scale);
	//	s->SetColorMask(m_surface->GetColorMask());
	//	buffer->SetRenderTarget(s);
	//	buffer->Clear(m_surface->GetColorMask());
	//	DrawTile(buffer,tx,ty,rc);
	//	buffer->SetRenderTarget(NULL);
	//	buffer->BlitRotated(x,y,angle,s);
	}
}

void Tiles::DrawTile(framebuffer_t& buffer, int tx, int ty, rect_t rStretch)
{
	if (!m_surface)
		return;

	rect_t rc;
	if (GetRect(tx,ty,rc)) {
		// buffer->BlitStretch(rStretch, m_surface, &rc);
	}
}