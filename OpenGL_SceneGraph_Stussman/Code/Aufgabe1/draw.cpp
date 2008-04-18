/**************************************************/
/*                                                */
/*  Draw Sourcecode Aufgabe 1                     */
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

#include "main.h"
#include "draw.h"

/**************************************************/
/* Draw 3D Objects                                */
/**************************************************/

void draw3D( )
{		
	GLUquadricObj	*q;									// Variable for a quadric object
	
	// Sphere 1
	glLoadIdentity( );									// Load a new matrix
	q = gluNewQuadric();								// Create a new quadric
	glTranslatef(1.0f, -1.0f, -3.0f);					// Translate the matrix to x=1, y=-1, z=-3
	glColor3f(1.0f, 1.0f, 1.0f);						// Set color to white
	gluSphere(q, 0.5, 32, 16);							// Draw the first sphere
	
	// TO DO Aufgabe 1.2
	////////////////////////////////////////////////////
  glTranslatef(1.0f, 0.0f, 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  gluSphere(q, 0.3, 32, 16);




}

/**************************************************/
/* Draw Screen                                    */
/**************************************************/

void draw_screen( )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear the screen and the depth buffer
	
	draw3D();											// Draw 3D stuff
	
	SDL_GL_SwapBuffers( );								// Swap the front buffer with the back buffer
														// (showing the generated image)
}

