#include "nodes/togglenode.h"


//----------------------------------------------------------//
ToggleNode::ToggleNode():GroupNode(){
}
//----------------------------------------------------------//
ToggleNode::~ToggleNode(){
}
//----------------------------------------------------------//
bool ToggleNode::isOn(){
  return mState;
}
//----------------------------------------------------------//
void ToggleNode::on(){ 
  mState = true; 
}
//----------------------------------------------------------//
void ToggleNode::off(){ 
  mState = false; 
}
//----------------------------------------------------------//
bool ToggleNode::toggle(){
  if(true == mState){
    mState = false;
  }else{
    mState = true;
  }
  return mState;
}
//----------------------------------------------------------//
void ToggleNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  if(true == mState){
    ToggleNode::visitChildren(aVisitor);
  }
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

