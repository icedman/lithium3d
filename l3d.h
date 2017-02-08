//////////////////////////////////////////////////////////////////////////////
//
// Minimal
// Copyright 2004 by Thierry Tremblay
//
// Minimal Sample for PocketHAL
// For more info: http://www.droneship.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_MINIMAL_H
#define INCLUDED_MINIMAL_H

// #include <PocketHAL/PocketHAL.h>
// #include "../common/game.h"

#include "lithium3d.h"

#include "md2.h"
#include "renderbasic.h"
#include "polygon.h"

#include "surface.h"
#include "fonttiles.h"
#include "sample.h"
#include "trace.h"

// using namespace PHAL;



//////////////////////////////////////////////////////////////////////////////
//
// MinimalGame
//
//////////////////////////////////////////////////////////////////////////////

class MinimalGame // : public Game
{
public:

    enum { UID = 0x0B6BE65F };

    MinimalGame();


protected:
    
    bool OnInitialize();            // Return true or false depending on success
    bool OnGameLoop();              // Game loop, return true to continue running or false to shutdown
	void OnKeyDown( int key );      // A key was pressed
    void OnKeyUp( int key );        // A key was released
	void OnShutdown();

private:

	int m_keys;
	vector_t m_pos;	
	framebuffer_t m_buffer;

	FontTiles m_text;
	surface_t m_fonts;

	object_t m_cube;
	CMD2Model m_model;
	CMD2Model m_model2;
};




#endif
