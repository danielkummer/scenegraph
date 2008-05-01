#include "actions/actions.h"

//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
ActionBase::ActionBase():mEnabled(true), mListeners(){
}
//-------------------------------------------------------//
ActionBase::~ActionBase(){
}
//-------------------------------------------------------//
void ActionBase::fire(){
  if(isEnabled()){ apply(); } 
}
//-------------------------------------------------------//
inline void ActionBase::enable(){
  mEnabled = true; 
}
//-------------------------------------------------------//
inline void ActionBase::disable(){ 
  mEnabled = false; 
}
//-------------------------------------------------------//
inline bool ActionBase::isEnabled(){ 
  return mEnabled; 
}
//-------------------------------------------------------//
void ActionBase::add(AbstractNode* aNode){
  mListeners.push_back(aNode);
}
//-------------------------------------------------------//
void ActionBase::remove(AbstractNode* aNode){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mListeners.begin(); vItr < mListeners.end(); vItr++){
    if(*vItr == aNode){
      vItr = mListeners.erase(vItr);
      break;
    }
  }
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
