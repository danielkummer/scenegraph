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
	ToggleNode* vToggle = reinterpret_cast<ToggleNode*>(aToggle);
//  ActionBase::add(vToggle);
  mListeners.push_back(vToggle);
  // keep children syncronized
  if(mOn){
    vToggle->on();
  }else{
    vToggle->off();
  }
}
//-------------------------------------------------------//
void OnOffAction::on(){
  mOn = true;
  for(unsigned i=0; i < mListeners.size(); i++){
//    (reinterpret_cast<ToggleNode*>(mListeners[i]))->on();
    mListeners[i]->on();
  }
} 
//-------------------------------------------------------//
void OnOffAction::off(){
  mOn = false;
  for(unsigned i=0; i < mListeners.size(); i++){
//    (reinterpret_cast<ToggleNode*>(mListeners[i]))->off();
    mListeners[i]->off();
  }
} 
//-------------------------------------------------------//
void OnOffAction::toggle(){
  for(unsigned i=0; i < mListeners.size(); i++){
//    (reinterpret_cast<ToggleNode*>(mListeners[i]))->toggle();
    mListeners[i]->toggle();
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

