#include "nodes/materialnode.h"


//----------------------------------------------------------//
MaterialNode::MaterialNode(GLenum aFace):mFace(aFace){
}
//----------------------------------------------------------//
MaterialNode::MaterialNode(GLenum aFace, Material *aMaterial):
mFace(aFace){
  setParam(GL_AMBIENT, aMaterial->ambient);
  setParam(GL_DIFFUSE, aMaterial->diffuse);
  setParam(GL_SPECULAR, aMaterial->specular);
  setParam(GL_EMISSION, aMaterial->emission);
  setParam(GL_SHININESS, aMaterial->shininess);

}
//----------------------------------------------------------//
void MaterialNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//
MaterialNode::~MaterialNode(){
  std::map<GLenum, float*>::const_iterator vItr;
  for(vItr=mParams.begin(); vItr != mParams.end(); vItr++){
    delete[] (vItr->second);
  }
  mParams.clear();
}
//----------------------------------------------------------//
void MaterialNode::setParam(GLenum aParamName, float aV1, float aV2, float aV3, float aV4){
  float* vParams = new float[4];
  vParams[0] = aV1;
  vParams[1] = aV2;
  vParams[2] = aV3;
  vParams[3] = aV4;
  std::map<GLenum, float*>::iterator vRes = mParams.find(aParamName);
  if(vRes != mParams.end()){
    delete[] vRes->second;
  }
  mParams[aParamName] = vParams;
}
//----------------------------------------------------------//
void MaterialNode::setParam(GLenum aParamName, float* aValues3){
  assert(NULL != aValues3);
  setParam(aParamName, aValues3[0], aValues3[1], aValues3[2], 0.0f);
}
//----------------------------------------------------------//

