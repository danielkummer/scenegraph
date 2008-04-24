#include "scene.h"



//-------------------------------------------------------//
AbstractScene::AbstractScene(){
  init();
  mActionFactory = new ActionFactory(mToActionMap, EActionNameCount);
}
//-------------------------------------------------------//
AbstractScene::~AbstractScene(){
  if(NULL != mSceneGraph){
    DestructorVisitor vDVisitor;
    vDVisitor.apply(mSceneGraph);
  }
  delete mSceneGraph;
  delete mActionFactory;
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
inline void AbstractScene::setSceneGraphRoot(AbstractNode *aNode){
  mSceneGraph = aNode;
}
//-------------------------------------------------------//
inline AbstractNode* AbstractScene::getSeneGraphRoot(){
  return mSceneGraph;
}
//-------------------------------------------------------//
void AbstractScene::init(){
}
//-------------------------------------------------------//
void AbstractScene::update(){
}
//-------------------------------------------------------//
void AbstractScene::handleEvent(SDL_Event &aEvent){
}
//-------------------------------------------------------//
void AbstractScene::createScene(){
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void SolarSytemScene::handleEvent(SDL_Event &aEvent){
  // TODO: do something with the events
}
//-------------------------------------------------------//
void SolarSytemScene::update(){
  
}
//-------------------------------------------------------//
void SolarSytemScene::init(){
  // TODO: define key mapping
  mKeyInputMap[SDLK_F2] = EToggleAxis;
  mKeyInputMap[SDLK_F3] = EToggleShadow;

  // action map
  // TODO: map all acitons
  mToActionMap[EToggleAxis] = EToggleAction;
  mToActionMap[EToggleShadow] = EToggleAction;
  mToActionMap[EToggleFar] = EToggleAction;
  mToActionMap[EToggleTrace] = EToggleAction;
//  mToActionMap[EShoot] = ;

  


}
//-------------------------------------------------------//
void SolarSytemScene::createScene(){
  

}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//


