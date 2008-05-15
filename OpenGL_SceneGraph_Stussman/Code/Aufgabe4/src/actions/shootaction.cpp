#include "actions/shootaction.h"


ShootAction::ShootAction():ActionBase(){

}
//-------------------------------------------------------//
ShootAction::~ShootAction(){

}
//-------------------------------------------------------//
void ShootAction::fire(){
  if(mEnabled){
    for(unsigned i=0; i<mListeners.size(); i++){
      reinterpret_cast<AbstractSpawn*>(mListeners[i])->spawn();
    }
  }
} 
//-------------------------------------------------------//
void ShootAction::fire(float aVal){
  ShootAction::fire();
}
//-------------------------------------------------------//
void ShootAction::add(AbstractNode *aNode){
  AbstractSpawn* vNode = reinterpret_cast<AbstractSpawn*>(aNode);
  ActionBase::add(vNode);
}
//-------------------------------------------------------//
//-------------------------------------------------------//





