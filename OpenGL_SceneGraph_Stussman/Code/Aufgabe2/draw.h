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

extern float fps;									// Frames per second
//extern KeyFlag keyFlag;

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

#endif
