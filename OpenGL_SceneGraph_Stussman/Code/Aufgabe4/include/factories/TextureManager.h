#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <stdio.h> 
#include <iostream> 
#include <stdlib.h>
#include <vector>

class TextureManager {
	public:
		static TextureManager* getReference();
		~TextureManager();	
		unsigned int createTexture(char *strFileName);
		unsigned int getId();
	private:				
		TextureManager();
		unsigned int *textures;		//Global Texture Array
		unsigned int currTexIndex;
		static TextureManager *texMan;
};

#endif /*TEXTUREMANAGER_H_*/
