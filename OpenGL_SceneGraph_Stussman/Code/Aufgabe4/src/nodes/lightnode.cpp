#include "nodes/lightnode.h"


//-------------------------------------------------------//
LightNode::LightNode(GLenum aLightNr){
  mLightNr = aLightNr;
  mPos = new float[4];
  if(false == glIsEnabled(GL_LIGHTING)){
    glEnable(GL_LIGHTING);
  }
  if(false == glIsEnabled(aLightNr)){
    on();
  }
}
//----------------------------------------------------------//
LightNode::~LightNode(){
  delete[] mPos;
}
//----------------------------------------------------------//
void LightNode::setParam(GLenum aParamType, float aA, float aB, float aC, float aD){
  float vValues[] = {aA, aB, aC, aD};
  if(GL_POSITION){
    mPos[0] = aA;
    mPos[1] = aB;
    mPos[2] = aC;
    mPos[3] = aD;
  }
  glLightfv(mLightNr, aParamType, vValues);
}
//----------------------------------------------------------//
void LightNode::setPos(){
  glLightfv(mLightNr, GL_POSITION, mPos);
}
//----------------------------------------------------------//
inline void LightNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void LightNode::on(){
  glEnable(mLightNr);
}
//-------------------------------------------------------//
void LightNode::off(){
  glDisable(mLightNr);
}
//-------------------------------------------------------//
void LightNode::toggle(){
  if(glIsEnabled(mLightNr)){
    glDisable(mLightNr);
  }else{
    glEnable(mLightNr);
  }
}
//-------------------------------------------------------//

