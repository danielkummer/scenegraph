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
Visitor::Visitor():AbstractVisitor(), mStackIdx(0), mBlendInfoSet(false){
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
  //copy(aSphereNode.mModelMatrix);
  if(0<aSphereNode.mCollidable){
    mCollider.push_back(&aSphereNode);
    aSphereNode.mModelMatrix[12] = mCurrentMatrix[12];
    aSphereNode.mModelMatrix[13] = mCurrentMatrix[13];
    aSphereNode.mModelMatrix[14] = mCurrentMatrix[14];
    aSphereNode.ref();
  }
  gluQuadricNormals(aSphereNode.mQuadric, GLU_SMOOTH);
  gluQuadricTexture(aSphereNode.mQuadric, aSphereNode.mUseTexCoord);
//  glEnable(GL_CULL_FACE);

  if(mBlendInfoSet){
    //glCullFace(GL_FRONT);
    //gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);

    //glCullFace(GL_BACK);
    //gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);
    //glDisable(GL_BLEND);
    mCurBlendInfo.mGeomNode = &aSphereNode;
    aSphereNode.ref();
    mBlendInfos.push_back(mCurBlendInfo);
    mBlendInfoSet = false;
  }else{
    gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);
  }
//  glDisable(GL_TEXTURE_2D);
  checkError(1);
}
//----------------------------------------------------------//
void Visitor::visit(LineNode &aLineNode){
  if(0<aLineNode.mCollidable){
    mCollider.push_back(&aLineNode);
    aLineNode.mModelMatrix[12] = mCurrentMatrix[12];
    aLineNode.mModelMatrix[13] = mCurrentMatrix[13];
    aLineNode.mModelMatrix[14] = mCurrentMatrix[14];
    aLineNode.ref();
  }
  glDisable(GL_LIGHTING);
  glLineWidth(aLineNode.mWidth);
  glBegin(GL_LINES);
    glVertex3f(aLineNode.mVert1X, aLineNode.mVert1Y, aLineNode.mVert1Z);
    glVertex3f(aLineNode.mVert2X, aLineNode.mVert2Y, aLineNode.mVert2Z);
  glEnd();
  glEnable(GL_LIGHTING);
  checkError(2);
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
  checkError(3);
}
//0 4  8 12
//1 5  9 13
//2 6 10 14
//3 7 11 15
//----------------------------------------------------------//
void Visitor::visit(TranslationNode &aTranslationNode){
  glTranslatef(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
  translate(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
  checkError(4);
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
  checkError(5);
}
//----------------------------------------------------------//
void Visitor::visit(ScaleNode &aScaleNode){
  glScalef(aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
  scale(aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
  checkError(6);
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
  if(mBlendInfoSet){
    mCurBlendInfo.mMatNode = &aMaterialNode;
    aMaterialNode.ref();
  }else{
    std::map<GLenum, float*>::iterator vItr;
    for(vItr=aMaterialNode.mParams.begin(); vItr!= aMaterialNode.mParams.end(); vItr++){
      glMaterialfv(aMaterialNode.mFace, vItr->first, vItr->second);
    }
  }
  checkError(7);

}
//----------------------------------------------------------//
void Visitor::visit(ColorNode &aColorNode){
  if(mBlendInfoSet){
    //mCurBlendInfo.mColorNode = &aColorNode;
    //aColorNode.ref();
  }else{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);	
    glColor4f(aColorNode.mRed, aColorNode.mGreen, aColorNode.mBlue, aColorNode.mAlpha);
  }
}
//----------------------------------------------------------//
void Visitor::visit(TextureNode &aTexNode){
  // TODO: enable/disable texturemode?? save which mode
  glEnable(GL_TEXTURE_2D);
  glBindTexture(aTexNode.mTarget, aTexNode.mTexID);
  if(true == aTexNode.mBlending){
    mCurBlendInfo.mTextureNode = &aTexNode;
    aTexNode.ref();
//    copy(mCurBlendInfo.mModelView);
    mBlendInfoSet = true;
    copy(aTexNode.mModelMatrix);
    //glEnable(GL_BLEND);
    //glBlendFunc(aTexNode.mSFactor, aTexNode.mDFactor);
  }
  checkError(8);

}
//----------------------------------------------------------//
void Visitor::visit(ShadowNode &aShadow){
  aShadow.draw(*this);
  checkError(9);
}
//----------------------------------------------------------//
void Visitor::visit(StarsNode &aStarNode){
  glEnable(GL_COLOR_MATERIAL);
  checkError(101);
  //glColor3f(1, 1, 1);
  //float val1[4] = {1, 1, 1, 1};
  //glMaterialfv(GL_FRONT, GL_AMBIENT, val1);
  //float val2[4] = {1, 1, 1, 1};
  //glMaterialfv(GL_FRONT, GL_DIFFUSE, val2);
  //float val3[4] = {1, 1, 1, 1};
  //glMaterialfv(GL_FRONT, GL_SPECULAR, val3);
  //float val4[4] = {1, 1, 1, 1};
  //glMaterialfv(GL_FRONT, GL_EMISSION, val4);
  //float val5[4] = {1, 1, 1, 1};
  //glMaterialfv(GL_FRONT, GL_SHININESS, val5);

  checkError(102);
  for(unsigned i=0; i<aStarNode.mNumStars; i++){
    glPointSize(aStarNode.mSizes[i]);
    checkError(103);
    glBegin(GL_POINTS);
      float* vP = &(aStarNode.mVertices[3*i]);
      glVertex3fv( vP );
    glEnd();
    checkError(104);
  }
  glDisable(GL_COLOR_MATERIAL);
  checkError(10);
}
//----------------------------------------------------------//
void Visitor::visit(RingNode &aRingNode){
  float fNormalVec[3] = {0.0f, -1.0f, 0.0f};
  float** vertices = aRingNode.mVertices;
  int quadCount = aRingNode.mQuadCount;

  glEnable(GL_TEXTURE_2D);
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
  checkError(11);
}
//----------------------------------------------------------//
void Visitor::visit(Separator &aNode){
  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
  glPushAttrib(GL_ALL_ATTRIB_BITS);
}

void Visitor::postvisit(Separator &aNode){
  glPopClientAttrib();
  glPopAttrib();
//  glEnable(GL_COLOR_MATERIAL);
//  glColor4f(1, 1, 1, 1);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_TEXTURE_2D);
  //DefaultMaterial vDMat;
  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vDMat.ambient);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vDMat.diffuse);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, vDMat.emission);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, vDMat.shininess);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vDMat.specular);
  checkError(12);
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
    //glPushMatrix();
    //  glLoadIdentity();
    //  float* vM = aNode.mModelMatrix;
    //  glLoadMatrixf(vM);
    //  glRotatef(aNode.getYaw(),   0, 0, 1);//vM[0], vM[1], vM[2]);
    //  glRotatef(aNode.getRoll(),  1, 0, 0 );//vM[8], vM[9], vM[10]);
    //  glRotatef(aNode.getPitch(), 0, 1, 0);//vM[4], vM[5], vM[6]);
    //  glTranslatef(aNode.getX(), 
    //               aNode.getY(), 
    //               aNode.getZ());
    //  glGetFloatv(GL_MODELVIEW_MATRIX, &aNode.mModelMatrix[0]);
    //glPopMatrix();

    push();
      loadMatrix(aNode.mModelMatrix);
      rotate(aNode.getYaw(),   0, 0, 1);//vM[0], vM[1], vM[2]);
      rotate(aNode.getRoll(),  1, 0, 0 );//vM[8], vM[9], vM[10]);
      rotate(aNode.getPitch(), 0, 1, 0);//vM[4], vM[5], vM[6]);
      translate(aNode.getX(), aNode.getY(), aNode.getZ());
      copy(aNode.mModelMatrix);
    pop();

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
    //glPushMatrix();
    //  glLoadMatrixf(vT);

    //  glRotatef(aNode.getRoll(),  0, 0, 1);
    //  glRotatef(aNode.getPitch(), 1, 0, 0);
    //  glRotatef(aNode.getYaw(),   0, 1, 0);

    //  glGetFloatv(GL_MODELVIEW_MATRIX, vT);

    //glPopMatrix();
    push();
    loadMatrix(vT);
    rotate(aNode.getRoll(), 0, 0, 1);
    rotate(aNode.getPitch(), 1, 0, 0);
    rotate(aNode.getYaw(), 0, 1, 0);
    copy(vT);
    pop();

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
  mCurrentCam = &aNode;
  checkError(13);
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
    mCurrentCam = &aNode ;
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
  glDisable(GL_TEXTURE_2D);
  checkError(14);
}
//----------------------------------------------------------//
void Visitor::visit(Quad& aQuad){
  if(mBlendInfoSet){
    mCurBlendInfo.mGeomNode = &aQuad;
    aQuad.ref();
    mBlendInfos.push_back(mCurBlendInfo);
    mBlendInfoSet = false;
  }else{
    checkError(151);
    push();
    glPushMatrix();
    //glTranslatef(aQuad.mPos.x, aQuad.mPos.y, aQuad.mPos.z);
    //translate(aQuad.mPos.x, aQuad.mPos.y, aQuad.mPos.z);
    //glTranslatef(aQuad.mOffset.x, aQuad.mOffset.y, aQuad.mOffset.z);
    //translate(aQuad.mOffset.x, aQuad.mOffset.y, aQuad.mOffset.z);
    glMultMatrixf(aQuad.mModelMatrix);
    mult(aQuad.mModelMatrix);
    checkError(152);
    glBegin(GL_QUADS);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(aQuad.mP1.x, aQuad.mP1.y, aQuad.mP1.z);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(aQuad.mP2.x, aQuad.mP2.y, aQuad.mP2.z);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(aQuad.mP3.x, aQuad.mP3.y, aQuad.mP3.z);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(aQuad.mP4.x, aQuad.mP4.y, aQuad.mP4.z);
    glEnd();
    glPopMatrix();
    pop();
  }
  checkError(15);
}
//----------------------------------------------------------//
void Visitor::visit(Billboard& aNode){
  if(mBlendInfoSet){
    mCurBlendInfo.mGeomNode = &aNode;
    aNode.ref();
    mBlendInfos.push_back(mCurBlendInfo);
    mBlendInfoSet = false;
  }else{
//0 4  8 12
//1 5  9 13
//2 6 10 14
//3 7 11 15

    //SPoint3D vLook = SPoint3D(mCurrentCam->mTransform[12] - aNode.mModelMatrix[12],
    //                          mCurrentCam->mTransform[13] - aNode.mModelMatrix[13],
    //                          mCurrentCam->mTransform[14] - aNode.mModelMatrix[14]);
    SPoint3D vLook = SPoint3D(mCurrentCam->mTransform[12] - mCurrentMatrix[12],
                              mCurrentCam->mTransform[13] - mCurrentMatrix[13],
                              mCurrentCam->mTransform[14] - mCurrentMatrix[14]);
    // HACK: actually it should be in a fixed axis billboard
    SPoint3D vUp = SPoint3D(0, 1, 0);
    //SPoint3D vUp = SPoint3D(mCurrentCam->mTransform[4],
    //                        mCurrentCam->mTransform[5],
    //                        mCurrentCam->mTransform[6]);
    SPoint3D vXAxis = vUp.cross(vLook).normalize();
    SPoint3D vYAxis = vLook.cross(vXAxis).normalize();


    aNode.mModelMatrix[0] = vXAxis.x;
    aNode.mModelMatrix[1] = vXAxis.y;
    aNode.mModelMatrix[2] = vXAxis.z;

    aNode.mModelMatrix[4] = vYAxis.x;
    aNode.mModelMatrix[5] = vYAxis.y;
    aNode.mModelMatrix[6] = vYAxis.z;

    aNode.mModelMatrix [8] = vLook.x;
    aNode.mModelMatrix [9] = vLook.y;
    aNode.mModelMatrix[10] = vLook.z;
    Quad* vQNode = &((Quad)aNode);
    visit(*vQNode);

  }
  checkError(16);
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
  //glPushMatrix();
  //  glLoadIdentity();
  //  glRotatef(aDeg, aAxisX, aAxisY, aAxisZ);
  //  glGetFloatv(GL_MODELVIEW_MATRIX, vRotMat);
  //glPopMatrix();

// http://www.cprogramming.com/tutorial/3d/rotation.html
  
//tX2 + c  tXY + sZ  tXZ - sY  0
//tXY-sZ   tY2 + c   tYZ + sX  0
//tXY + sY tYZ - sX  tZ2 + c   0
//0        0         0         1

//Where c = cos (theta), s = sin (theta), t = 1-cos (theta), and <X,Y,Z> is the unit vector representing the arbitary axis

  float vRad = aDeg /180.0f * 3.14159265f;
  float c = cos(-vRad);
  float s = sin(-vRad);
  float t = 1 - c;
  vRotMat [0] = t * aAxisX * aAxisX + c;
  vRotMat [1] = t * aAxisX * aAxisY - s * aAxisZ;
  vRotMat [2] = t * aAxisX * aAxisY + s * aAxisY;
  vRotMat [3] = 0;

  vRotMat [4] = t * aAxisX * aAxisY + s * aAxisZ;;
  vRotMat [5] = t * aAxisY * aAxisY + c;
  vRotMat [6] = t * aAxisY * aAxisZ - s * aAxisX;
  vRotMat [7] = 0;

  vRotMat [8] = t * aAxisX * aAxisZ - s * aAxisY;
  vRotMat [9] = t * aAxisY * aAxisZ + s * aAxisX;
  vRotMat[10] = t * aAxisZ * aAxisZ + c;
  vRotMat[11] = 0;

  vRotMat[12] = 0;
  vRotMat[13] = 0;
  vRotMat[14] = 0;
  vRotMat[15] = 1;

  mult(vRotMat);
}
//----------------------------------------------------------//
void Visitor::mult(float* aMatrix){
//0 4  8 12
//1 5  9 13
//2 6 10 14
//3 7 11 15
  float* vNewMat = new float[16];
  vNewMat [0]= mCurrentMatrix[0]  * aMatrix[0] + 
               mCurrentMatrix[4]  * aMatrix[1] + 
               mCurrentMatrix[8]  * aMatrix[2];// + 
               //mCurrentMatrix[12] * aMatrix[3];
  vNewMat [4]= mCurrentMatrix[0]  * aMatrix[4] + 
               mCurrentMatrix[4]  * aMatrix[5] + 
               mCurrentMatrix[8]  * aMatrix[6];// + 
               //mCurrentMatrix[12] * aMatrix[7];
  vNewMat [8]= mCurrentMatrix[0]  * aMatrix[8] + 
               mCurrentMatrix[4]  * aMatrix[9] + 
               mCurrentMatrix[8]  * aMatrix[10];// + 
               //mCurrentMatrix[12] * aMatrix[11];
  vNewMat[12]= mCurrentMatrix[0]  * aMatrix[12] + 
               mCurrentMatrix[4]  * aMatrix[13] + 
               mCurrentMatrix[8]  * aMatrix[14] + 
               mCurrentMatrix[12];// * aMatrix[15];

  vNewMat [1]= mCurrentMatrix[1]  * aMatrix[0] + 
               mCurrentMatrix[5]  * aMatrix[1] + 
               mCurrentMatrix[9]  * aMatrix[2];// + 
               //mCurrentMatrix[13] * aMatrix[3];
  vNewMat [5]= mCurrentMatrix[1]  * aMatrix[4] + 
               mCurrentMatrix[5]  * aMatrix[5] + 
               mCurrentMatrix[9]  * aMatrix[6];// + 
               //mCurrentMatrix[13] * aMatrix[7];
  vNewMat [9]= mCurrentMatrix[1]  * aMatrix[8] + 
               mCurrentMatrix[5]  * aMatrix[9] + 
               mCurrentMatrix[9]  * aMatrix[10];// + 
               //mCurrentMatrix[13] * aMatrix[11];
  vNewMat[13]= mCurrentMatrix[1]  * aMatrix[12] + 
               mCurrentMatrix[5]  * aMatrix[13] + 
               mCurrentMatrix[9]  * aMatrix[14] + 
               mCurrentMatrix[13];// * aMatrix[15];

  vNewMat [2]= mCurrentMatrix[2]  * aMatrix[0] + 
               mCurrentMatrix[6]  * aMatrix[1] + 
               mCurrentMatrix[10] * aMatrix[2];// + 
               //mCurrentMatrix[14] * aMatrix[3];
  vNewMat [6]= mCurrentMatrix[2]  * aMatrix[4] + 
               mCurrentMatrix[6]  * aMatrix[5] + 
               mCurrentMatrix[10] * aMatrix[6];// + 
               //mCurrentMatrix[14] * aMatrix[7];
  vNewMat[10]= mCurrentMatrix[2]  * aMatrix[8] + 
               mCurrentMatrix[6]  * aMatrix[9] + 
               mCurrentMatrix[10] * aMatrix[10];// + 
               //mCurrentMatrix[14] * aMatrix[11];
  vNewMat[14]= mCurrentMatrix[2] * aMatrix[12] + 
               mCurrentMatrix[6]  * aMatrix[13] + 
               mCurrentMatrix[10] * aMatrix[14] + 
               mCurrentMatrix[14];// * aMatrix[15];
  vNewMat [3] = 0.0f;
  vNewMat [7] = 0.0f;
  vNewMat[11] = 0.0f;
  vNewMat[15] = 1.0f;
  delete[] mCurrentMatrix;
  mCurrentMatrix = vNewMat;
}
//----------------------------------------------------------//
void Visitor::translate(float aX, float aY, float aZ){
  mCurrentMatrix[12] += (aX * mCurrentMatrix[0] + aY * mCurrentMatrix[4] + aZ * mCurrentMatrix [8]);
  mCurrentMatrix[13] += (aX * mCurrentMatrix[1] + aY * mCurrentMatrix[5] + aZ * mCurrentMatrix [9]);
  mCurrentMatrix[14] += (aX * mCurrentMatrix[2] + aY * mCurrentMatrix[6] + aZ * mCurrentMatrix[10]);
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

void Visitor::drawBlended(){

  checkError(171);
  sort(mBlendInfos.begin(), mBlendInfos.end());
  mBlendInfoSet = false;
  // draw back first
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  checkError(172);
  for(unsigned i=0; i<mBlendInfos.size(); i++){
    SBlendInfo* vBI = &(mBlendInfos[i]);
    vBI->mMatNode->accept(*this);
  checkError(175);
    glBindTexture(vBI->mTextureNode->mTarget, vBI->mTextureNode->mTexID);
  checkError(1750);
    glBlendFunc(vBI->mTextureNode->mSFactor, vBI->mTextureNode->mDFactor);
  checkError(1751);
    glPushMatrix();
    push();
    glMultMatrixf(vBI->mTextureNode->mModelMatrix);
    mult(vBI->mTextureNode->mModelMatrix);
//    vBI->mColorNode->accept(*this);
    vBI->mGeomNode->accept(*this);
    glPopMatrix();
    pop();
  }
  checkError(173);
  glCullFace(GL_BACK);
  for(unsigned i=0; i<mBlendInfos.size(); i++){
    SBlendInfo* vBI = &(mBlendInfos[i]);
    vBI->mMatNode->accept(*this);
    glBindTexture(vBI->mTextureNode->mTarget, vBI->mTextureNode->mTexID);
    glBlendFunc(vBI->mTextureNode->mSFactor, vBI->mTextureNode->mDFactor);
    glPushMatrix();
    push();
    glMultMatrixf(vBI->mTextureNode->mModelMatrix);
    mult(vBI->mTextureNode->mModelMatrix);
    //vBI->mColorNode->accept(*this);
    vBI->mGeomNode->accept(*this);
    glPopMatrix();
    pop();
    vBI->mTextureNode->unref();
    vBI->mGeomNode->unref();
//    vBI->mColorNode->unref();
    vBI->mMatNode->unref();
  }
  checkError(174);
  glBlendFunc(GL_ONE, GL_ZERO);
  glDisable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  glDisable(GL_TEXTURE_2D);


  mBlendInfos.clear();
  checkError(17);
}
//----------------------------------------------------------//
void Visitor::apply(AbstractNode *aAbstractNode){
  AbstractVisitor::apply(aAbstractNode);
  checkCollisions();
  drawBlended();
}

//----------------------------------------------------------//
inline void Visitor::checkError(int aInt){
  int vErrNum = glGetError();
  if(0<vErrNum){
    printf("@ %i ERROR: %i %s\n", aInt, vErrNum, gluErrorString(vErrNum));
  }
}
//----------------------------------------------------------//
void Visitor::checkCollisions(){
  // only spheres
  for(unsigned i=0; i<mCollider.size(); i++){
    if(1 == mCollider[i]->mCollidable){
      
      for(unsigned j=i+1; j<mCollider.size(); j++){
        // only check collision if it is of other type
        if( 1 < mCollider[j]->mCollidable){
          // check distance
          float vdx = mCollider[i]->mModelMatrix[12] - mCollider[j]->mModelMatrix[12];
          float vdy = mCollider[i]->mModelMatrix[13] - mCollider[j]->mModelMatrix[13];
          float vdz = mCollider[i]->mModelMatrix[14] - mCollider[j]->mModelMatrix[14];
          float vLen = sqrt(vdx * vdx + vdy * vdy + vdz * vdz);
          float vR1 = (float)((SphereNode*)mCollider[i])->mRadius;
          float vR2;
          bool vColliding = false;
          if(2==mCollider[j]->mCollidable){
            vR2 = (float)((SphereNode*)mCollider[j])->mRadius;
            if(vLen < (vR1 + vR2)){
              // collision
              printf("Collision at %f %f %f \n", 
                      mCollider[i]->mModelMatrix[12] + vR1 * vdx, 
                      mCollider[i]->mModelMatrix[13] + vR1 * vdy, 
                      mCollider[i]->mModelMatrix[14] + vR1 * vdz);
              vColliding = true;
            }
          }else{
            vR2 = 10;
            if(vLen < (vR1)){
              // collision
              printf("Collision 2 at %f %f %f \n", 
                      mCollider[i]->mModelMatrix[12] + vR1 * vdx, 
                      mCollider[i]->mModelMatrix[13] + vR1 * vdy, 
                      mCollider[i]->mModelMatrix[14] + vR1 * vdz);
              vColliding = true;
            }
          }
          if(vColliding){
            // TODO: remove shot from scenegraph (how?)
            mCollider[j]->mCollidable = 0;

            // draw somthing at that place
            // TODO: mRoot is not good for viewports
            // TODO: memory leaks if currently in use while exit!!
            TransformSeparator* vT = new TransformSeparator();
            if(vLen==0) vLen = 1.0f;
            vT->add(new TranslationNode(mCollider[i]->mModelMatrix[12] - vR1 * vdx / vLen, 
                                        mCollider[i]->mModelMatrix[13] - vR1 * vdy / vLen, 
                                        mCollider[i]->mModelMatrix[14] - vR1 * vdz / vLen));
            vT->add(new ScalatorNode(0.1f, 0.1f, 0.1f, 2, 2, 2));
            vT->add(new TextureNode( TextureManager::getReference()->createTexture("Textures/latest_smooth2.bmp"), GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_TEXTURE_2D));
            vT->add(new MaterialNode(GL_FRONT, new TransDefaultMaterial()));
//            vT->add(new Billboard(1, 1));
            vT->add(new SphereNode(1));
            DestructorNode* vDestr = new DestructorNode(3, (GroupNode*)mRootNode);
            vDestr->add(vT);
            ((GroupNode*)mRootNode)->add(vDestr);
          }
        }
      } // for
    } // if
    mCollider[i]->unref();
  }
  mCollider.clear();
}


