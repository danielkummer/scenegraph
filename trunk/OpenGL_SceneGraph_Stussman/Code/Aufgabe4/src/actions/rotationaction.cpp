#include "actions/rotationaction.h"



RotationAction::RotationAction(EAxis aAxis, float aAngle): 
ActionBase(), mAxis(aAxis), mAngle(aAngle){
  
}
//-------------------------------------------------------//
RotationAction::~RotationAction(){

}
//-------------------------------------------------------//
void RotationAction::apply(){
  for(unsigned i=0; i < mListeners.size(); i++){
    (reinterpret_cast<MoveNode*>(mListeners[i]))->rotate(mAxis, mAngle);
  }
}
//-------------------------------------------------------//




