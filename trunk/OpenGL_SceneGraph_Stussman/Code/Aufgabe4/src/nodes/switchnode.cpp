#include "nodes/switchnode.h"


//----------------------------------------------------------//
void SwitchNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  if(mCurrent >= 0 && mCurrent<(int)mChildren.size()){
    mChildren[mCurrent]->accept(aVisitor);
  }
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//
void SwitchNode::switchTo(unsigned int aChildNr){
  if(aChildNr >= 0 && aChildNr <(unsigned)mChildren.size()){
    mCurrent = aChildNr;
  }else{
    mCurrent = -1;
  }
}
//----------------------------------------------------------//

