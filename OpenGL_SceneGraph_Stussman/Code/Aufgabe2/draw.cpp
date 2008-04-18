/**************************************************/
/*                                                */
/*  Draw Sourcecode Aufgabe 2                     */
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
/* Variable definition                            */
/**************************************************/
float fps;											// Frames per second
float angle;										// Rotation angle of ship
float dist;											// Ship translation

float xangle;
float yangle;
float zangle;
float posx;
float posy;
float posz = -10;
float mousetune = 0.1f;

/**************************************************/
/* Draw 3D Objects                                */
/**************************************************/

void draw3D() {
	glLoadIdentity();								// Load a new matrix

	camera();										// Calculate and set cameraview and cameraposition
	
	incAnimationVars();											

	// Draw Ship
	/////////////////////	
	drawShip();										// Draw ship

	// TODO: 2.2, 2.3, 2.5
	// ////////////////////


	
	// Draw grid
	////////////////////
	glPushMatrix();									// Save matrix
	glTranslatef( 0.0f, -3.0f, 0.0f);				// Translate grid in the y-axis
	drawGrid();										// Draw a grid on the ground
	glPopMatrix();									// Restore matrix
}

/**************************************************/
/* Calculate and set camera                       */
/**************************************************/

void camera() {
	// TODO 2.4 to 2.6
	////////////////////////////////////////////////
  yangle += (keyFlag.relMouseX * mousetune);
  xangle += (keyFlag.relMouseY * mousetune);
  if(4 == keyFlag.rollButton){
    zangle += 1;
  }
  if(5 == keyFlag.rollButton){
    zangle -= 1;
  }
  keyFlag.rollButton = -1;
  keyFlag.relMouseX = 0;
  keyFlag.relMouseY = 0;

  
  float dx = 0;
  float dy = 0;
  float dz = 0;

  if(keyFlag.left){
    dx = 1;
  }
  if(keyFlag.right){
    dx = -1;
  }
  if(keyFlag.up){
    dz = 1;
  }
  if(keyFlag.down){
    dz = -1;
  }
  if(keyFlag.pageUp){
    dy = 1;
  }
  if(keyFlag.pageDown){
    dy = -1;
  }
  /*
  // shooter
  posx += dx * cos(yangle*vToRad) - dz * sin(yangle*vToRad);
  posy += dy * cos(xangle*vToRad);
  posz += dx * sin(yangle*vToRad) + dz * cos(yangle*vToRad);
*/
/*
    float x = (float)( dx*cos(yRot) + dy*sin(xRot)*sin(yRot) - dz*cos(xRot)*sin(yRot) );
    float y = (float)(              + dy*cos(xRot)           + dz*sin(xRot)           );
    float z = (float)( dx*sin(yRot) - dy*sin(xRot)*cos(yRot) + dz*cos(xRot)*cos(yRot) );
*/
  float vToRad = 3.14f/180;
  posx += dx * cos(yangle*vToRad) + dy * sin(xangle*vToRad) * sin(yangle*vToRad) - dz * cos(xangle*vToRad) * sin(yangle*vToRad);
  posy +=                           dy * cos(xangle*vToRad)                      + dz * sin(xangle*vToRad);
  posz += dx * sin(yangle*vToRad) - dy * sin(xangle*vToRad) * cos(yangle*vToRad) + dz * cos(xangle*vToRad) * cos(yangle*vToRad);

  glRotatef(zangle, 0, 0, 1);
  glRotatef(xangle, 1, 0, 0);
  glRotatef(yangle, 0, 1, 0);
  glTranslatef(posx, posy, posz);
}

/**************************************************/
/* Increment Animation Variables                  */
/**************************************************/

void incAnimationVars() {
	angle = angle + 60.0f/fps ;						// deltaAngle = 60/fps; 60 degrees per second
	dist = dist + 20.0f/fps;						// 20 units per second

	if (angle >= 360){angle = 0;}					// reset angle, 360 degrees = 0 degrees
	if (dist > 100){dist = -50;}					// reset distance to set a loop
}

/**************************************************/
/* Draw The Ship                                  */
/**************************************************/

void drawShip() {
	// TODO 2.1
	////////////////////////////////////////////////
  glPushMatrix();
  glTranslatef(dist, 0.0, 0.0);
  glRotatef(180, 0, 1, 0);
  glRotatef(3*angle, 1, 0, 0);


	float v0[] = {  0.0f,  0.0f,  0.0f };		// Vertices
	float v1[] = {  4.0f,  -1.0f,  0.0f };		// Vertices
	float v2[] = {  4.0f,  0.0f,  -1.0f };		// Vertices
	float v3[] = {  4.0f,  1.0f,  0.0f };		// Vertices
	// ...
	byte red[]    = { 255,   0,   0, 255 };		// Colors
  byte blue[] = {0, 255, 0, 255};
  byte green[] = {0, 0, 255, 255};
	// ...

	glBegin( GL_TRIANGLES );		// Tell OpenGL to draw triangles using the following vertexes

		glColor4ubv( red );			// Change color to red
		glVertex3fv( v0 );			// Set point 0
		glVertex3fv( v1 );			// Set point 0
		glVertex3fv( v2 );			// Set point 0

		glColor4ubv( blue );			// Change color to red
		glVertex3fv( v0 );			// Set point 0
		glVertex3fv( v2 );			// Set point 0
		glVertex3fv( v3 );			// Set point 0

		glColor4ubv( green );			// Change color to red
		glVertex3fv( v0 );			// Set point 0
		glVertex3fv( v1 );			// Set point 0
		glVertex3fv( v3 );			// Set point 0

		glVertex3fv( v1 );			// Set point 0
		glVertex3fv( v3 );			// Set point 0
		glVertex3fv( v2 );			// Set point 0


	glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);

        glColor3f(1, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);

    glEnd();

  glPopMatrix();
}

/**************************************************/
/* Draw Grid                                      */
/**************************************************/

void drawGrid()
{

    for(float i = -50; i <= 50; i += 1)	{			// Draw a 1x1 grid along the X and Z axis
        glLineWidth(1);
        glBegin(GL_LINES);							// Start drawing some lines	
            glColor3ub(0, 255, 0);							// Turn the lines green
            glVertex3f(-50, 0, i);					// Do the horizontal lines (along the X)
            glVertex3f(50, 0, i);

            glVertex3f(i, 0, -50);					// Do the vertical lines (along the Z)
            glVertex3f(i, 0, 50);

        glEnd();
    }
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(10, 0, 0);

        glColor3f(1, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 10, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 10);

    glEnd();
}

/**************************************************/
/* Draw Screen                                    */
/**************************************************/

void draw_screen( ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear the screen and the depth buffer
	
	draw3D();
	countFrames();
	
	SDL_GL_SwapBuffers( );											// Swap the buffers
}

/**************************************************/
/* Count Frames                                   */
/**************************************************/

void countFrames() {
	static double thisFrame, lastFrame;								// Define placeholders for frametimes
	static int count = 0;											// Define placeholder to count frames
	
	thisFrame = SDL_GetTicks();										// Get time
    count++;														// Count frames
	
    if((thisFrame-lastFrame) > 0){									// Check if 10 millis are over
		
		fps = 1000.0f*(float)count/(float)(thisFrame-lastFrame);	// Calculate frames per second
		
		lastFrame=thisFrame;										// Set frametime value
		count = 0;													// Reset count value
	}
}
