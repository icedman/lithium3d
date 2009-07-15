
#include "fonttiles.h"

FontTiles::FontTiles()
{
	m_xspacing=0;
	m_yspacing=0;
	m_orientation=VERTICAL;
}

FontTiles::~FontTiles()
{
}

void FontTiles::SetSpacing(int sx, int sy)
{
	m_xspacing=sx;
	m_yspacing=sy;
}

int FontTiles::GetCharIndex(int charAscii)
{
	int index=0;
	switch (charAscii) {
	case '.':
		index = 37;		
		break;
	case '?':
		index = 38;
		break;
	case ':':
		index = 39;
		break;
	case '\'':
		index = 40;
		break;
	default:		
   		if ((charAscii >= 'A') && (charAscii <= 'Z')) {
   			index = charAscii - 'A' + 11; 
		} else if ((charAscii >= 'a') && (charAscii <= 'z')) {
			index = charAscii - 'a' + 11; 
		} else if ((charAscii >= '0') && (charAscii <= '9')) {
			index = charAscii - '0' + 1;
		}
		break;
	}
	return index;
}

void FontTiles::DisplayText(framebuffer_t& buffer, LPCTSTR text, int x,int y, int offset)
{
	if (!m_surface)
		return;
	
	int charIndex;
	int charAscii;
   
	int index;
	int indexX=0;
	int indexY=0;

	charIndex=0;
	charAscii=text[charIndex];
	while (charAscii!='\0') {

		index=GetCharIndex(charAscii);

		if (m_orientation==VERTICAL) 
			DrawTile(buffer, offset, index, x + (indexX * (m_tileWidth + m_xspacing)), y + (indexY * (m_tileHeight + m_yspacing)));
		else
			DrawTile(buffer, index, offset , x + (indexX * (m_tileWidth + m_xspacing)), y + (indexY * (m_tileHeight + m_yspacing)));

		indexX++;
		charIndex++;
		charAscii=text[charIndex];
		if (charAscii=='\n') {
			indexX=0;
			indexY++;
			charIndex++;
			charAscii=text[charIndex];
		}
	}
}

void FontTiles::DisplayChar(framebuffer_t& buffer, TCHAR c, int x, int y, int offset,int scale)
{
	int index=GetCharIndex(c);
	if (scale==1) {
		if (m_orientation==VERTICAL) 
			DrawTile(buffer,offset,index,x,y);
		else
			DrawTile(buffer,index,offset,x,y);
	} else {
		if (m_orientation==VERTICAL) 
			DrawTile(buffer,offset,index,x,y,scale);
		else
			DrawTile(buffer,index,offset,x,y,scale);
	}
}