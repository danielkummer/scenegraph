#include "nodes/colornode.h"

//-------------------------------------------------------//
ColorNode::ColorNode(float aRed, float aGreen, float aBlue):
mRed(aRed), mGreen(aGreen), mBlue(aBlue){
}
//-------------------------------------------------------//
ColorNode::~ColorNode(){
}
//-------------------------------------------------------//
inline void ColorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
