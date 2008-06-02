/**************************************************/
/*                                                */
/*  Draw Sourcecode Aufgabe 2                     */
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

#include "draw.h"
#include "scene.h"

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
float speed = 300.0f;

SolarSytemScene* scene;
Clock* clk;

/**************************************************/
/* Draw 3D Objects                                */
/**************************************************/

void draw3D() {
	glLoadIdentity();								// Load a new matrix

//	camera();										// Calculate and set cameraview and cameraposition
	
  clk->tick();
  scene->update();

	drawGrid();										// Draw a grid on the ground
}

/**************************************************/
/* Calculate and set camera                       */
/**************************************************/

//void camera() {
//	// TODO 2.4 to 2.6
//	////////////////////////////////////////////////
//  yangle += (keyFlag.relMouseX * mousetune);
//  xangle += (keyFlag.relMouseY * mousetune);
//  if(4 == keyFlag.rollButton){
//    speed += 10.0f;
//    printf("speed: %f\n", speed);
//  }
//  if(5 == keyFlag.rollButton){
//    speed -= 10.0f;
//    printf("speed: %f\n", speed);
//  }
//  keyFlag.rollButton = -1;
//  keyFlag.relMouseX = 0;
//  keyFlag.relMouseY = 0;
//
//  Clock::getDefaultClock()->setDilatation(speed);
//  float dx = 0;
//  float dy = 0;
//  float dz = 0;
//
//  if(keyFlag.left){
//    dx = 1.1f;
//  }
//  if(keyFlag.right){
//    dx = -1.1f;
//  }
//  if(keyFlag.up){
//    dz = 1.1f;
//  }
//  if(keyFlag.down){
//    dz = -1.1f;
//  }
//  if(keyFlag.pageUp){
//    dy = 1.1f;
//  }
//  if(keyFlag.pageDown){
//    dy = -1.1f;
//  }
//  /*
//  // shooter
//  posx += dx * cos(yangle*vToRad) - dz * sin(yangle*vToRad);
//  posy += dy * cos(xangle*vToRad);
//  posz += dx * sin(yangle*vToRad) + dz * cos(yangle*vToRad);
//*/
///*
//    float x = (float)( dx*cos(yRot) + dy*sin(xRot)*sin(yRot) - dz*cos(xRot)*sin(yRot) );
//    float y = (float)(              + dy*cos(xRot)           + dz*sin(xRot)           );
//    float z = (float)( dx*sin(yRot) - dy*sin(xRot)*cos(yRot) + dz*cos(xRot)*cos(yRot) );
//*/
//  float vToRad = 3.14f/180;
//  posx += dx * cos(yangle*vToRad) + dy * sin(xangle*vToRad) * sin(yangle*vToRad) - dz * cos(xangle*vToRad) * sin(yangle*vToRad);
//  posy +=                           dy * cos(xangle*vToRad)                      + dz * sin(xangle*vToRad);
//  posz += dx * sin(yangle*vToRad) - dy * sin(xangle*vToRad) * cos(yangle*vToRad) + dz * cos(xangle*vToRad) * cos(yangle*vToRad);
//
//  glRotatef(zangle, 0, 0, 1);
//  glRotatef(xangle, 1, 0, 0);
//  glRotatef(yangle, 0, 1, 0);
//  glTranslatef(posx, posy, posz);
//}

/**************************************************/
/* Increment Animation Variables                  */
/**************************************************/

//void incAnimationVars() {
//	angle = angle + speed * 60.0f/fps ;						// deltaAngle = 60/fps; 60 degrees per second
//	dist = dist + 20.0f/fps;						// 20 units per second
//
//	if (angle >= 360){angle = 0;}					// reset angle, 360 degrees = 0 degrees
//	if (dist > 100){dist = -50;}					// reset distance to set a loop
//}

/**************************************************/
/* Draw The Ship                                  */
/**************************************************/



/**************************************************/
/* Draw Grid                                      */
/**************************************************/

void drawGrid()
{
  glPushMatrix();
  	glTranslatef( 0.0f, -3.0f, 0.0f);				// Translate grid in the y-axis
  	glEnable(GL_COLOR_MATERIAL);
    glColor3f(0, 255, 0);							// Turn the lines green
    for(float i = -50; i <= 50; i += 1)	{			// Draw a 1x1 grid along the X and Z axis
        glLineWidth(1);        
        glBegin(GL_LINES);							// Start drawing some lines	
            glColor3f(0, 255, 0);							// Turn the lines green
            glVertex3f(-50, 0, i);					// Do the horizontal lines (along the X)
            glVertex3f(50, 0, i);
            glVertex3f(i, 0, -50);					// Do the vertical lines (along the Z)
            glVertex3f(i, 0, 50);
        glEnd();        
    }
    glDisable(GL_COLOR_MATERIAL);
  glPopMatrix();

  int vErr = glGetError();
  if(0!=vErr){
    printf("GL_ERROR@drawGrid(): %i\n", vErr);
  }

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
//------------------
bool handleEvent(SDL_Event &aEvent){
  return scene->handleEvent(aEvent);
}
//------------------
void initScene(){

  clk = Clock::getDefaultClock();
  scene = new SolarSytemScene();
  scene->init();
  scene->createScene();
}
//------------------
void quitScene(){

  delete clk;
  delete scene;

}
//------------------

