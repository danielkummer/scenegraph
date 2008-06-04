#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_






#include "main.h"

#include <stdio.h> 
#include <iostream> 
#include <stdlib.h>
#include <vector>
#include <string>

typedef std::map<const std::string, unsigned> TTexCache;

class TextureManager {
	public:
		static TextureManager* getReference();
    static void deleteRef();
		~TextureManager();	
		unsigned int createTexture(char *strFileName);
		unsigned int getId();
	private:				
		TextureManager();
//		unsigned int *textures;		//Global Texture Array
		unsigned int currTexIndex;
		static TextureManager *texMan;
    TTexCache mTexCache;
};

#endif /*TEXTUREMANAGER_H_*/
