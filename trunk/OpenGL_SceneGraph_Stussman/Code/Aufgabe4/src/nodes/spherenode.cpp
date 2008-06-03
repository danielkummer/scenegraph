#include "nodes/spherenode.h"




SphereNode::SphereNode(double aRadius, 
                       int aSlice, 
                       int aStacks, 
                       GLboolean aUseTexCoord):
AbstractNode()
{
  mRadius = aRadius;
  mSlices = aSlice;
  mStacks = aStacks;
  mUseTexCoord = aUseTexCoord;
}
//-------------------------------------------------------//
SphereNode::~SphereNode(){

}
//-------------------------------------------------------//
GLUquadric* SphereNode::mQuadric = gluNewQuadric();
//-------------------------------------------------------//
inline void SphereNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
