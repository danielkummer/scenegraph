#include "nodes/cam.h"



CamNode::CamNode():MoveNode(){
  for(unsigned i=0; i<16; i++){
    mTransform[i] = 0.0f;
  }
  mTransform[0] = 1.0f;
  mTransform[5] = 1.0f;
  mTransform[10] = 1.0f;
  mTransform[15] = 1.0f;


}
//----------------------------------------------------------//
CamNode::~CamNode(){

}
//----------------------------------------------------------//
void CamNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//


