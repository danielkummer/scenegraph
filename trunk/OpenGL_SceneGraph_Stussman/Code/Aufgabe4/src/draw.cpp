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

GLUquadricObj* quadric = gluNewQuadric();
//GroupNode* sceneRoot;
SolarSytemScene* scene;
Clock* clk;
// TODO: remove testcode
SwitchNode* vToggle;
long counter = 0;

/**************************************************/
/* Draw 3D Objects                                */
/**************************************************/

void draw3D() {
	glLoadIdentity();								// Load a new matrix

	camera();										// Calculate and set cameraview and cameraposition
	
  float light_pos[] =    {0.0f, 10.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	incAnimationVars();											

  gluQuadricNormals(quadric, GL_SMOOTH);

  clk->tick();
  scene->update();

	drawShip();										// Draw ship

	// TODO: 2.2, 2.3, 2.5
	// ////////////////////


	
	// Draw grid
	////////////////////
	glPushMatrix();									// Save matrix
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
    speed += 10.0f;
    printf("speed: %f\n", speed);
  }
  if(5 == keyFlag.rollButton){
    speed -= 10.0f;
    printf("speed: %f\n", speed);
  }
  keyFlag.rollButton = -1;
  keyFlag.relMouseX = 0;
  keyFlag.relMouseY = 0;

  Clock::getDefaultClock()->setDilatation(speed);
  float dx = 0;
  float dy = 0;
  float dz = 0;

  if(keyFlag.left){
    dx = 0.1f;
  }
  if(keyFlag.right){
    dx = -0.1f;
  }
  if(keyFlag.up){
    dz = 0.1f;
  }
  if(keyFlag.down){
    dz = -0.1f;
  }
  if(keyFlag.pageUp){
    dy = 0.1f;
  }
  if(keyFlag.pageDown){
    dy = -0.1f;
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
	angle = angle + speed * 60.0f/fps ;						// deltaAngle = 60/fps; 60 degrees per second
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
	  unsigned char red[]    = { 255,   0,   0, 255 };		// Colors
    unsigned char blue[] = {0, 255, 0, 255};
    unsigned char green[] = {0, 0, 255, 255};
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

    drawAxis();
  glPopMatrix();
}

/**************************************************/
/* Draw Grid                                      */
/**************************************************/

void drawGrid()
{
  glPushMatrix();
  	glTranslatef( 0.0f, -3.0f, 0.0f);				// Translate grid in the y-axis
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
  glPopMatrix();

  drawAxis(10);
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
/*
  sceneRoot = new GroupNode();

  sceneRoot->ref();

  Director vDirector = Director();
  sceneRoot->add(vDirector.createSolarSystem() );
  

  PrintVisitor().apply(sceneRoot);
*/

}

void quitScene(){

//  DestructorVisitor vDVisitor = DestructorVisitor();
//  vDVisitor.apply(sceneRoot);
//  sceneRoot->unref();
  delete clk;
  delete scene;

}
//------------------
void drawSun(){
  glPushMatrix();
//  glPolygonMode(GL_FRONT, GL_LINE);
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//  gluQuadricNormals(quadric, GL_NONE);
  glRotatef(-90, 0, 1, 0);
  glColor3f(1.0f, 1.0f, 0.0f);

//  glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);    
  GLfloat sun_emission[] = { 1.0, 1.0, 0.0, 1.0 };
  glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, sun_emission );

  float radius = 5;
    if(showShadow){
      float modelMatrix[16];
      glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);
//      drawShadow( modelMatrix, radius);
    }


    gluSphere(quadric, radius, 20, 10);
//  glDisable(GL_COLOR_MATERIAL);
  GLfloat default_emission[] = { 0.0, 0.0, 0.0, 1 };
  glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, default_emission );

  drawAxis();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glPopMatrix();
}


void drawEarth(){
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//  gluQuadricNormals(quadric, GL_SMOOTH);
      float radius = 1.0f;

  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glRotatef(-angle, 0, 1, 0); // Rotation um Sonne
    glTranslatef(10, 0, 0); // Radius zur Sonne

    if(showShadow){
      float modelMatrix[16];
      glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);
//      drawShadow( modelMatrix, radius);
    }

    drawMoon();

    glRotatef(angle, 0, 1, 0); // gegen Rotation um die Achse fix im Raum zu lassen
    glRotatef(90-23, 1, 0, 0); // shiefe der Erdachse
    glRotatef(-angle*365.25f, 0, 0, 1); // Eigendrehung
//    glEnable(GL_COLOR_MATERIAL);
      glColor3f(0,0,1);
      gluSphere(quadric, radius, 20, 10);
//    glDisable(GL_COLOR_MATERIAL);
    drawAxis(5.0f);
  glPopMatrix();
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawMoon(){
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//  gluQuadricNormals(quadric, GL_SMOOTH);

  glColor3f(0.8f, 0.8f, 0.8f);
  glPushMatrix();
//    glRotatef(-angle, 0, 1, 0); // Rotation um Sonne
//    glTranslatef(10, 0, 0); // Radius zur Sonne

    glRotatef(angle*365.25f/4, 0, 1, 0); // Drehung um Erde
    glTranslatef(2, 0 , 0);

    float radius = 0.6f;
    if(showShadow){
      float modelMatrix[16];
      glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);
//      drawShadow( modelMatrix, radius);
    }


    glRotatef(90, 1, 0, 0);
//    glRotatef(-angle*365.25f/8, 0, 0, 1); // Eigendrehung

    gluSphere(quadric, radius, 20, 10);
    drawAxis();
  glPopMatrix();
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawAxis(float len){
  if(isAxisDrawn){
      glLineWidth(3);
      glBegin(GL_LINES);
          glColor3f(1, 0, 0);
          glVertex3f(0, 0, 0);
          glVertex3f(len, 0, 0);

          glColor3f(1, 1, 0);
          glVertex3f(0, 0, 0);
          glVertex3f(0, len, 0);

          glColor3f(0, 0, 1);
          glVertex3f(0, 0, 0);
          glVertex3f(0, 0, len);
      glEnd();
      glLineWidth(1);
  }
}

