#include "nodes/ringnode.h"


//-------------------------------------------------------//
RingNode::RingNode(float fOuterRadius, float fInnerRadius, unsigned iQuadCount){
  mOuterRadius = fOuterRadius;
  mInnerRadius = fInnerRadius;
  mQuadCount = iQuadCount;   
  mVertexCount = iQuadCount * 2; //2 vertices overlap on edges -> re-use
 
  float phi = 2*(float)M_PI / (float)mQuadCount;
 
  //init vertices
  mVertices = new float*[mVertexCount];   
  for(int i = 0; i < mVertexCount ; i++) {
      mVertices[i] = new float[3];   
  }
 
  //calculate vertices
  for(int i = 0; i < mVertexCount / 2 ; i++) {
      //inner vertex
      mVertices[i][0] = mInnerRadius*cos(i*phi);
      mVertices[i][1] = 0;
      mVertices[i][2] = -mInnerRadius*sin(i*phi);                       
  }
  for(int i = mVertexCount / 2 ; i < mVertexCount ; i++) {
      //outer vertex
      mVertices[i][0] = mOuterRadius*cos(i*phi);
      mVertices[i][1] = 0;
      mVertices[i][2] = -mOuterRadius*sin(i*phi);                       
  }     
}

//-------------------------------------------------------//
void RingNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
RingNode::~RingNode(){
  for(int i=0; i<mVertexCount; i++){
    delete[] mVertices[i];
  }
  delete[] mVertices;
}
//-------------------------------------------------------//


