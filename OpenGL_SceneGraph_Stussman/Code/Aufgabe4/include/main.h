/**************************************************/
/*                                                */
/*  Main Header Aufgabe 2                         */
/*                                                */
/**************************************************/
/*  Authors:                Reto Bollinger        */
/*                          bolliret@zhwin.ch     */
/*                                                */
/*                          Hanspeter Br�hlmann   */
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


struct vertex3D										// Struct for a 3D vertex
{
	float x;
	float y;
	float z;
};

struct vertex2D										// Struct for a 2D vertex (texture coordinates)
{
	float x;
	float y;
};

struct triang										// Struct for all values for a triangle
{
	vertex3D vertex1;
	vertex3D vertex2;
	vertex3D vertex3;

	vertex3D normal1;
	vertex3D normal2;
	vertex3D normal3;

	vertex2D tCoord1;
	vertex2D tCoord2;
	vertex2D tCoord3;

};

struct mat											// Material definitions
{
	float matAmbient[4];
	float matDiffuse[4];
	float matSpecular[4];
	float matShininess;
};

struct group										// Definition for an object group
{
	triang* triangle;									// Pointer to an array of triangles
	mat material;
	char* textureName;
	int textureID;
	int size;
};

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



