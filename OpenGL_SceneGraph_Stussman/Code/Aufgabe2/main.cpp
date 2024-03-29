/**************************************************/
/*                                                */
/*  Main Sourcecode Aufgabe 2                     */
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

#include "main.h"
#include "draw.h"

/**************************************************/
/* Variable definition                            */
/**************************************************/

KeyFlag keyFlag;									// Placeholder for pressed keys
int width = 1024;									// Dimensions of our window
int height = 768;

bool fullscreen = false;								// Fullscreen or windowed mode

/**************************************************/
/* Exit                                           */
/**************************************************/

void quit_program( int code )
{
    SDL_Quit( );									// Quit SDL and restore previous video settings
    exit( code );									// Exit program
}

/**************************************************/
/* Poll Keyevents                                 */
/**************************************************/

void process_events( )
{
    SDL_Event event;								// SDL event placeholder
	
	// Used for camera control
	//////////////////////////	
    while( SDL_PollEvent( &event ) ) 				// Grab all the events off the queue
	{
        switch( event.type ) 
		{
    case SDL_QUIT:								// Handle quit requests (like Ctrl-c)
            quit_program( 0 );
            break;
    case SDL_MOUSEMOTION:
      keyFlag.relMouseX = event.motion.xrel;
      keyFlag.relMouseY = event.motion.yrel;
      break;
    case SDL_MOUSEBUTTONDOWN:
      switch( event.button.button ){
        case 4:
        case 5:
          keyFlag.rollButton = event.button.button;
          break;
      }
    case SDL_MOUSEBUTTONUP:
      switch( event.button.button ){
        case 4:
        case 5:
//          keyFlag.rollButton = -1;
          break;
      }
		case SDL_KEYDOWN:							// Handle each keydown
			
			switch( event.key.keysym.sym ) {
			case SDLK_ESCAPE:
				quit_program( 0 );					// Quit program
				break;
				
			case SDLK_RIGHT:
				keyFlag.right = true;				// Set keyflags
				break;
				
			case SDLK_LEFT:
				keyFlag.left = true;
				break;
				
			case SDLK_UP:
				keyFlag.up = true;
				break;
				
			case SDLK_DOWN:
				keyFlag.down = true;
				break;
				
			case SDLK_PAGEUP:
				keyFlag.pageUp = true;
				break;
				
			case SDLK_PAGEDOWN:
				keyFlag.pageDown = true;
				break;
				
			default:
				break;
			}
			
			break;
			
		case SDL_KEYUP:								// Handle each keyup
			switch( event.key.keysym.sym ) 
			{
			case SDLK_RIGHT:
				keyFlag.right = false;				// Set keyflags
				break;
				
			case SDLK_LEFT:
				keyFlag.left = false;
				break;
				
			case SDLK_UP:
				keyFlag.up = false;
				break;
				
			case SDLK_DOWN:
				keyFlag.down = false;
				break;
				
			case SDLK_PAGEUP:
				keyFlag.pageUp = false;
				break;
				
			case SDLK_PAGEDOWN:
				keyFlag.pageDown = false;
				break;
	
			case SDL_VIDEORESIZE:						// Handle resize events
				width = event.resize.w;					// Set event width value
				height = event.resize.h;				// Set event height vlaue
				SDL_Quit();								// Quit SDL
				init_SDL();								// Restart SDL
				init_OpenGL();							// Restart OpenGL
				break;
				
			default:
				break;
			}
			break;
        }
    }
}

/**************************************************/
/* Init OpenGL                                    */
/* Returnvalue: true if init was successful       */
/**************************************************/

bool init_OpenGL( ) {	
	
    float ratio = (float) width / (float) height;	// Calculate and store the aspect ratio of the display
	
   	glMatrixMode( GL_PROJECTION );					// Change to the projection matrix
	
    gluPerspective( 60.0, ratio, 0.1, 1024.0 );		// Set view perspective
	
    glMatrixMode( GL_MODELVIEW );					// Change to the modelview matrix
	
	glEnable(GL_DEPTH_TEST);						// Enable hidden surface removal
	
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
	
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 			// First, initialize SDL's video subsystem (video only)
	{
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        quit_program( 1 );							// Failed, exit
    }
	
    info = SDL_GetVideoInfo( );						// Get some video information
	
    if( !info ) 									// This should probably never happen
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
	
	flags = SDL_OPENGL;								// Set flags for SDL OpenGL
	flags = flags | SDL_RESIZABLE;
    
	if (fullscreen) {
		flags = flags | SDL_FULLSCREEN;				// Set flag for fullscreen or windowed mode
	}
    
    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) 	// Set the video mode
	{
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError( ) );
        return false;
    }
	
    SDL_ShowCursor(false);
    SDL_WM_GrabInput(SDL_GRAB_ON);
	return true;
}

/**************************************************/
/* Main                                           */
/* Returnvalue: 0 if main was successful          */
/**************************************************/

int main( int argc, char* argv[] )
{
	if(!init_SDL())					// If intialising of SDL fails -> quit the program with error code 1
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
