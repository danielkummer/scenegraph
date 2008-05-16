#include "actions/switchaction.h"



//SwitchAction::SwitchAction(){
//
//
//}
////-------------------------------------------------------//
//SwitchAction::~SwitchAction(){
//
//}
////-------------------------------------------------------//
void SwitchAction::fire(){
  if(mEnabled){
    for(unsigned i=0; i<mListeners.size(); i++){
      SwitchNode* vNode = reinterpret_cast<SwitchNode*>(mListeners[i]);
      int vNum = vNode->getNumChildren();
      int vCur = vNode->getCurrent();
      if(0<=vCur){
        vCur++;
        if(vCur>=vNum){
          vCur = 0;
        }
        vNode->switchTo(vCur);
      }
    }
  }
}
//-------------------------------------------------------//
void SwitchAction::fire(float aValue){
  SwitchAction::fire();
}
//-------------------------------------------------------//




