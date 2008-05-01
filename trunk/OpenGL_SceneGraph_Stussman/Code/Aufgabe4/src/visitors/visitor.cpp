#include "visitors/visitor.h"


//----------------------------------------------------------//
Visitor::Visitor():AbstractVisitor(){
}
//----------------------------------------------------------//
Visitor::~Visitor(){
}
//----------------------------------------------------------//
void Visitor::visit(SphereNode &aSphereNode){
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
//    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(aLineNode.mVert1X, aLineNode.mVert1Y, aLineNode.mVert1Z);
    glVertex3f(aLineNode.mVert2X, aLineNode.mVert2Y, aLineNode.mVert2Z);
  glEnd();
}
//----------------------------------------------------------//
void Visitor::visit(TranslationNode &aTranslationNode){
  glTranslatef(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
}
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
void Visitor::visit(RotorNode &aRotorNode){
  RotationNode vTmp = aRotorNode;
  Visitor::visit(vTmp);
}
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
  glColor4f(aColorNode.mRed, aColorNode.mGreen, aColorNode.mBlue, aColorNode.mAlpha);
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
  glColor3f(1, 1, 1);
//  glMaterialf(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 1);
  glPointSize(1.5);
  glBegin(GL_POINTS);
  for(unsigned i=0; i<aStarNode.mNumStars; i++){
      glVertex3fv(&aStarNode.mVertices[3*i]);
  }
  glEnd();
//  glDisable(GL_COLOR_MATERIAL);
}
//----------------------------------------------------------//
void Visitor::visit(RingNode &aRingNode){
  float fNormalVec[3] = {0.0f, 1.0f, 0.0f};
  float** vertices = aRingNode.mVertices;
  int quadCount = aRingNode.mQuadCount;

//  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glDisable(GL_CULL_FACE);
  glColor4f(1, 1, 1, 1);
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
//  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

}
//----------------------------------------------------------//
void Visitor::visit(Separator &aNode){
//  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

}

void Visitor::postvisit(Separator &aNode){
//  glPopClientAttrib();
  glColor4f(1, 1, 1, 1);
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

