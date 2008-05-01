#include "nodes/shadownode.h"


//-------------------------------------------------------//
ShadowNode::ShadowNode(float* aLightPos, float* aNormal, float* aPointInPlane, float* aColor):
mNode(NULL), mLightPos(aLightPos), mNormal(aNormal), mPointInPlane(aPointInPlane), mColor(aColor)
{
  mLightPos = new float[3];
  mLightPos[0] = aLightPos[0];
  mLightPos[1] = aLightPos[1];
  mLightPos[2] = aLightPos[2];

  mNormal = new float[3];
  mNormal[0] = aNormal[0];
  mNormal[1] = aNormal[1];
  mNormal[2] = aNormal[2];

  mPointInPlane = new float[3];
  mPointInPlane[0] = aPointInPlane[0];
  mPointInPlane[1] = aPointInPlane[1];
  mPointInPlane[2] = aPointInPlane[2];

  mColor = new float[3];
  mColor[0] = aColor[0];
  mColor[1] = aColor[1];
  mColor[2] = aColor[2];
}
//-------------------------------------------------------//
ShadowNode::~ShadowNode(){
  if(mNode != 0){
    mNode->unref();
  }
  mNode = NULL;
  delete[] mLightPos;
  delete[] mNormal;
  delete[] mPointInPlane;
  delete[] mColor;
}
//----------------------------------------------------------//
void ShadowNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//
void ShadowNode::setNodeToShadow(AbstractNode* aNode){
  if(mNode != NULL){
    mNode->unref();
  }
  mNode = aNode; 
  mNode->ref();
}
//----------------------------------------------------------//
AbstractNode* ShadowNode::getNodeToShadow(){
  return mNode;
}
//----------------------------------------------------------//
void ShadowNode::draw(AbstractVisitor &aVisitor){
  if(NULL != mNode){
    float shadowMatrix[16];
    buildShadowMatrix(shadowMatrix, mLightPos, mNormal, mPointInPlane);

  //    glDisable(GL_DEPTH_TEST);							// Disable depth test to see the shadow also from below
    glDisable(GL_LIGHTING);								// Disable light effects
    glColor3fv(mColor);						// Shadow's color
	  glPolygonMode(GL_FRONT, GL_FILL);
    glPushMatrix();
      glMultMatrixf(shadowMatrix);
      mNode->accept(aVisitor);
    glPopMatrix();
	  glEnable(GL_DEPTH_TEST);							// Enable depth test to sea the shadow also from below
    glEnable(GL_LIGHTING);								// Enable light effects
	  glDisable(GL_BLEND);								// Disable blending
  }
}
//----------------------------------------------------------//
void ShadowNode::buildShadowMatrix(float* shadowMatrix, float* lightPos, float* normal, float* p){
    float d = normal[0]*lightPos[0] + normal[1]*lightPos[1] + normal[2]*lightPos[2];
	  float c = p[0]*normal[0] + p[1]*normal[1] + p[2]*normal[2] - d; 
	
    shadowMatrix[0]  = c + lightPos[0] * normal[0];	    // First row
    shadowMatrix[4]  =	   lightPos[0] * normal[1];
    shadowMatrix[8]  =	   lightPos[0] * normal[2];
    shadowMatrix[12] =	  -lightPos[0] * (c+d);
	
    shadowMatrix[1]  =	   lightPos[1] * normal[0];		// Second row
    shadowMatrix[5]  = c + lightPos[1] * normal[1];
    shadowMatrix[9]  =	   lightPos[1] * normal[2];
    shadowMatrix[13] =	  -lightPos[1] * (c+d);
	
    shadowMatrix[2]  =	   lightPos[2] * normal[0];		// Third row
    shadowMatrix[6]  =	   lightPos[2] * normal[1];
    shadowMatrix[10] = c + lightPos[2] * normal[2];
    shadowMatrix[14] =	  -lightPos[2] * (c+d);
	
    shadowMatrix[3]  = normal[0];		// Fourth row
    shadowMatrix[7]  = normal[1];
    shadowMatrix[11] = normal[2];
    shadowMatrix[15] = -d;
  	for (int i=0;i<16;i++) shadowMatrix[i] /= shadowMatrix[15];
}
//----------------------------------------------------------//

