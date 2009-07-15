
#ifndef _LITH_TILES_H_
#define _LITH_TILES_H_

#include "framebuffer.h"
#include <windows.h>
#include <tchar.h>

class Tiles
{	
public:	
	int m_tileWidth;
	int m_tileHeight;
	int m_width;
	int m_height;

	bool m_shared;

	Tiles();
	~Tiles();

	pframebuffer_t operator()() { return m_surface; }
	void SetColorMask(pixel_t p);
	bool GetRect(int tx,int ty,rect_t &rect);
	bool SetTiles(pframebuffer_t surface, int width, int height, bool shared=false);
	void DrawTile(framebuffer_t& buffer, int tx, int ty, int x,int y);	
	void DrawTile(framebuffer_t& buffer, int tx, int ty, int x, int y,double scale);	
	void DrawTile(framebuffer_t& buffer, int tx, int ty, int x, int y,double scale,float angle);
	void DrawTile(framebuffer_t& buffer, int tx, int ty, rect_t rStretch);

public:	
	pframebuffer_t m_surface;

	int m_offsetX;
	int m_offsetY;
};

#endif // _LITH_TILES_H_