#include "actions/moveaction.h"



MoveAction::MoveAction(EDirection aDir, float aDist): 
ActionBase(), mDir(aDir), mDist(aDist){
  
}
//-------------------------------------------------------//
MoveAction::~MoveAction(){

}
//-------------------------------------------------------//
void MoveAction::apply(){
  for(unsigned i=0; i < mListeners.size(); i++){
    (reinterpret_cast<MoveNode*>(mListeners[i]))->move(mDir, mDist);
  }
}
//-------------------------------------------------------//




