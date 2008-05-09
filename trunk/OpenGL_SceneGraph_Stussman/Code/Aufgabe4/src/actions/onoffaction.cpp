#include "actions/onoffaction.h"


//----------------------------------------------------------//
OnOffAction::~OnOffAction(){

}
//----------------------------------------------------------//

OnOffAction::OnOffAction(){
  mOn = true;
}

//-------------------------------------------------------//
inline void OnOffAction::apply(){
  toggle();
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

