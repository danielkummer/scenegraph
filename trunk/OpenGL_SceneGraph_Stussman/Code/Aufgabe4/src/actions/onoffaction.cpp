#include "actions/onoffaction.h"


//----------------------------------------------------------//
OnOffAction::~OnOffAction(){

}
//----------------------------------------------------------//

OnOffAction::OnOffAction(){
  mOn = true;
}

//-------------------------------------------------------//
inline void OnOffAction::fire(){
  if(mEnabled){
    toggle();
  }
}
//-------------------------------------------------------//
inline void OnOffAction::fire(float aVal){
  fire();
}
//-------------------------------------------------------//
inline void OnOffAction::add(AbstractNode* aToggle){
	
  ActionBase::add(aToggle);
  // keep children syncronized
  if(mOn){
    reinterpret_cast<ToggleNode*>(aToggle)->on();
  }else{
    reinterpret_cast<ToggleNode*>(aToggle)->off();
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

