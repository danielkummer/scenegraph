#include "nodes/lightnode.h"

LightNode::LightNode(GLenum aLightNr, float posX, float posY, float posZ, float posW, float ambA, float ambB, float ambC, float ambD, float diffA, float diffB, float diffC, float diffD) {
	
	mLightNr = aLightNr;
	mPos = new float[4];
	if(false == glIsEnabled(GL_LIGHTING)){
	  glEnable(GL_LIGHTING);
	}
	if(false == glIsEnabled(aLightNr)){
	  on();
	}
	
	
	LightNode::setParam(GL_AMBIENT, ambA, ambB, ambC, ambD);
  	LightNode::setParam(GL_DIFFUSE, diffA, diffB, diffC, diffD);
  	LightNode::setParam(GL_POSITION, posX, posY, posZ, posW);  	
}

//-------------------------------------------------------//
LightNode::LightNode(GLenum aLightNr){
  mLightNr = aLightNr;
  mPos = new float[4];
  glEnable(aLightNr);
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
  if(aParamType == GL_POSITION){
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
  //glLightf(mLightNr, GL_SPOT_CUTOFF, 30.0);			// Set light2 cutoff to define the lightangle
  //glLightf(mLightNr, GL_SPOT_EXPONENT, 5.0);		// Set light2 exponent to define the intensity of light in the spot	
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

