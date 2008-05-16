#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h>

#include "visitors/visitor.h"

//----------------------------------------------------------//
Visitor::Visitor():AbstractVisitor(), mStackIdx(0){
  mCurrentMatrix = new float[16];
  loadIdentity();
  for(unsigned i=0; i<32; i++){
    mMatrixStack[i] = NULL;
  }

}
//----------------------------------------------------------//
Visitor::~Visitor(){
  //for(unsigned i=0; i<32; i++){
  //  delete[] mMatrixStack[i];
  //}
  //delete[] mMatrixStack;
  delete[] mCurrentMatrix;
}
//----------------------------------------------------------//
void Visitor::visit(SphereNode &aSphereNode){
//  glGetFloatv(GL_MODELVIEW_MATRIX, aSphereNode.mModelMatrix);
  gluQuadricNormals(aSphereNode.mQuadric, GLU_SMOOTH);
  gluQuadricTexture(aSphereNode.mQuadric, aSphereNode.mUseTexCoord);
  glEnable(GL_CULL_FACE);

  if(glIsEnabled(GL_BLEND)){
    glCullFace(GL_FRONT);
    gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);

    glCullFace(GL_BACK);
    gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);
    glDisable(GL_BLEND);
  }else{
    gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);
  }
  copy(aSphereNode.mModelMatrix);
}
//----------------------------------------------------------//
void Visitor::visit(LineNode &aLineNode){
  glLineWidth(aLineNode.mWidth);
  glBegin(GL_LINES);
    glVertex3f(aLineNode.mVert1X, aLineNode.mVert1Y, aLineNode.mVert1Z);
    glVertex3f(aLineNode.mVert2X, aLineNode.mVert2Y, aLineNode.mVert2Z);
  glEnd();
}
//----------------------------------------------------------//
void Visitor::visit(AbstractSpawn &aSpawn){
  if(aSpawn.mFire){
    aSpawn.fire(mCurrentMatrix[12], 
                mCurrentMatrix[13], 
                mCurrentMatrix[14], 
                mCurrentMatrix[0], 
                mCurrentMatrix[1], 
                mCurrentMatrix[2]);
     aSpawn.mFire = false;
  }
}
//0 4  8 12
//1 5  9 13
//2 6 10 14
//3 7 11 15
//----------------------------------------------------------//
void Visitor::visit(TranslationNode &aTranslationNode){
  glTranslatef(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
  translate(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
}
//----------------------------------------------------------//
//void Visitor::visit(TranslatorNode &aTranslatorNode){
//  TranslationNode vTmp = aTranslatorNode;
//  Visitor::visit(vTmp);
//}
//----------------------------------------------------------//
void Visitor::visit(RotationNode &aRotationNode){
  glRotatef(aRotationNode.mGradAngle, 
            aRotationNode.mAxisX,
            aRotationNode.mAxisY,
            aRotationNode.mAxisZ);
  rotate(aRotationNode.mGradAngle, 
         aRotationNode.mAxisX,
         aRotationNode.mAxisY,
         aRotationNode.mAxisZ);
}
//----------------------------------------------------------//
void Visitor::visit(ScaleNode &aScaleNode){
  glScalef(aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
  scale(aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
}
//----------------------------------------------------------//
//void Visitor::visit(RotorNode &aRotorNode){
//  RotationNode vTmp = aRotorNode;
//  Visitor::visit(vTmp);
//}
//----------------------------------------------------------//
void Visitor::visit(LightNode &aLightNode){
  aLightNode.setPos();
}
//----------------------------------------------------------//
void Visitor::visit(MaterialNode &aMaterialNode){
  std::map<GLenum, float*>::iterator vItr;
  for(vItr=aMaterialNode.mParams.begin(); vItr!= aMaterialNode.mParams.end(); vItr++){
    glMaterialfv(aMaterialNode.mFace, vItr->first, vItr->second);
  }
}
//----------------------------------------------------------//
void Visitor::visit(ColorNode &aColorNode){
  glEnable(GL_COLOR_MATERIAL);	
  glColor4f(aColorNode.mRed, aColorNode.mGreen, aColorNode.mBlue, aColorNode.mAlpha);
  glDisable(GL_COLOR_MATERIAL);
}
//----------------------------------------------------------//
void Visitor::visit(TextureNode &aTexNode){
  // TODO: enable/disable texturemode??
  glBindTexture(aTexNode.mTarget, aTexNode.mTexID);
  if(true == aTexNode.mBlending){
    glEnable(GL_BLEND);
    glBlendFunc(aTexNode.mSFactor, aTexNode.mDFactor);
  }
}
//----------------------------------------------------------//
void Visitor::visit(ShadowNode &aShadow){
  aShadow.draw(*this);
}
//----------------------------------------------------------//
void Visitor::visit(StarsNode &aStarNode){
  glEnable(GL_COLOR_MATERIAL);
  glColor3f(1, 1, 1);
  for(unsigned i=0; i<aStarNode.mNumStars; i++){
    glPointSize(aStarNode.mSizes[i]);
    glBegin(GL_POINTS);
      glVertex3fv(&aStarNode.mVertices[3*i]);
    glEnd();
  }
  glDisable(GL_COLOR_MATERIAL);
}
//----------------------------------------------------------//
void Visitor::visit(RingNode &aRingNode){
  float fNormalVec[3] = {0.0f, -1.0f, 0.0f};
  float** vertices = aRingNode.mVertices;
  int quadCount = aRingNode.mQuadCount;

  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);  
  glDisable(GL_CULL_FACE);
  glBegin(GL_QUADS);
    glNormal3fv(fNormalVec);

    //iterate over all quads but the last one
    for(int i = 0; i < quadCount -1; i++) {           
      glTexCoord2f(0.0f, 1.0f);           
      glVertex3fv(vertices[i]);

      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(vertices[i+quadCount]);

      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(vertices[i+quadCount + 1]);

      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(vertices[i + 1]);
    }
    //last vertex
    glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(vertices[quadCount - 1]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vertices[2 * quadCount - 1]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vertices[quadCount]);
    glTexCoord2f(1.0f, 1.0f);       
    glVertex3fv(vertices[0]);    
  glEnd();   
  glEnable(GL_CULL_FACE);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

}
//----------------------------------------------------------//
void Visitor::visit(Separator &aNode){
//  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

}

void Visitor::postvisit(Separator &aNode){
//  glPopClientAttrib();
  //glColor4f(1, 1, 1, 1);
  DefaultMaterial vDMat;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vDMat.ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vDMat.diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, vDMat.emission);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, vDMat.shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vDMat.specular);
}
//----------------------------------------------------------//
void Visitor::visit(TransformSeparator &aNode){
  glPushMatrix();
  push();
}

void Visitor::postvisit(TransformSeparator &aNode){
  glPopMatrix();
  pop();
}
//----------------------------------------------------------//
void Visitor::visit(MoveNode &aNode){
  if(aNode.getChanged()){
    // construct movement
    glPushMatrix();
      glLoadIdentity();
      float* vM = aNode.mModelMatrix;
      glLoadMatrixf(vM);
      glRotatef(aNode.getYaw(),   0, 0, 1);//vM[0], vM[1], vM[2]);
      glRotatef(aNode.getRoll(),  1, 0, 0 );//vM[8], vM[9], vM[10]);
      glRotatef(aNode.getPitch(), 0, 1, 0);//vM[4], vM[5], vM[6]);
      glTranslatef(aNode.getX(), 
                   aNode.getY(), 
                   aNode.getZ());
      glGetFloatv(GL_MODELVIEW_MATRIX, &aNode.mModelMatrix[0]);
    glPopMatrix();

    // reset delta values
    aNode.reset();
  }
  // apply transformation matrix
  glMultMatrixf(&aNode.mModelMatrix[0]);
  mult(aNode.mModelMatrix);
}
//----------------------------------------------------------//
void Visitor::visit(CamNode &aNode){
  glLoadIdentity();
  float* vT = aNode.mTransform;
  if(aNode.getChanged()){
    // construct movement
    glPushMatrix();
      glLoadMatrixf(vT);

      glRotatef(aNode.getRoll(),  0, 0, 1);
      glRotatef(aNode.getPitch(), 1, 0, 0);
      glRotatef(aNode.getYaw(),   0, 1, 0);

      glGetFloatv(GL_MODELVIEW_MATRIX, vT);

    glPopMatrix();
    vT[12] += (aNode.getX() * vT[0] + aNode.getY() * vT[4] + aNode.getZ() * vT[8]);
    vT[13] += (aNode.getX() * vT[1] + aNode.getY() * vT[5] + aNode.getZ() * vT[9]);
    vT[14] += (aNode.getX() * vT[2] + aNode.getY() * vT[6] + aNode.getZ() * vT[10]);


    // reset delta values
    aNode.reset();
  }
  // construct transformation matrix
  // set up inverse matrix (?) see  http://www.flipcode.com/archives/OpenGL_Camera.shtml
  float* vM = aNode.mModelMatrix;

  vM[0] = vT[0];
  vM[1] = vT[4];
  vM[2] = vT[8];
  vM[3] = 0;

  vM[4] = vT[1];
  vM[5] = vT[5];
  vM[6] = vT[9];
  vM[7] = 0;

  vM[8]  = vT[2];
  vM[9]  = vT[6];
  vM[10] = vT[10];
  vM[11] = 0;

  vM[12] = -(vT[0]*vT[12] +
             vT[1]*vT[13] +
						 vT[2]*vT[14]);
  vM[13] = -(vT[4]*vT[12] +
             vT[5]*vT[13] +
						 vT[6]*vT[14]);
  vM[14] = -(vT[8]*vT[12] +
             vT[9]*vT[13] +
						 vT[10]*vT[14]);
  vM[15] = 1.0f;

  // apply transformation matrix
  glLoadMatrixf(vM);
//  loadMatrix(vM);
}
//----------------------------------------------------------//
void Visitor::visit(CamFollowNode &aNode) {
	
	for(int i=0; i < 16; i++) {
		aNode.mTransform[i] = aNode.mGlueNode->mModelMatrix[i];
	}
	
	//aNode.mTransform = aNode.mGlueNode.mModelMatrix;	
	
	float* vT = aNode.mTransform;
	float* vM = aNode.mModelMatrix;

  	vM[0] = vT[0];
  	vM[1] = vT[4];
  	vM[2] = vT[8];
  	vM[3] = 0;
	
  	vM[4] = vT[1];
  	vM[5] = vT[5];
  	vM[6] = vT[9];
  	vM[7] = 0;

	vM[8]  = vT[2];
  	vM[9]  = vT[6];
  	vM[10] = vT[10];
  	vM[11] = 0;

 	vM[12] = -(vT[0]*vT[12] +
             vT[1]*vT[13] +
						 vT[2]*vT[14]);
  	vM[13] = -(vT[4]*vT[12] +
             vT[5]*vT[13] +
						 vT[6]*vT[14]);
  	vM[14] = -(vT[8]*vT[12] +
             vT[9]*vT[13] +
						 vT[10]*vT[14]);
  	vM[15] = 1.0f;

  	// apply transformation matrix
    glTranslatef(0, -1, -3);
    glRotatef(90, 0, 1, 0);
//  	glLoadMatrixf(vM);
    glMultMatrixf(vM);
}
//----------------------------------------------------------//

void Visitor::visit(PolygonObjectNode &aPolygonObjectNode){
	for(int ig=0; ig < aPolygonObjectNode.groupcount; ig++)	{						// contains material definitions, textures 																						// and of course the triangles)
		if(aPolygonObjectNode.groups[ig].textureName != 0)	{						// if the material has a texture (texureName contains not only 0)
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, aPolygonObjectNode.groups[ig].textureID );	

		}							
		// Set material values for group[ig].material
			
		glDisable(GL_COLOR_MATERIAL);
		
 		glMaterialfv(GL_FRONT, GL_AMBIENT, aPolygonObjectNode.groups[ig].material.matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, aPolygonObjectNode.groups[ig].material.matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, aPolygonObjectNode.groups[ig].material.matSpecular);
		float shine[1] = {aPolygonObjectNode.groups[ig].material.matShininess};
		glMaterialfv(GL_FRONT, GL_SHININESS, shine);
		
		// draw triangles	
		for(int it=0; it < aPolygonObjectNode.groups[ig].size; it++)	{				// for each triangle of this group 
			glBegin ( GL_TRIANGLES );							// tell OpenGL to draw triangles using the following vertices
				glNormal3f(aPolygonObjectNode.groups[ig].triangle[it].normal1.x, aPolygonObjectNode.groups[ig].triangle[it].normal1.y, aPolygonObjectNode.groups[ig].triangle[it].normal1.z);
				glTexCoord2f(aPolygonObjectNode.groups[ig].triangle[it].tCoord1.x, aPolygonObjectNode.groups[ig].triangle[it].tCoord1.y);
				glVertex3f(aPolygonObjectNode.groups[ig].triangle[it].vertex1.x, aPolygonObjectNode.groups[ig].triangle[it].vertex1.y, aPolygonObjectNode.groups[ig].triangle[it].vertex1.z);
				
				glNormal3f(aPolygonObjectNode.groups[ig].triangle[it].normal2.x, aPolygonObjectNode.groups[ig].triangle[it].normal2.y, aPolygonObjectNode.groups[ig].triangle[it].normal2.z);
				glTexCoord2f(aPolygonObjectNode.groups[ig].triangle[it].tCoord2.x, aPolygonObjectNode.groups[ig].triangle[it].tCoord2.y);
				glVertex3f(aPolygonObjectNode.groups[ig].triangle[it].vertex2.x, aPolygonObjectNode.groups[ig].triangle[it].vertex2.y, aPolygonObjectNode.groups[ig].triangle[it].vertex2.z);
				
				glNormal3f(aPolygonObjectNode.groups[ig].triangle[it].normal3.x, aPolygonObjectNode.groups[ig].triangle[it].normal3.y, aPolygonObjectNode.groups[ig].triangle[it].normal3.z);
				glTexCoord2f(aPolygonObjectNode.groups[ig].triangle[it].tCoord3.x, aPolygonObjectNode.groups[ig].triangle[it].tCoord3.y);
				glVertex3f(aPolygonObjectNode.groups[ig].triangle[it].vertex3.x, aPolygonObjectNode.groups[ig].triangle[it].vertex3.y, aPolygonObjectNode.groups[ig].triangle[it].vertex3.z);				
			glEnd();											// end drawing triangles
		}
	}
}
//----------------------------------------------------------//
void Visitor::loadIdentity(){
  for(unsigned i=0; i<16; i++){
    mCurrentMatrix[i] = 0.0f;
  }
  mCurrentMatrix[0]  = 1.0f;
  mCurrentMatrix[5]  = 1.0f;
  mCurrentMatrix[10] = 1.0f;
  mCurrentMatrix[15] = 1.0f;
}


//----------------------------------------------------------//
void Visitor::rotate(float aDeg, float aAxisX, float aAxisY, float aAxisZ){
  float vRotMat[16];
  glPushMatrix();
    glLoadIdentity();
    glRotatef(aDeg, aAxisX, aAxisY, aAxisZ);
    glGetFloatv(GL_MODELVIEW_MATRIX, vRotMat);
  glPopMatrix();

  mult(vRotMat);
}
//----------------------------------------------------------//
void Visitor::mult(float* aMatrix){
//0 4  8 12
//1 5  9 13
//2 6 10 14
//3 7 11 15
  float vTemp[16];
  copy(vTemp);
  mCurrentMatrix[0] = vTemp[0]  * aMatrix[0] + 
                      vTemp[4]  * aMatrix[1] + 
                      vTemp[8]  * aMatrix[2] + 
                      vTemp[12] * aMatrix[3];
  mCurrentMatrix[4] = vTemp[0]  * aMatrix[4] + 
                      vTemp[4]  * aMatrix[5] + 
                      vTemp[8]  * aMatrix[6] + 
                      vTemp[12] * aMatrix[7];
  mCurrentMatrix[8] = vTemp[0]  * aMatrix[8] + 
                      vTemp[4]  * aMatrix[9] + 
                      vTemp[8]  * aMatrix[10] + 
                      vTemp[12] * aMatrix[11];
  mCurrentMatrix[12]= vTemp[0]  * aMatrix[12] + 
                      vTemp[4]  * aMatrix[13] + 
                      vTemp[8]  * aMatrix[14] + 
                      vTemp[12] * aMatrix[15];

  mCurrentMatrix[1] = vTemp[1]  * aMatrix[0] + 
                      vTemp[5]  * aMatrix[1] + 
                      vTemp[9]  * aMatrix[2] + 
                      vTemp[13] * aMatrix[3];
  mCurrentMatrix[5] = vTemp[1]  * aMatrix[4] + 
                      vTemp[5]  * aMatrix[5] + 
                      vTemp[9]  * aMatrix[6] + 
                      vTemp[13] * aMatrix[7];
  mCurrentMatrix[9] = vTemp[1]  * aMatrix[8] + 
                      vTemp[5]  * aMatrix[9] + 
                      vTemp[9]  * aMatrix[10] + 
                      vTemp[13] * aMatrix[11];
  mCurrentMatrix[13]= vTemp[1]  * aMatrix[12] + 
                      vTemp[5]  * aMatrix[13] + 
                      vTemp[9]  * aMatrix[14] + 
                      vTemp[13] * aMatrix[15];

  mCurrentMatrix[2] = vTemp[2]  * aMatrix[0] + 
                      vTemp[6]  * aMatrix[1] + 
                      vTemp[10] * aMatrix[2] + 
                      vTemp[14] * aMatrix[3];
  mCurrentMatrix[6] = vTemp[2]  * aMatrix[4] + 
                      vTemp[6]  * aMatrix[5] + 
                      vTemp[10] * aMatrix[6] + 
                      vTemp[14] * aMatrix[7];
  mCurrentMatrix[10]= vTemp[2]  * aMatrix[8] + 
                      vTemp[6]  * aMatrix[9] + 
                      vTemp[10] * aMatrix[10] + 
                      vTemp[14] * aMatrix[11];
  mCurrentMatrix[14]= vTemp[2] * aMatrix[12] + 
                      vTemp[6]  * aMatrix[13] + 
                      vTemp[10] * aMatrix[14] + 
                      vTemp[14] * aMatrix[15];
  mCurrentMatrix[3] = 0.0f;
  mCurrentMatrix[7] = 0.0f;
  mCurrentMatrix[11] = 0.0f;
  mCurrentMatrix[15] = 1.0f;
}
//----------------------------------------------------------//
void Visitor::translate(float aX, float aY, float aZ){
  mCurrentMatrix[12] += aX;
  mCurrentMatrix[13] += aY;
  mCurrentMatrix[14] += aZ;
}
//----------------------------------------------------------//
void Visitor::scale(float aX, float aY, float aZ){
  mCurrentMatrix[0] *= aX;
  mCurrentMatrix[5] *= aY;
  mCurrentMatrix[10] *= aZ;
}
//----------------------------------------------------------//
void Visitor::push(){
  assert(mStackIdx < 32);
  mMatrixStack[mStackIdx] = mCurrentMatrix;
  mCurrentMatrix = new float[16];
  for(unsigned i=0; i<16; i++){
    mCurrentMatrix[i] = mMatrixStack[mStackIdx][i];
  }
  mStackIdx++;
}
//----------------------------------------------------------//
void Visitor::pop(){
  delete[] mCurrentMatrix;
  mStackIdx--;
  assert(mStackIdx >= 0);

  mCurrentMatrix = mMatrixStack[mStackIdx];
}
//----------------------------------------------------------//
void Visitor::copy(float *aToMatrix){
  for(unsigned i=0; i<16; i++){
    aToMatrix[i] = mCurrentMatrix[i];
  }
}
//----------------------------------------------------------//
void Visitor::loadMatrix(float *aMatrix){
  for(unsigned i=0; i<16; i++){
    mCurrentMatrix[i] = aMatrix[i];
  }
}
//----------------------------------------------------------//

