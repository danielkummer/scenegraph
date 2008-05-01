#include "nodes/scalenode.h"

//-------------------------------------------------------//
ScaleNode::ScaleNode(float aScaleX, float aScaleY, float aScaleZ):
mScaleX(aScaleX), mScaleY(aScaleY), mScaleZ(aScaleZ){
}
//-------------------------------------------------------//
inline void ScaleNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
