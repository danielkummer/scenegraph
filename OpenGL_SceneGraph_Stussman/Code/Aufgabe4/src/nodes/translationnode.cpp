#include "nodes/translationnode.h"

//-------------------------------------------------------//
TranslationNode::TranslationNode(float aX, float aY, float aZ):
AbstractNode(){
  mX = aX;
  mY = aY;
  mZ = aZ;
}
//-------------------------------------------------------//
inline void TranslationNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
