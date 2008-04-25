#include "actions/onoffaction.h"


//-------------------------------------------------------//
OnOffAction::~OnOffAction(){

}
//-------------------------------------------------------//
inline void OnOffAction::apply(){
  toggle();
}
//-------------------------------------------------------//
//inline void OnOffAction::accept(AbstractVisitor &aVisitor){
//  aVisitor.visit(*this);
//}
//-------------------------------------------------------//
inline void OnOffAction::add(ToggleNode* aToggle){
  ActionBase::add(aToggle);
}
//-------------------------------------------------------//
void OnOffAction::on(){
  mOn = true;
  for(unsigned i=0; i < mListeners.size(); i++){
    (reinterpret_cast<ToggleNode*>(mListeners[i]))->on();
  }
} 
//-------------------------------------------------------//
void OnOffAction::off(){
  mOn = false;
  for(unsigned i=0; i < mListeners.size(); i++){
    (reinterpret_cast<ToggleNode*>(mListeners[i]))->off();
  }
} 
//-------------------------------------------------------//
void OnOffAction::toggle(){
  if(mOn){
    mOn = false;
    for(unsigned i=0; i < mListeners.size(); i++){
      (reinterpret_cast<ToggleNode*>(mListeners[i]))->off();
    }
  }else{
    mOn = true;
    for(unsigned i=0; i < mListeners.size(); i++){
      (reinterpret_cast<ToggleNode*>(mListeners[i]))->on();
    }
  }
//  for(unsigned i=0; i < mChildren.size(); i++){
//    (reinterpret_cast<ToggleNode*>(mChildren[i]))->toggle();
//  }
}
//-------------------------------------------------------//
inline bool OnOffAction::isOn(){
  return mOn;
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//


