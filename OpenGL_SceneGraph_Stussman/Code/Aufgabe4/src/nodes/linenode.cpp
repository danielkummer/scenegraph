#include "nodes/linenode.h"

//-------------------------------------------------------//
LineNode::LineNode(float aVert1X,
                   float aVert1Y, 
                   float aVert1Z, 
                   float aVert2X, 
                   float aVert2Y, 
                   float aVert2Z, 
                   float aWidth):
mVert1X(aVert1X),
mVert1Y(aVert1Y),
mVert1Z(aVert1Z),
mVert2X(aVert2X),
mVert2Y(aVert2Y),
mVert2Z(aVert2Z),
mWidth(aWidth){
}
//-------------------------------------------------------//
inline void LineNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
