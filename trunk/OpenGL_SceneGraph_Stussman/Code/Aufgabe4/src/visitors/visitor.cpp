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
Visitor::Visitor():AbstractVisitor(){
}
//----------------------------------------------------------//
Visitor::~Visitor(){
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
     aSpawn.fire();
     aSpawn.mFire = false;
  }
}

//----------------------------------------------------------//
void Visitor::visit(TranslationNode &aTranslationNode){
  glTranslatef(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
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
}
//----------------------------------------------------------//
void Visitor::visit(ScaleNode &aScaleNode){
  glScalef(aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
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
//  glEnable(GL_COLOR_MATERIAL);
//  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glEnable(GL_COLOR_MATERIAL);
  glColor3f(1, 1, 1);
//  glMaterialf(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 1);
  for(unsigned i=0; i<aStarNode.mNumStars; i++){
    glPointSize(aStarNode.mSizes[i]);
  glBegin(GL_POINTS);
    glVertex3fv(&aStarNode.mVertices[3*i]);
  glEnd();
  }
glDisable(GL_COLOR_MATERIAL);
//  glDisable(GL_COLOR_MATERIAL);
}
//----------------------------------------------------------//
void Visitor::visit(RingNode &aRingNode){
  float fNormalVec[3] = {0.0f, -1.0f, 0.0f};
  float** vertices = aRingNode.mVertices;
  int quadCount = aRingNode.mQuadCount;

//  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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
}

void Visitor::postvisit(TransformSeparator &aNode){
  glPopMatrix();
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
