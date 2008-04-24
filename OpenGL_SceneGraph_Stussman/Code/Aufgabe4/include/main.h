/**************************************************/
/*                                                */
/*  Main Header Aufgabe 2                         */
/*                                                */
/**************************************************/
/*  Authors:                Reto Bollinger        */
/*                          bolliret@zhwin.ch     */
/*                                                */
/*                          Hanspeter Brühlmann   */
/*                          bruehhan@zhwin.ch     */
/*                                                */
/**************************************************/
/*  Date:                   15. October 2004      */
/**************************************************/

#ifndef _MAIN_H
#define _MAIN_H


//------ memory leaks -------//
#ifdef WIN32
  #define _CRTDBG_MAP_ALLOC
  #define _CRTDBG_MAPALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
#endif

//_CrtSetBreakAlloc(122); // to set a memory-allocation breakpoint in your code (for the 18th memory allocation)
//_crtBreakAlloc = 122;
//------    -------//

#ifdef WIN32 
  #include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 
 
#include <SDL.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <stdio.h> 
#include <iostream> 
#include <stdlib.h>
#include <math.h>
#include <SDL_syswm.h> 
#include <SDL_byteorder.h> 
 
//#include "createTexture.h"
#include "draw.h"


using namespace std;

/**************************************************/
/* Struct definition                              */
/**************************************************/

struct KeyFlag {
	bool right;
	bool left;
	bool up;
	bool down;
	bool pageUp;
	bool pageDown;
  int relMouseY;
  int relMouseX;
  int rollButton;
} ;

/**************************************************/
/* Variable definition                            */
/**************************************************/
extern KeyFlag keyFlag;
extern bool isAxisDrawn;
extern bool showShadow;
/**************************************************/
/* Function definition                            */
/**************************************************/

void quit_program( int code );						// Quit program

void process_events( );								// Process keyevents

bool init_OpenGL( );								// Init OpenGL

bool init_SDL();									// Init SDL Engine

int main( int argc, char* argv[] );					// Main

#endif



