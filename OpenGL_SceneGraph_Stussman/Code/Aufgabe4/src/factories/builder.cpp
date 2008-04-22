#include "factories/builder.h"
//#include "createTexture.h"



/**************************************************/
/* Create texture                                 */
/**************************************************/

int createTexture(char *strFileName)
{
	SDL_Surface *bitmap;													// SDL_Surface to load the image into
	SDL_Surface *conv;														// SDL_Surface to copy the image into (with correct color order)
															
	int pitch;																// Variable to store the length of one pixel-line
	int height_div_2;														// Variable to store the size of half the number of rows

	void* temp_row;															// Variable to store the pointer to a pixel-line

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
  unsigned int texId;
	glGenTextures(1, &texId);									// Generate a new texture ID
	glBindTexture(GL_TEXTURE_2D, texId);						// Bind the texture (the following commands work with this texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// Set the filter mode for magnification to linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// Set the filter mode for minification to linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// Set the wrapping mode for the texturecoourdinate s to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			// Set the wrapping mode for the texturecoourdinate t to repeat
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, conv->w, conv->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, conv->pixels);	//copy the image into the texture
	SDL_FreeSurface(bitmap);
	SDL_FreeSurface(conv);
  return texId;
}

//-------------------------------------------------------//


Builder::Builder():mCurrent(NULL){ }
//-------------------------------------------------------//
Builder::~Builder(){
  if(NULL != mCurrent){
    mCurrent->unref();
  }
}
//-------------------------------------------------------//
AbstractNode* Builder::getResult(){
  AbstractNode* vNode = mCurrent;
  mCurrent = NULL;
  return vNode;
}
//-------------------------------------------------------//
void Builder::setRootNode(GroupNode* aNode){
  if(NULL == mCurrent){
    mCurrent = aNode;
  }else{
    printf("WARNING: trying to set a Node but another is under construction!");
  }
}
//-------------------------------------------------------//
void Builder::buildGroupNode(ActionBase* aAction){
  append(aAction, new GroupNode());
}
//-------------------------------------------------------//
void Builder::buildTransformSeparator(ActionBase* aAction){
  append(aAction, new TransformSeparator());
}
//-------------------------------------------------------//
void Builder::buildSphereNode(double aRadius, int aSlices, int aStacks, GLboolean aUseTexCoord, ActionBase* aAction){
  append(aAction, new SphereNode(aRadius, aSlices, aStacks, aUseTexCoord));
}
//-------------------------------------------------------//
void Builder::buildLineNode(float aVert1X,
                   float aVert1Y, 
                   float aVert1Z, 
                   float aVert2X, 
                   float aVert2Y, 
                   float aVert2Z, 
                   float aWidth,
                   ActionBase* aAction){
  append(aAction, new LineNode(aVert1X, aVert1Y, aVert1Z, aVert2X, aVert2Y, aVert2Z, aWidth));
}
//-------------------------------------------------------//
void Builder::buildTranslationNode(float aX, float aY, float aZ, ActionBase* aAction){
  append(aAction, new TranslationNode(aX, aY, aZ));
}
//-------------------------------------------------------//
void Builder::buildRotationNode(float aAngle, float aAxisX, float aAxisY, float aAxisZ, ActionBase* aAction){
  append(aAction, new RotationNode(aAngle, aAxisX, aAxisY, aAxisZ));
}
//-------------------------------------------------------//
void Builder::buildScaleNode(float aScaleX, float aScaleY, float aScaleZ, ActionBase* aAction){
  append(aAction, new ScaleNode(aScaleX, aScaleY, aScaleZ));
}
//-------------------------------------------------------//
void Builder::buildRotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, ActionBase* aAction){
  append(aAction, new RotorNode(aAngleVel, aAngle, aAxisX, aAxisY, aAxisZ));
}
//-------------------------------------------------------//
void Builder::buildLightNode(GLenum aLightNr, ActionBase* aAction){
  append(aAction, new LightNode(aLightNr));
}
//-------------------------------------------------------//
void Builder::buildMaterialNode(GLenum aFace, ActionBase* aAction){
  append(aAction, new MaterialNode(aFace));
}
//-------------------------------------------------------//
void Builder::buildColorNode(float aRed, float aGreen, float aBlue, ActionBase* aAction){
  append(aAction, new ColorNode(aRed, aGreen, aBlue));
}
//-------------------------------------------------------//
void Builder::buildTextureNode(GLint aTexID, GLenum aTarget, ActionBase* aAction){
  append(aAction, new TextureNode(aTexID, aTarget));
}
//-------------------------------------------------------//
void Builder::buildShadowNode(float* aLightPos, float* aNormal, float* aPointInPlane, float* aColor, ActionBase* aAction){
  append(aAction, new ShadowNode(aLightPos, aNormal, aPointInPlane, aColor)); 
}
//-------------------------------------------------------//
void Builder::append(ActionBase* aAction, AbstractNode* aNode){
  mCurrent->add(aNode);
  if(NULL != aAction){
    aAction->add(aNode);
  }
  mLastAdded = aNode;
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
AbstractNode* Director::createPlanet(PlanetDef* aPlanterDef, AbstractNode** aNodelist, unsigned aNodeCount){
  mBuilder.setRootNode(new TransformSeparator());

  mBuilder.buildRotationNode(aPlanterDef->orbitInclination, 1, 0, 0);
  mBuilder.buildRotorNode(aPlanterDef->orbitVelocity, 0, 0, 1, 0); // rot around sun
  mBuilder.buildTranslationNode(aPlanterDef->orbitRadius, 0, 0); // radius to sun
  for(unsigned i=0; i<aNodeCount; i++){
    mBuilder.append(NULL, aNodelist[i]);
  }
  float vPos[4] = {0.0f, 10.0f, 0.0f, 1.0f};
  float vNormal[4] = {0.0f, 1.0f, 0.0f, 1.0f};
  float vPoint[4] = {0.0f, -3.0f, 0.0f, 1.0f};
  float vColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  ShadowNode* vShadowN = new ShadowNode(vPos, vNormal, vPoint, vColor);
  vShadowN->setNodeToShadow(new SphereNode(aPlanterDef->radius));
  ToggleNode* vToggle = new ToggleNode();
  vToggle->on();
  vToggle->add(vShadowN);
  //TODO: shadow toggle action
  mBuilder.append(NULL, vToggle);
  if(aPlanterDef->mAntiRot){
    mBuilder.buildRotorNode(-aPlanterDef->orbitVelocity, 0, 0, 1, 0); // anti rotation
  }
  mBuilder.buildRotationNode(aPlanterDef->tilt, 1, 0, 0); // tilt
  mBuilder.buildRotorNode(aPlanterDef->rotVelocity, 0, 0, 1, 0);
  mBuilder.buildRotationNode(90, 1, 0, 0);
  //TODO: add textures, material, color here
  int vTexId = createTexture(aPlanterDef->textureName);
  mBuilder.buildTextureNode(vTexId);

  mBuilder.buildSphereNode(aPlanterDef->radius, 16, 16, true);

  ToggleNode* vToggleN = new ToggleNode();
  vToggleN->add(createAxis(2*aPlanterDef->radius));
  vToggleN->on();
  //TODO: add toggle axis action
  mBuilder.append(NULL, vToggleN);

  return mBuilder.getResult();
}
//-------------------------------------------------------//
AbstractNode* Director::createSun(){
  return NULL;
}
//-------------------------------------------------------//
AbstractNode* Director::createSolarSystem(){
  GroupNode* vGroup = new GroupNode();
//  vGroup->add(createAxis());
  AbstractNode* vMoon = createPlanet(&(MoonDef()));
  AbstractNode* earth = createPlanet(&(EarthDef()), &vMoon, 1);
  
  AbstractNode* vRing = createSaturnRings(&(MarsDef()), "Textures/Saturnring.bmp");

  AbstractNode* mars = createPlanet(&(MarsDef()), &vRing, 1);
  vGroup->add(earth);
  vGroup->add(mars);
  vGroup->add(new StarsNode(200, 200, 10000));
  return vGroup;
}
//-------------------------------------------------------//
AbstractNode* Director::createSaturnRings(PlanetDef *aPlanetDef, char* aTextureName, float aInnerFactor, float aOuterFactor){
  TransformSeparator* vTSep = new TransformSeparator();
  // ring should be stable as the rotation axis of the planet
  vTSep->add(new RotorNode(-aPlanetDef->orbitVelocity, 0, 0, 1, 0));
  // same tilt as planet
  vTSep->add(new RotationNode(aPlanetDef->tilt, 1, 0, 0));

  vTSep->add( new TextureNode( createTexture(aTextureName)) );
  vTSep->add( new ColorNode(1, 1, 1) ); 
  float vInner = aPlanetDef->radius * aInnerFactor;
  float vOuter = aPlanetDef->radius * aOuterFactor;
  vTSep->add( new RingNode(vInner, vOuter, 64) );

  return vTSep;

}
//-------------------------------------------------------//
AbstractNode* Director::createAxis(float aLength){
  GroupNode* vG = new GroupNode();
  //TODO: axis toggle action
  vG->add(new ColorNode(1,0,0));
  vG->add(new LineNode(0, 0, 0, aLength, 0, 0, 3));

  vG->add(new ColorNode(0, 1, 0));
  vG->add(new LineNode(0, 0, 0, 0, aLength, 0, 3));

  vG->add(new ColorNode(0, 0, 1));
  vG->add(new LineNode(0, 0, 0, 0, 0, aLength, 3));

  return vG;
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//


