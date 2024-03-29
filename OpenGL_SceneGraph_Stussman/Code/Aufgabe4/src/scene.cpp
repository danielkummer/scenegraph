#include <assert.h>

#include "scene.h"
#include "nodes/materialnode.h"



///**************************************************/
///* Create texture                                 */
///**************************************************/
//
//int createTexture(char *strFileName)
//{
//	SDL_Surface *bitmap;													// SDL_Surface to load the image into
//	SDL_Surface *conv;														// SDL_Surface to copy the image into (with correct color order)
//															
//	int pitch;																// Variable to store the length of one pixel-line
//	int height_div_2;														// Variable to store the size of half the number of rows
//
//	void* temp_row;															// Variable to store the pointer to a pixel-line
//
//	bitmap = SDL_LoadBMP(strFileName);										// Load image into an SDL_Surface
//	
//	if (!bitmap)															// If loading failed
//	{																		//
//	   printf("Could not load texture %s.\n",strFileName);					// print an error message
//	   quit_program( 0 );													// and quit
//	}
//
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN											// Select wether we use RGB or BGR mode 
//	conv = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 32,0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff); // Create an SDL-Surface (big endian)
//#else
//	conv = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 32,0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000); // Create an SDL-Surface (little endian)
//#endif
//
//	SDL_BlitSurface(bitmap, 0, conv, 0);									// Copy the loaded image to the surface with the correct color order
//
//	// Flip Loaded Bitmap upside down
//	// (SDL and OpenGL use diffrent Coordinate Systems)
//	////////////////////////////////////////////////////////
//	pitch = conv->pitch;													// length of one pixel-line
//
//	temp_row = (void *)malloc(pitch);										// Allocate memory for the inversion
//	if(NULL == temp_row)													// If you're not able to allocate the memory
//	{																		//
//		SDL_SetError("Not enough memory for image inversion");				// display an error message
//	}
//	height_div_2 = (int) (conv->h * .5);									// use only one half of the rows. (Works also with a odd number of rows)
//	for(int index = 0; index < height_div_2; index++)							// for every line in the lower half swap it with the corresponding line
//	{																		// in the upper half
//		memcpy(
//			(Uint8 *)temp_row,												// 
//			(Uint8 *)(conv->pixels) + pitch * index,						// copy one line from the first half to the temp variable
//			pitch);															// size of one line
//		memcpy(
//			(Uint8 *)(conv->pixels) + pitch * index,						//
//			(Uint8 *)(conv->pixels) + pitch * (conv->h - index-1),			// copy the corresponding line from the upper half to the line in the lower half
//			pitch);															// size of one line
//		memcpy(
//			(Uint8 *)(conv->pixels) + pitch * (conv->h - index-1),			//
//			temp_row,														// copy the tempvariable back to the corresponding line in the upper half
//			pitch);															// size of one line
//	}
//	free(temp_row);															// free allocated memory now that we don't need it anymore
//
//	// End flipping
//	/////////////////////////////////////////////////////////
//  unsigned int texId;
//	glGenTextures(1, &texId);									// Generate a new texture ID
//	glBindTexture(GL_TEXTURE_2D, texId);						// Bind the texture (the following commands work with this texture)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// Set the filter mode for magnification to linear
////  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		// Set the filter mode for magnification to linear
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// Set the filter mode for minification to linear
////  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);		// Set the filter mode for minification to linear
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// Set the wrapping mode for the texturecoourdinate s to repeat
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			// Set the wrapping mode for the texturecoourdinate t to repeat
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, conv->w, conv->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, conv->pixels);	//copy the image into the texture
//	SDL_FreeSurface(bitmap);
//	SDL_FreeSurface(conv);
//  int vErr = glGetError();
//  if(0!=vErr){
//    printf("GL_ERROR@createTexture(): %i %s %s\n", vErr, gluErrorString(vErr), strFileName);
//  }
//  return texId;
//}

//-------------------------------------------------------//



//-------------------------------------------------------//
AbstractScene::AbstractScene():
mSceneGraph(NULL), mActionFactory(NULL)
{
  for(unsigned i=0; i<EActionNameCount; i++){
    mToActionMap[i] = 0;
  }
  for(unsigned i=0; i<SDLK_LAST; i++){
    mKeyInputMap[i] = 0;
    mKeyFlags[i] = 0;    
  }
}
//-------------------------------------------------------//
AbstractScene::~AbstractScene(){
  mSceneGraph->unref();
  delete mActionFactory;
  TextureManager::getReference()->deleteRef();
}
//-------------------------------------------------------//
void AbstractScene::setActionMap(unsigned int aEActionName, unsigned int aEAction){
  mToActionMap[aEActionName] = aEAction;
}
//-------------------------------------------------------//
void AbstractScene::setActionMap(unsigned int *aEAcitonMap, unsigned int aCount){
  for(unsigned i=0; i<aCount; i++){
    mToActionMap[i] = aEAcitonMap[i];
  }
}
//-------------------------------------------------------//
void AbstractScene::setKeyInputMap(SDLKey aKey, unsigned int aEActionName){
  mKeyInputMap[aKey] = aEActionName;
}
//-------------------------------------------------------//
void AbstractScene::setKeyInputMap(SDLKey *aKeyMap, unsigned int aCount){
  for(unsigned i=0; i<aCount; i++){
    mKeyInputMap[i] = aKeyMap[i];
  }
}
//-------------------------------------------------------//
inline void AbstractScene::setSceneGraphRoot(GroupNode *aNode){
  mSceneGraph = aNode;
}
//-------------------------------------------------------//
inline GroupNode* AbstractScene::getSeneGraphRoot(){
  return mSceneGraph;
}
//-------------------------------------------------------//
void AbstractScene::init(){
}
//-------------------------------------------------------//
void AbstractScene::update(){
  for(unsigned i=0; i<SDLK_LAST; i++){
    if(1==mKeyFlags[i]){
      unsigned vKeyMapVal = mKeyInputMap[i];
      if(0 != vKeyMapVal){
        mActionFactory->getAction(vKeyMapVal)->fire();
      }
    }
  }
  assert(NULL != mSceneGraph);
  mVisitor.apply(mSceneGraph);
}
//-------------------------------------------------------//
bool AbstractScene::handleEvent(SDL_Event &aEvent){
  if(aEvent.type == SDL_KEYDOWN){
    if(2 > mKeyFlags[aEvent.key.keysym.sym]){
      mKeyFlags[aEvent.key.keysym.sym] = true;
      return true;
    }else{
      unsigned vKeyMapVal = mKeyInputMap[aEvent.key.keysym.sym];
      if(0 != vKeyMapVal){
        mActionFactory->getAction(vKeyMapVal)->fire();
        return true;
      }
    }
  }
  if(aEvent.type == SDL_KEYUP &&  2 > mKeyFlags[aEvent.key.keysym.sym]){
    mKeyFlags[aEvent.key.keysym.sym] = false;
	  return true;    
  }
  return false;
}
//-------------------------------------------------------//
void AbstractScene::createScene(){
  mActionFactory = new ActionFactory(mToActionMap, EActionNameCount);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
SolarSytemScene::SolarSytemScene():AbstractScene(), mAxis(NULL){

}
//-------------------------------------------------------//
SolarSytemScene::~SolarSytemScene(){
}
//-------------------------------------------------------//
bool SolarSytemScene::handleEvent(SDL_Event &aEvent){
	float mousetune = 0.1f;
  if( !AbstractScene::handleEvent(aEvent)){
    // TODO: do something with the events
    // Handle mouse events
    if(aEvent.type == SDL_MOUSEMOTION) {
    	//TODO: redo!!
    	float xangle = -(aEvent.motion.xrel * mousetune);
  		float yangle = -(aEvent.motion.yrel * mousetune);
 			mActionFactory->getAction(ECamPitchClockwise)->fire(yangle);
			mActionFactory->getAction(ECamYawClockwise)->fire(xangle);
      return true;
    }
    if(aEvent.type == SDL_MOUSEBUTTONDOWN) {
    	
    	if(aEvent.button.button == 5) {
    		Clock::getDefaultClock()->setDilatation(Clock::getDefaultClock()->getDilatation() + 0.1f);	
    	} else if(aEvent.button.button == 4) {
    		Clock::getDefaultClock()->setDilatation(Clock::getDefaultClock()->getDilatation() - 0.1f);
    	}		
    } 
    
  }
  return false;
}
//-------------------------------------------------------//
//void SolarSytemScene::update(){
  
//}
//-------------------------------------------------------//
void SolarSytemScene::init(){
  // TODO: define key mapping
  mKeyInputMap[SDLK_F2] = EToggleAxis;
  mKeyInputMap[SDLK_F3] = EToggleShadow;
  mKeyInputMap[SDLK_F4] = EToggleLight;
  mKeyInputMap[SDLK_TAB] = ECamSwitchType;
  // prevent contious action firing (fire only at keypress once)
  mKeyFlags[SDLK_F2] = 2;
  mKeyFlags[SDLK_F3] = 2;
  mKeyFlags[SDLK_F4] = 2;
  mKeyFlags[SDLK_F5] = 2;
  mKeyFlags[SDLK_TAB] = 2;
//  mKeyFlags[SDLK_SPACE] = 2;


  // Ship key bindings
  mKeyInputMap[SDLK_a] = EShipMoveFwd;
  mKeyInputMap[SDLK_d] = EShipMoveBack;
  mKeyInputMap[SDLK_w] = EShipStrafeLeft;
  mKeyInputMap[SDLK_s] = EShipStrafeRight;
  mKeyInputMap[SDLK_q] = EShipMoveUp;
  mKeyInputMap[SDLK_e] = EShipMoveDown;

  mKeyInputMap[SDLK_r] = EShipRollClk;
  mKeyInputMap[SDLK_f] = EShipRollCClk;
  mKeyInputMap[SDLK_t] = EShipPitchClk;
  mKeyInputMap[SDLK_g] = EShipPitchCClk;
  mKeyInputMap[SDLK_y] = EShipYawClk;
  mKeyInputMap[SDLK_z] = EShipYawClk;
  mKeyInputMap[SDLK_h] = EShipYawCClk;

  mKeyInputMap[SDLK_SPACE] = EShipShoot;

  // Camera key bindings
  mKeyInputMap[SDLK_F5] = ECamSwitchType;
  mKeyInputMap[SDLK_i] 	= ECamMoveFwd;
  mKeyInputMap[SDLK_k] 	= ECamMoveBack;
  mKeyInputMap[SDLK_j] 	= ECamStrafeRight;
  mKeyInputMap[SDLK_l] 	= ECamStrafeLeft;
  mKeyInputMap[SDLK_u] 	= ECamMoveUp;
  mKeyInputMap[SDLK_o] 	= ECamMoveDown;

  mKeyInputMap[SDLK_m] 	= ECamRollClockwise;
  mKeyInputMap[SDLK_n] 	= ECamRollCClockwise;
  mKeyInputMap[SDLK_b] 	= ECamPitchClockwise;
  mKeyInputMap[SDLK_v] 	= ECamPitchCClockwise;
  mKeyInputMap[SDLK_c] 	= ECamYawClockwise;
  mKeyInputMap[SDLK_x] 	= ECamYawCClockwise;


  // action map
  // TODO: map all acitons
  
  // Generic action mappings
  mToActionMap[EToggleAxis] 	= EToggleAction;
  mToActionMap[EToggleShadow] 	= EToggleAction;
  mToActionMap[EToggleLight] 	= EToggleAction;
  mToActionMap[EToggleFar] 		= EToggleAction;
  mToActionMap[EToggleTrace] 	= EToggleAction;

  // Ship action mapping
  mToActionMap[EShipMoveFwd] 	= EShipMoveFwdAction;
  mToActionMap[EShipMoveBack] 	= EShipMoveBackAction;
  mToActionMap[EShipMoveUp] 	= EShipMoveUpAction;
  mToActionMap[EShipMoveDown] 	= EShipMoveDownAction;
  mToActionMap[EShipStrafeLeft] = EShipStrafeLeftAction;
  mToActionMap[EShipStrafeRight]= EShipStrafeRightAction;

  mToActionMap[EShipRollClk] 	= EShipRollClkAction;
  mToActionMap[EShipRollCClk] 	= EShipRollCClkAction;
  mToActionMap[EShipPitchClk] 	= EShipPitchClkAction;
  mToActionMap[EShipPitchCClk] 	= EShipPitchCClkAction;
  mToActionMap[EShipYawClk] 	= EShipYawClkAction;
  mToActionMap[EShipYawCClk] 	= EShipYawCClkAction;
  mToActionMap[EShipShoot] = EShipShootAction;

  // Camera action Mapping
  mToActionMap[ECamSwitchType]	= ECamSwitchTypeAction;	
  mToActionMap[ECamMoveFwd]	 = ECamMoveFwdAction;
  mToActionMap[ECamMoveBack] = ECamMoveBackAction;

  mToActionMap[ECamStrafeRight] = ECamStrafeRightAction;
  mToActionMap[ECamStrafeLeft]  = ECamStrafeLeftAction;

  mToActionMap[ECamMoveUp]	 = ECamMoveUpAction;
  mToActionMap[ECamMoveDown] = ECamMoveDownAction;

  mToActionMap[ECamRollClockwise]	 = ECamRollClockwiseAction;
  mToActionMap[ECamRollCClockwise] = ECamRollCClockwiseAction;

  mToActionMap[ECamPitchClockwise]  = ECamPitchClockwiseAction;
  mToActionMap[ECamPitchCClockwise]	= ECamPitchCClockwiseAction;

  mToActionMap[ECamYawClockwise]  = ECamYawClockwiseAction;
  mToActionMap[ECamYawCClockwise]	= ECamYawCClockwiseAction;
}
//-------------------------------------------------------//
void SolarSytemScene::createScene(){

  AbstractScene::createScene();
//  Director vDirector;
  mSceneGraph = new Separator();
  mSceneGraph->ref();

  //Scene Camera
  SwitchNode* vCamSwitchNode = new SwitchNode();
  Builder vCameraBuilder(vCamSwitchNode, mActionFactory->getAction(ECamSwitchType));

  std::vector<ActionBase*> vCameraActions;
  
  vCameraActions.push_back(mActionFactory->getAction(ECamMoveBack));
  vCameraActions.push_back(mActionFactory->getAction(ECamMoveDown));
  vCameraActions.push_back(mActionFactory->getAction(ECamMoveFwd));
  vCameraActions.push_back(mActionFactory->getAction(ECamMoveUp));
  vCameraActions.push_back(mActionFactory->getAction(ECamStrafeLeft));
  vCameraActions.push_back(mActionFactory->getAction(ECamStrafeRight));

  vCameraActions.push_back(mActionFactory->getAction(ECamRollClockwise));
  vCameraActions.push_back(mActionFactory->getAction(ECamRollCClockwise));
  vCameraActions.push_back(mActionFactory->getAction(ECamPitchClockwise));
  vCameraActions.push_back(mActionFactory->getAction(ECamPitchCClockwise));
  vCameraActions.push_back(mActionFactory->getAction(ECamYawClockwise));
  vCameraActions.push_back(mActionFactory->getAction(ECamYawCClockwise));
  
  vCameraBuilder.buildCamNode(vCameraActions);
  mSceneGraph->add(vCameraBuilder.getResult());

  DefaultMaterial vMat;
  mSceneGraph->add(new MaterialNode(GL_FRONT_AND_BACK, &vMat));
  mSceneGraph->add(new ColorNode(1, 1, 1, 1));

  // scene axis
//  mSceneGraph->add(createAxis(20));

  // light
  LightNode* vLight = new LightNode(GL_LIGHT0);
  vLight->setParam(GL_AMBIENT, 0.1f, 0.1f, 0.1f, 1.0f);
  vLight->setParam(GL_DIFFUSE, 0.8f, 0.8f, 0.8f, 1.0f);
  vLight->setParam(GL_POSITION, 1.0f, 1.0f, 1.0f, 1.0f);
  mSceneGraph->add(vLight);

  mSceneGraph->add(createSolarSystem());  
  
  
  // spaceship
  Builder vSpaceShipBuilder(new TransformSeparator());
  
  std::vector<ActionBase*> vShipActions;
  
  vShipActions.push_back(mActionFactory->getAction(EShipMoveBack));
  vShipActions.push_back(mActionFactory->getAction(EShipMoveDown));
  vShipActions.push_back(mActionFactory->getAction(EShipMoveFwd));
  vShipActions.push_back(mActionFactory->getAction(EShipMoveUp));
  vShipActions.push_back(mActionFactory->getAction(EShipStrafeLeft));
  vShipActions.push_back(mActionFactory->getAction(EShipStrafeRight));

  vShipActions.push_back(mActionFactory->getAction(EShipRollClk));
  vShipActions.push_back(mActionFactory->getAction(EShipRollCClk));
  vShipActions.push_back(mActionFactory->getAction(EShipPitchClk));
  vShipActions.push_back(mActionFactory->getAction(EShipPitchCClk));
  vShipActions.push_back(mActionFactory->getAction(EShipYawClk));
  vShipActions.push_back(mActionFactory->getAction(EShipYawCClk));
  
  vSpaceShipBuilder.buildMoveNode(vShipActions);

  CamFollowNode* vShipCamera = new CamFollowNode(vSpaceShipBuilder.getLast());      
  vCamSwitchNode->add(vShipCamera);   
  vCamSwitchNode->switchTo(0);


  vSpaceShipBuilder.buildPolygonObjectNode("objects/spaceship.obj", "objects/spaceship.mtl");
  vSpaceShipBuilder.append(0, createAxis(5));
  
  vSpaceShipBuilder.buildLightNode(GL_LIGHT1, 
                                        3.0f, // pos
                                        0.0f, 
                                        0.0f, 
                                        1.0f, 
                                        0.2f, // ambient
                                        0.2f, 
                                        0.2f, 
                                        1.0f, 
                                        1.0f, // diffuse
                                        1.0f, 
                                        1.0f, 
                                        1.0f, 
                                        mActionFactory->getAction(EToggleLight));
  LightNode* vLightNode = reinterpret_cast<LightNode*>(vSpaceShipBuilder.getLast());
  vLightNode->setParam(GL_SPOT_DIRECTION, 0, 0, -1, 1);
  vLightNode->setParam(GL_SPOT_EXPONENT, 50, 0, 0, 0);
  vLightNode->setParam(GL_SPOT_CUTOFF, 40, 0, 0, 0);

//TODO: add offset to position the shot to the wings
  Builder vRCannon(new TransformSeparator());
  vRCannon.buildTranslationNode(0, -0.25, 0.75);
//  vRCannon.buildShootSpawn(mSceneGraph, mActionFactory->getAction(EShipShoot));
  vRCannon.buildLaserSpawn(mSceneGraph, mActionFactory->getAction(EShipShoot));
  vSpaceShipBuilder.append(NULL, vRCannon.getResult());
    
  Builder vLCannon(new TransformSeparator());
  vLCannon.buildTranslationNode(0, -0.25, -0.75);
  vLCannon.buildShootSpawn(mSceneGraph, mActionFactory->getAction(EShipShoot));
//  vLCannon.buildLaserSpawn(mSceneGraph, mActionFactory->getAction(EShipShoot));
  vSpaceShipBuilder.append(NULL, vLCannon.getResult());

  mSceneGraph->add(vSpaceShipBuilder.getResult());

  TransformSeparator* vTS;
  TransDefaultMaterial vTMat;
  Separator* vS;
  for(unsigned i=0; i<1; i++){
//    //TODO: remove test quad
    vTS = new TransformSeparator();
    unsigned vFlames[16];
    vFlames [0] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame1.bmp");
    vFlames [1] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame2.bmp");
    vFlames [2] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame3.bmp");
    vFlames [3] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame4.bmp");
    vFlames [4] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame5.bmp");
    vFlames [5] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame6.bmp");
    vFlames [6] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame7.bmp");
    vFlames [7] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame8.bmp");
    vFlames [8] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame9.bmp");
    vFlames [9] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame10.bmp");
    vFlames[10] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame11.bmp");
    vFlames[11] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame12.bmp");
    vFlames[12] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame13.bmp");
    vFlames[13] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame14.bmp");
    vFlames[14] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame15.bmp");
    vFlames[15] = TextureManager::getReference()->createTexture("Textures/corona_anim/flame16.bmp");

//    vTS->add(new TextureNode(createTexture("Textures/th_Corona.bmp"), GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_TEXTURE_2D));
    vTS->add(new TextureAnimator(16, vFlames, GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_TEXTURE_2D, 16));

    vTMat = TransDefaultMaterial(0.5f);
    vTMat.set(GL_EMISSION, 1.0, 1.0, 1.0, 1.0);

    vTS->add(new MaterialNode(GL_FRONT_AND_BACK, &vTMat));
    vTS->add(new Billboard(9, 9));
////    mTS->add(new Quad(9, 9, 0, 0, 0, 1, 1, 1, 0, 1, 0));
////    mTS->add(new Quad(9, 9, 0, 0, 0, rand()-32500, rand()-32500, rand()-32500, 0, 1, 0));
//    vTS->add(new MaterialNode(GL_FRONT_AND_BACK, &DefaultMaterial()));
    vS = new Separator();
    vS->add(vTS);
    mSceneGraph->add(vS);
  }
  
  PrintVisitor().apply(mSceneGraph);  
}

//-------------------------------------------------------//
AbstractNode* SolarSytemScene::createPlanet(PlanetDef* aPlanetDef, bool aMoonYesOrNo, float aAlpha){
  try
  {
  	RingDef* ring = dynamic_cast <RingDef*> (aPlanetDef);
  	if(ring) 
  		return createPlanet(ring);
  }catch (std::bad_cast)
  { 
  //dynamic_cast<> failed
  }

  Builder vBuilder(new TransformSeparator());

  vBuilder.buildRotationNode(aPlanetDef->orbitInclination, 1, 0, 0);
  vBuilder.buildRotorNode(aPlanetDef->orbitVelocity, 0, 0, 1, 0); // rot around sun
  vBuilder.buildTranslationNode(aPlanetDef->orbitRadius, 0, 0); // radius to sun

  // moons
  if(true == aMoonYesOrNo){
    for(unsigned i=0; i<aPlanetDef->mMoons.size(); i++){
      vBuilder.append(NULL, createPlanet(aPlanetDef->mMoons[i], true, (aPlanetDef->mMoons[i])->mAlpha));
    }
  }

  // shadows
  float vPos[4] = {0.0f, 10.0f, 0.0f, 1.0f};
  float vNormal[4] = {0.0f, 1.0f, 0.0f, 1.0f};
  float vPoint[4] = {0.0f, -3.0f, 0.0f, 1.0f};
  float vColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  ShadowNode* vShadowN = new ShadowNode(vPos, vNormal, vPoint, vColor);
  vShadowN->setNodeToShadow(new SphereNode(aPlanetDef->radius));
  Separator* vSepNode = new Separator();
  vSepNode->add(vShadowN);
  ToggleNode* vToggle = new ToggleNode();
  vToggle->off();
  vToggle->add(vSepNode);
  vBuilder.append(mActionFactory->getAction(EToggleShadow), vToggle);

  // anti rotation for stable axis
  if(aPlanetDef->mAntiRot){
    vBuilder.buildRotorNode(-aPlanetDef->orbitVelocity, 0, 0, 1, 0); // anti rotation
  }

  vBuilder.buildRotationNode(aPlanetDef->tilt, 1, 0, 0); // tilt
  vBuilder.buildRotorNode(aPlanetDef->rotVelocity, 0, 0, 1, 0);
  vBuilder.buildRotationNode(90, 1, 0, 0);
  //TODO: add textures, material, color here
  int vTexId = TextureManager::getReference()->createTexture(aPlanetDef->textureName);
  if(1.0f > aAlpha){
    vBuilder.buildTextureNode(vTexId, GL_TEXTURE_2D, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, NULL);
  }else{
    vBuilder.buildTextureNode(vTexId);
  }
  if(NULL != aPlanetDef->material){
    vBuilder.buildMaterialNode(GL_FRONT_AND_BACK, aPlanetDef->material);
  }
  if(1.0f > aAlpha){
    vBuilder.buildColorNode(1, 1, 1, aAlpha, NULL);
  }
  vBuilder.buildSphereNode(aPlanetDef->radius, 32, 32, true);
  // TODO: why does the 2 following lines cause a memoryleak!?!?!?!?
  // only for transparent spheres!?
  AbstractNode* vLast = vBuilder.getLast();
  vLast->mCollidable = 1;

  // axis
  ToggleNode* vToggleN = new ToggleNode();
  vToggleN->add(createAxis(4*aPlanetDef->radius));
  vToggleN->off();
  vBuilder.append(mActionFactory->getAction(EToggleAxis), vToggleN);

  Separator* vSep = new Separator();
  vSep->add(vBuilder.getResult());

  return vSep;

}
//-------------------------------------------------------//
AbstractNode* SolarSytemScene::createPlanet(RingDef* aRingDef){
  PlanetDef* vPlanetDef = aRingDef->mPlanetDef;
  TransformSeparator* vTSep = new TransformSeparator();
  // ring should be stable as the rotation axis of the planet
  vTSep->add(new RotorNode(-vPlanetDef->orbitVelocity, 0, 0, 1, 0));
  // same tilt as planet
  vTSep->add(new RotationNode(vPlanetDef->tilt, 1, 0, 0));

  vTSep->add( new TextureNode( TextureManager::getReference()->createTexture(aRingDef->textureName)) );
  vTSep->add( new ColorNode(1, 1, 1) ); 
  float vInner = vPlanetDef->radius * aRingDef->mInnerFactor;
  float vOuter = vPlanetDef->radius * aRingDef->mOuterFactor;
  vTSep->add( new RingNode(vInner, vOuter, 64) );
//  vTSep->add( new RotationNode(180, 1, 0, 0) );
//  vTSep->add( new RingNode(vInner, vOuter, 64) );

  return vTSep;
}
//-------------------------------------------------------//
AbstractNode* SolarSytemScene::createSolarSystem(){
  TransformSeparator* vTSep = new TransformSeparator();

  // Sun
  SunDef vSunD;
  vTSep->add(createPlanet(&vSunD));
  // Sun surface
  SunTransDef vSunDTrans;
  int vDir = 1;
  float vAlpha = 0.5f;
  for(unsigned i=0; i<3; i++){
    vSunDTrans.radius += .015f;
    vSunDTrans.rotVelocity += 1.01f;
    vDir = -vDir;
    vSunDTrans.rotVelocity = vDir * vSunDTrans.rotVelocity;
    vTSep->add(createPlanet(&vSunDTrans, true, vAlpha));
    vAlpha -= 0.1f;
    vSunDTrans.rotVelocity = vDir * vSunDTrans.rotVelocity;
  }

  // stars
  Separator* vStarsSep = new Separator();
  Material* vEmitMat = new DefaultMaterial();
  vEmitMat->set(GL_EMISSION, 1, 1, 1);
  vEmitMat->set(GL_COLOR, 1, 1, 1);
  vStarsSep->add(new MaterialNode(GL_FRONT_AND_BACK, vEmitMat));
  delete vEmitMat; // MaterialNode copies the values
  vStarsSep->add(new StarsNode(500, 400, 10000));
  vTSep->add(vStarsSep);
  return vTSep;
}
//-------------------------------------------------------//
AbstractNode* SolarSytemScene::createAxis(float aLength){

  if(NULL==mAxis){
    Builder vBuilder(new Separator());

    DefaultMaterial vMat;
    vBuilder.buildMaterialNode(GL_FRONT_AND_BACK, &vMat);

    vBuilder.buildColorNode(1, 0, 0);
    vBuilder.buildLineNode(0, 0, 0, 1, 0, 0, 3);

    vBuilder.buildColorNode(0, 1, 0);
    vBuilder.buildLineNode(0, 0, 0, 0, 1, 0, 3);

    vBuilder.buildColorNode(0, 0, 1);
    vBuilder.buildLineNode(0, 0, 0, 0, 0, 1, 3);

    vBuilder.buildColorNode(1, 1, 1);
    DefaultMaterial vDMat;
    vBuilder.buildMaterialNode(GL_FRONT_AND_BACK, &vDMat);
    mAxis = vBuilder.getResult();
  }

  Builder vRootBuilder(new ToggleNode(), mActionFactory->getAction(EToggleAxis));
  Builder vTSepBuilder(new TransformSeparator(), NULL);
  vTSepBuilder.buildUniformScaleNode(aLength, NULL);
  vTSepBuilder.append(NULL, mAxis);

  vRootBuilder.append(NULL, vTSepBuilder.getResult());
  
  return vRootBuilder.getResult();
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//


