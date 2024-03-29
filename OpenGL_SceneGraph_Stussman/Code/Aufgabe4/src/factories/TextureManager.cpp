#include "factories/TextureManager.h"

TextureManager* TextureManager::texMan = NULL;

TextureManager *TextureManager::getReference() {
	if(texMan == NULL) {
		texMan = new TextureManager();	
	}
	return texMan;
}

void TextureManager::deleteRef(){
  delete texMan;
  texMan = NULL;
}

TextureManager::TextureManager() {
//	textures = new unsigned int[100];			//init texture array
	currTexIndex = 0;
}
TextureManager::~TextureManager() {
//	glDeleteTextures(currTexIndex, textures);
//	delete[] textures;	
  TTexCache::iterator vItr;
  for(vItr=mTexCache.begin(); vItr!=mTexCache.end(); vItr++){
    glDeleteTextures(1, &(vItr->second));
  }
}	

unsigned int TextureManager::getId(){
	return currTexIndex;	
}

unsigned int TextureManager::createTexture(char *strFileName) {
  TTexCache::iterator vItr = mTexCache.find(std::string(strFileName));
  if(vItr != mTexCache.end()){
    return vItr->second;
  }
  


  SDL_Surface *bitmap;													// SDL_Surface to load the image into
  SDL_Surface *conv;														// SDL_Surface to copy the image into (with correct color order)
															
  int pitch;																// Variable to store the length of one pixel-line
  int height_div_2;														// Variable to store the size of half the number of rows

  void* temp_row;															// Variable to store the pointer to a pixel-line
	
  //set current textureID and increment currTexId for next use
  currTexIndex++;

  bitmap = SDL_LoadBMP(strFileName);										// Load image into an SDL_Surface
	
  if (!bitmap)															// If loading failed
  {																		//
     printf("Could not load texture %s.\n",strFileName);					// print an error message
     quit_program( 0 );													// and quit
  }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN											// Select wether we use RGB or BGR mode 
  conv = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 32,0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff); // Create an SDL-Surface (big endian)
#else
  conv = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 32,0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000); // Create an SDL-Surface (little endian)
#endif

  SDL_BlitSurface(bitmap, 0, conv, 0);									// Copy the loaded image to the surface with the correct color order

  // Flip Loaded Bitmap upside down
  // (SDL and OpenGL use diffrent Coordinate Systems)
  ////////////////////////////////////////////////////////
  pitch = conv->pitch;													// length of one pixel-line

  temp_row = (void *)malloc(pitch);										// Allocate memory for the inversion
  if(NULL == temp_row)													// If you're not able to allocate the memory
  {																		//
	  SDL_SetError("Not enough memory for image inversion");				// display an error message
  }
  height_div_2 = (int) (conv->h * .5);									// use only one half of the rows. (Works also with a odd number of rows)
  for(int index = 0; index < height_div_2; index++)							// for every line in the lower half swap it with the corresponding line
  {																		// in the upper half
	  memcpy(
		  (Uint8 *)temp_row,												// 
		  (Uint8 *)(conv->pixels) + pitch * index,						// copy one line from the first half to the temp variable
		  pitch);															// size of one line
	  memcpy(
		  (Uint8 *)(conv->pixels) + pitch * index,						//
		  (Uint8 *)(conv->pixels) + pitch * (conv->h - index-1),			// copy the corresponding line from the upper half to the line in the lower half
		  pitch);															// size of one line
	  memcpy(
		  (Uint8 *)(conv->pixels) + pitch * (conv->h - index-1),			//
		  temp_row,														// copy the tempvariable back to the corresponding line in the upper half
		  pitch);															// size of one line
  }
  free(temp_row);															// free allocated memory now that we don't need it anymore

  // End flipping
  /////////////////////////////////////////////////////////
  GLuint textureID;
  glGenTextures(1, &textureID);									// Generate a new texture ID
  glBindTexture(GL_TEXTURE_2D, textureID);						// Bind the texture (the following commands work with this texture)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// Set the filter mode for magnification to linear
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// Set the filter mode for minification to linear
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// Set the wrapping mode for the texturecoourdinate s to repeat
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			// Set the wrapping mode for the texturecoourdinate t to repeat
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, conv->w, conv->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, conv->pixels);	//copy the image into the texture
  SDL_FreeSurface(bitmap);
  SDL_FreeSurface(conv);
	
  mTexCache.insert(std::pair<const std::string, unsigned>(std::string(strFileName), textureID));

  return textureID;
}
