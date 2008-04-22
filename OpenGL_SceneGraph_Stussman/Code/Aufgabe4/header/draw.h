/**************************************************/
/*                                                */
/*  Draw Header Aufgabe 2                         */
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

#ifndef _DRAW_H
#define _DRAW_H

/**************************************************/
/* Variable definition                            */
/**************************************************/
#include <math.h>
#include "main.h"
//#include "shadow.h"
#include "nodes.h"
#include "visitors.h"
#include "builder.h"


extern float fps;									// Frames per second
extern GroupNode* sceneRoot;
/**************************************************/
/* Function definition                            */
/**************************************************/

void draw3D( );

void draw_screen( );

void countFrames( );

void camera( );

void incAnimationVars( );

void drawShip( );

void drawGrid( );

void initScene();
void quitScene();
void drawSun();
void drawEarth();
void drawMoon();
void drawAxis(float len=1);


#endif

