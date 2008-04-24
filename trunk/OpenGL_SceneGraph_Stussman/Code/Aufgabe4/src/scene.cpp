#include "scene.h"
#include <assert.h>



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
  mSceneGraph->unref();
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
  assert(NULL != mSceneGraph);
  mVisitor.apply(mSceneGraph);
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
SolarSytemScene::SolarSytemScene():AbstractScene(){
  init();
}
//-------------------------------------------------------//
void SolarSytemScene::handleEvent(SDL_Event &aEvent){
  // TODO: do something with the events
}
//-------------------------------------------------------//
//void SolarSytemScene::update(){
  
//}
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

  
  createScene();

}
//-------------------------------------------------------//
void SolarSytemScene::createScene(){

  Director vDirector;
  mSceneGraph = new GroupNode();
  mSceneGraph->ref();
  mSceneGraph->add(vDirector.createSolarSystem());

  PrintVisitor().apply(mSceneGraph);
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//


