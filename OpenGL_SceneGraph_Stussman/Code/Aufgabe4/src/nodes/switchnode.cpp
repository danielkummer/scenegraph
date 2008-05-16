#include "nodes/switchnode.h"


//----------------------------------------------------------//
void SwitchNode::accept(AbstractVisitor &aVisitor){
  realAdd();
  aVisitor.visit(*this);
  if(mCurrent >= 0 && mCurrent<(int)mChildren.size()){
    mChildren[mCurrent]->accept(aVisitor);
  }
  aVisitor.postvisit(*this);
  realRemove();
}
//----------------------------------------------------------//
void SwitchNode::switchTo(unsigned int aChildNr){
  realAdd();
  if(aChildNr >= 0 && aChildNr <(unsigned)mChildren.size()){
    mCurrent = aChildNr;
  }else{
    mCurrent = -1;
  }
}
//----------------------------------------------------------//
int SwitchNode::getCurrent(){
  return mCurrent;
}
//----------------------------------------------------------//
int SwitchNode::getNumChildren(){
  return (int)mChildren.size();
}
//----------------------------------------------------------//

