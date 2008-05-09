/**************************************************/
/*                                                */
/*  Draw Header Aufgabe 2                         */
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

#ifndef _DRAW_H
#define _DRAW_H

/**************************************************/
/* Variable definition                            */
/**************************************************/
#include <math.h>
#include "main.h"
//#include "shadow.h"
//#include "nodes/nodes.h"
//#include "visitors/visitors.h"
#include "nodes/groupnode.h"
#include "factories/builder.h"


extern float fps;									// Frames per second
extern GroupNode* sceneRoot;
/**************************************************/
/* Function definition                            */
/**************************************************/

void draw3D( );

void draw_screen( );

void countFrames( );

void camera( );

//void incAnimationVars( );

void drawGrid( );

void initScene();
void quitScene();
bool handleEvent(SDL_Event &aEvent);



#endif

