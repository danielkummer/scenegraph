#include "visitors.h"

//-------------------------------------------------------//
void AbstractVisitor::apply(AbstractNode* aAbstractNode){
  mRootNode = aAbstractNode;
  aAbstractNode->accept(*this);
  mRootNode = NULL;
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void Visitor::visit(SphereNode &aSphereNode){
  gluQuadricTexture(aSphereNode.mQuadric, aSphereNode.mUseTexCoord);
  gluSphere(aSphereNode.mQuadric, aSphereNode.mRadius, aSphereNode.mSlices, aSphereNode.mStacks);
}
//-------------------------------------------------------//
void Visitor::visit(LineNode &aLineNode){
  glLineWidth(aLineNode.mWidth);
  glBegin(GL_LINES);
//    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(aLineNode.mVert1X, aLineNode.mVert1Y, aLineNode.mVert1Z);
    glVertex3f(aLineNode.mVert2X, aLineNode.mVert2Y, aLineNode.mVert2Z);
  glEnd();
}
//-------------------------------------------------------//
void Visitor::visit(TranslationNode &aTranslationNode){
  glTranslatef(aTranslationNode.mX, aTranslationNode.mY, aTranslationNode.mZ);
}
//-------------------------------------------------------//
void Visitor::visit(RotationNode &aRotationNode){
  glRotatef(aRotationNode.mGradAngle, 
            aRotationNode.mAxisX,
            aRotationNode.mAxisY,
            aRotationNode.mAxisZ);
}
//-------------------------------------------------------//
void Visitor::visit(ScaleNode &aScaleNode){
  glScalef(aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
}
//-------------------------------------------------------//
void Visitor::visit(RotorNode &aRotorNode){
  RotationNode vTmp = aRotorNode;
  Visitor::visit(vTmp);
}
//-------------------------------------------------------//
void Visitor::visit(LightNode &aLightNode){
  aLightNode.setPos();
}
//-------------------------------------------------------//
void Visitor::visit(MaterialNode &aMaterialNode){
  std::map<GLenum, float*>::iterator vItr;
  for(vItr=aMaterialNode.mParams.begin(); vItr!= aMaterialNode.mParams.end(); vItr++){
    glMaterialfv(aMaterialNode.mFace, vItr->first, vItr->second);
  }
}
//-------------------------------------------------------//
void Visitor::visit(ColorNode &aColorNode){
  glColor3f(aColorNode.mRed, aColorNode.mGreen, aColorNode.mBlue);
}
//-------------------------------------------------------//
void Visitor::visit(TextureNode &aTexNode){
  glBindTexture(aTexNode.mTarget, aTexNode.mTexID);
}
//-------------------------------------------------------//
void Visitor::visit(ShadowNode &aShadow){
  aShadow.draw(*this);
}
//-------------------------------------------------------//
inline float randf(){
  return float(rand()/(float)RAND_MAX);
}
//-------------------------------------------------------//
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
//-------------------------------------------------------//
void Visitor::visit(RingNode &aRingNode){
  float fNormalVec[3] = {0.0f, 1.0f, 0.0f};
  float** vertices = aRingNode.mVertices;
  int quadCount = aRingNode.mQuadCount;

  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

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
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void DestructorVisitor::postvisit(GroupNode &aGroupNode){
  aGroupNode.clear();
}
//-------------------------------------------------------//
void DestructorVisitor::postvisit(TransformSeparator &aTransformSep){
  aTransformSep.clear();
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void PrintVisitor::visit(GroupNode &aGroupNode) {
  printIdent();
  printf("%p GroupNode begin\n", &aGroupNode); 
  mIdent++;
}
//-------------------------------------------------------//
void PrintVisitor::postvisit(GroupNode &aGroupNode){
  mIdent--;
  printIdent();
  printf("%p GroupNode end\n", &aGroupNode); 
}
//-------------------------------------------------------//
void PrintVisitor::visit(TransformSeparator &aTransformSeparatorNode){
  glMatrixStackPos++;
  printIdent();
  printf("%p TransformSeparator begin glMatrixStack %d\n", &aTransformSeparatorNode, glMatrixStackPos); 
  mIdent++;
}

//-------------------------------------------------------//
void PrintVisitor::postvisit(TransformSeparator &aTransformSeparatorNode){
  mIdent--;
  glMatrixStackPos--;
  printIdent();
  printf("%p TransformSeparator end glMatrixStack %d\n", &aTransformSeparatorNode, glMatrixStackPos); 
}
//-------------------------------------------------------//
void PrintVisitor::visit(SphereNode &aSphereNode){
  printIdent();
  printf("%p SphereNode Radius: %.2f\n", &aSphereNode, aSphereNode.mRadius); 
}
//-------------------------------------------------------//
void PrintVisitor::visit(LineNode &aLineNode){
  printIdent();
  printf("%p LineNode from: <%.2f, %.2f,%.2f>to <%.2f, %.2f, %.2f> width: %.2f\n", 
    &aLineNode,
    aLineNode.mVert1X,
    aLineNode.mVert1Y,
    aLineNode.mVert1Z,
    aLineNode.mVert2X,
    aLineNode.mVert2Y,
    aLineNode.mVert2Z,
    aLineNode.mWidth);
}
//-------------------------------------------------------//
void PrintVisitor::printIdent(){
  for(unsigned i=0; i<mIdent; i++){
    printf("  ");
  }
}
//-------------------------------------------------------//
void PrintVisitor::visit(TranslationNode &aTranslationNode){
  printIdent();
  printf("%p TranslationNode Displacement: %.2f, %.2f, %.2f\n", 
          &aTranslationNode,
          aTranslationNode.mX,
          aTranslationNode.mY,
          aTranslationNode.mZ); 
}
//-------------------------------------------------------//
void PrintVisitor::visit(RotationNode &aRotationNode){
  printIdent();
  printf("%p RotationNode Angle(degrees): %.2f Axis: %.2f, %.2f, %.2f\n", 
          &aRotationNode,
          aRotationNode.getAngle(),
          aRotationNode.mAxisX,
          aRotationNode.mAxisY,
          aRotationNode.mAxisZ); 
}
//-------------------------------------------------------//
void PrintVisitor::visit(RotorNode &aRotorNode){
  printIdent();
  printf("%p RotorNode AngleVel: %.2f, Angle(degrees): %.2f Axis: %.2f, %.2f, %.2f\n", 
          &aRotorNode,
          aRotorNode.mAngleVel,
          aRotorNode.getAngle(),
          aRotorNode.mAxisX,
          aRotorNode.mAxisY,
          aRotorNode.mAxisZ); 
}
//-------------------------------------------------------//
void PrintVisitor::visit(ScaleNode &aScaleNode){
  printIdent();
  printf("%p ScaleNode scaling: %.2f, %.2f, %.2f\n", &aScaleNode, aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
}
//-------------------------------------------------------//
void PrintVisitor::visit(LightNode &aLightNode){
  printIdent();
  printf("%p LightNode\n", &aLightNode);
}
//-------------------------------------------------------//
void PrintVisitor::visit(MaterialNode &aMaterialNode){
  printIdent();
  printf("%p MaterialNode\n", &aMaterialNode);
}
//-------------------------------------------------------//
void PrintVisitor::visit(ColorNode &aColorNode){
  printIdent();
  printf("%p ColorNode\n", &aColorNode);
}
//-------------------------------------------------------//
void PrintVisitor::visit(TextureNode &aTexNode){
  printIdent();
  printf("%p TextureNode ID: %d\n", &aTexNode, aTexNode.mTexID);
}
//-------------------------------------------------------//
void PrintVisitor::visit(ShadowNode &aShadow){
  printIdent();
  printf("%p ShadowNode\n", &aShadow);
}
//-------------------------------------------------------//
void PrintVisitor::visit(StarsNode &aStarsNode){
  printIdent();
  printf("%p StarsNode min R: %.2f, delta R: %.2f, num: %d\n",
    &aStarsNode,
    aStarsNode.mRadiusMin,
    aStarsNode.mDeltaR,
    aStarsNode.mNumStars);
}
//-------------------------------------------------------//
void PrintVisitor::visit(RingNode &aRingNode){
  printIdent();
  printf("%p RingNode minR: %.2f, maxR: %.2f, numQuads: %d",
        &aRingNode,
        aRingNode.mInnerRadius,
        aRingNode.mOuterRadius,
        aRingNode.mQuadCount);
}

//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void EventVisitor::apply(AbstractNode* aAbstractNode, SDL_Event &aEvent){
  mEvent = aEvent;
  AbstractVisitor::apply(aAbstractNode);
}
//-------------------------------------------------------//
/*void EventVisitor::visit(AbstractNode &aAbstractNode){
  switch(aAbstractNode.mBeh){
    case eBeh1:{
      switch(mEvent.type){
        case SDL_KEYDOWN:{
          switch(mEvent.key.keysym.sym){
            case SDLK_F1:{
              // code 
            }
            break;
            case SDLK_F2:{
              // code 
            }
            break;

          }
        }
      }
    }
    break;
  }
}
*/
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//




