#include "nodes/rotationnode.h"


//-------------------------------------------------------//
RotationNode::RotationNode(float aAngle, float aAxisX, float aAxisY, float aAxisZ):
AbstractNode(){
  mAxisX = aAxisX;
  mAxisY = aAxisY;
  mAxisZ = aAxisZ;
  setAngle(aAngle);
}
//-------------------------------------------------------//
void RotationNode::setAngle(float aAngle){
  mGradAngle = aAngle;
}
//-------------------------------------------------------//
inline void RotationNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}

//-------------------------------------------------------//
