#include "nodes/colornode.h"

//-------------------------------------------------------//
ColorNode::ColorNode(float aRed, float aGreen, float aBlue, float aAlpha):
mRed(aRed), mGreen(aGreen), mBlue(aBlue), mAlpha(aAlpha){
}
//-------------------------------------------------------//
ColorNode::~ColorNode(){
}
//-------------------------------------------------------//
inline void ColorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
