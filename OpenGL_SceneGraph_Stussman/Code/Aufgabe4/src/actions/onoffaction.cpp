#include "actions/onoffaction.h"


//----------------------------------------------------------//
OnOffAction::~OnOffAction(){

}
//-------------------------------------------------------//
inline void OnOffAction::apply(){
  toggle();
}
//-------------------------------------------------------//
inline void OnOffAction::add(ToggleNode* aToggle){
  ActionBase::add(aToggle);
  // keep children syncronized
  if(mOn){
    aToggle->on();
  }else{
    aToggle->off();
  }
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
  for(unsigned i=0; i < mListeners.size(); i++){
    (reinterpret_cast<ToggleNode*>(mListeners[i]))->toggle();
  }
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


//----------------------------------------------------------//

//----------------------------------------------------------//

