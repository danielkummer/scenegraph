#include "actions/shootaction.h"


ShootAction::ShootAction():public ActionBase(){

}
//-------------------------------------------------------//
ShootAction::~ShootAction(){

}
//-------------------------------------------------------//
ShootAction::fire(){
  if(mEnabled){
    for(unsigned i=0; i<mListeners; i++){
      mListeners[i]->spawn();
    }
  }
} 
//-------------------------------------------------------//
ShootAction::fire(float aVal){
  ShootAction::fire();
}
//-------------------------------------------------------//
ShootAction::add(AbstractNode *aNode){
  AbstractSpawn* vNode = reinterpret_cast<AbstractSpawn*>aNode;
  ActionBase::add(vNode);
}
//-------------------------------------------------------//
//-------------------------------------------------------//





