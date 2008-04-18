/**************************************************/
/*                                                */
/*  Main Sorucecode Aufgabe 1                     */
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

int	width = 1024;									// Dimensions of our window
int height = 768;

bool fullscreen = false;							// Fullscreen or windowed mode

/**************************************************/
/* Exit                                           */
/**************************************************/

void quit_program( int code )
{
    SDL_Quit( );									// Quit SDL and restore previous video stettings
    exit( code );									// Exit program
}

/**************************************************/
/* Poll keyevents                                 */
/**************************************************/

void process_events( )
{
  SDL_Event event;								// SDL event placeholder

  while( SDL_PollEvent( &event ) ) {				// Grab all the events off the queue

    switch( event.type ) {

      case SDL_QUIT:								// Handle quit requests (like Ctrl-c)
        quit_program( 0 );
        break;

      case SDL_VIDEORESIZE:
        width = event.resize.w;
        height = event.resize.h;
        glViewport(0, 0, width, height);
        break;

      case SDL_KEYDOWN:
        {							// Handle each Keydown
          switch( event.key.keysym.sym ) {		// Switch keyvalue

            case SDLK_ESCAPE:
              quit_program( 0 );					// Quit program
              break;

            case SDLK_F1:
              quit_program( 0 );					// Quit program
              break;

            case SDLK_F2:
              fullscreen = (true==fullscreen) ? false : true;
              init_SDL();
              init_OpenGL();
              glViewport(0, 0, width, height);
              break;

            default:
              break;
              }
        }

    default:
      break;
    }
  }
}

/**************************************************/
/* Init OpenGL                                    */
/* Returnvalue: true if init was successful       */
/**************************************************/

bool init_OpenGL( )
{	
  float ratio = (float) width / (float) height;	// Calculate and store the aspect ratio of the display
  glMatrixMode( GL_PROJECTION );					// Change to the projection matrix
  gluPerspective( 60.0, ratio, 0.1, 1024.0 );		// Set view perspective
  glMatrixMode( GL_MODELVIEW );					// Change to the modelview matrix
	glEnable(GL_DEPTH_TEST);						// Enable hidden surface elimination
	return true;
}

/**************************************************/
/* Init SDL                                       */
/* Returnvalue: true if init was successful       */
/**************************************************/

bool init_SDL()
{
    const SDL_VideoInfo* info = NULL;				// Information about the current video settings
	
    int bpp = 0;									// Color depth in bits of our window
    int flags = 0;									// Flags we will pass into SDL_SetVideoMode
	
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )			// First, initialize SDL's video subsystem (video only)
	{
        fprintf( stderr, "Video initialization failed: %s\n",
			SDL_GetError( ) );
        quit_program( 1 );							// Failed, exit
    }
	
    info = SDL_GetVideoInfo( );						// Get some video information
	
    if( !info )										// This should probably never happen
	{
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        return false;
    }
	
    bpp = info->vfmt->BitsPerPixel;					// Get color depth
	
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );		// Sets the color-depth of the red, green and blue color-part
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );	// to 8bit (standard today) 
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );	// Set depth buffer
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );	// Sets wether to enable or disable doublebuffering
	
    flags = SDL_OPENGL | SDL_RESIZABLE;								// Set flags for SDL OpenGL
    
	if (fullscreen){
		flags = flags | SDL_FULLSCREEN;				// Set flag for fullscreen or windowed mode
	}
    
    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 )	// Set the video mode
	{															// If failed, print error message
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError( ) );
        return false;
    }
	
	return true;
}

/**************************************************/
/* Main                                           */
/* Returnvalue: 0 if main was successful          */
/**************************************************/

int main( int argc, char* argv[] )
{
	if(!init_SDL( ))				// If intialising of SDL fails -> quit the program with error code 1
	{
		quit_program( 1 );
	}
	
	if(!init_OpenGL())				// If intialising of OpenGL fails -> quit the program with error code 1
	{
		quit_program( 1 );
	}
	
	while(true)						// Repeat forever
	{
		draw_screen();				// Draw your graphics
		process_events( );			// Process any ocuring events 
	}
	
	quit_program(0);				// You shouldn't get here. Only if someone changes the while condition...
}
