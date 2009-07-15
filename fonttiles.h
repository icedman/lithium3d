
#ifndef FONTTILES_H
#define FONTTILES_H

#include "tiles.h"

class FontTiles : public Tiles
{
public:	

	enum {
		VERTICAL,
		HORIZONTAL
	};

	int m_orientation;
	int	m_xspacing;
	int	m_yspacing;
 
	FontTiles();
	~FontTiles();

	virtual int GetCharIndex(int charAscii);
	void SetSpacing(int sx, int sy);
	void DisplayChar(framebuffer_t& buffer, TCHAR c, int x, int y, int offset=0, int scale=1);
	void DisplayText(framebuffer_t& buffer, LPCTSTR text, int x,int y, int offset=0);
};

#endif //FONTTILES_H