#include "visitors/printvisitor.h"


//----------------------------------------------------------//
void PrintVisitor::visit(GroupNode &aGroupNode) {
  printIdent();
  printf("ID: %d GroupNode begin\n", aGroupNode.mID); 
  mIdent++;
}
//----------------------------------------------------------//
void PrintVisitor::postvisit(GroupNode &aGroupNode){
  mIdent--;
  printIdent();
  printf("ID: %d GroupNode end\n", aGroupNode.mID); 
}
//----------------------------------------------------------//
void PrintVisitor::visit(TransformSeparator &aTransformSeparatorNode){
  glMatrixStackPos++;
  printIdent();
  printf("ID: %d TransformSeparator begin glMatrixStack %d\n", aTransformSeparatorNode.mID, glMatrixStackPos); 
  mIdent++;
}
//----------------------------------------------------------//
void PrintVisitor::postvisit(TransformSeparator &aTransformSeparatorNode){
  mIdent--;
  glMatrixStackPos--;
  printIdent();
  printf("ID: %d TransformSeparator end glMatrixStack %d\n", aTransformSeparatorNode.mID, glMatrixStackPos); 
}
//----------------------------------------------------------//
void PrintVisitor::visit(SphereNode &aSphereNode){
  printIdent();
  printf("ID: %d SphereNode Radius: %.2f\n", aSphereNode.mID, aSphereNode.mRadius); 
}
//----------------------------------------------------------//
void PrintVisitor::visit(LineNode &aLineNode){
  printIdent();
  printf("ID: %d LineNode from: <%.2f, %.2f,%.2f>to <%.2f, %.2f, %.2f> width: %.2f\n", 
    aLineNode.mID,
    aLineNode.mVert1X,
    aLineNode.mVert1Y,
    aLineNode.mVert1Z,
    aLineNode.mVert2X,
    aLineNode.mVert2Y,
    aLineNode.mVert2Z,
    aLineNode.mWidth);
}
//----------------------------------------------------------//
void PrintVisitor::printIdent(){
  for(unsigned i=0; i<mIdent; i++){
    printf("  ");
  }
}
//----------------------------------------------------------//
void PrintVisitor::visit(TranslationNode &aTranslationNode){
  printIdent();
  printf("ID: %d TranslationNode Displacement: %.2f, %.2f, %.2f\n", 
          aTranslationNode.mID,
          aTranslationNode.mX,
          aTranslationNode.mY,
          aTranslationNode.mZ); 
}
//----------------------------------------------------------//
void PrintVisitor::visit(RotationNode &aRotationNode){
  printIdent();
  printf("ID: %d RotationNode Angle(degrees): %.2f Axis: %.2f, %.2f, %.2f\n", 
          aRotationNode.mID,
          aRotationNode.getAngle(),
          aRotationNode.mAxisX,
          aRotationNode.mAxisY,
          aRotationNode.mAxisZ); 
}
//----------------------------------------------------------//
void PrintVisitor::visit(RotorNode &aRotorNode){
  printIdent();
  printf("ID: %d RotorNode AngleVel: %.2f, Angle(degrees): %.2f Axis: %.2f, %.2f, %.2f\n", 
          aRotorNode.mID,
          aRotorNode.mAngleVel,
          aRotorNode.getAngle(),
          aRotorNode.mAxisX,
          aRotorNode.mAxisY,
          aRotorNode.mAxisZ); 
}
//----------------------------------------------------------//
void PrintVisitor::visit(ScaleNode &aScaleNode){
  printIdent();
  printf("ID: %d ScaleNode scaling: %.2f, %.2f, %.2f\n", aScaleNode.mID, aScaleNode.mScaleX, aScaleNode.mScaleY, aScaleNode.mScaleZ);
}
//----------------------------------------------------------//
void PrintVisitor::visit(LightNode &aLightNode){
  printIdent();
  printf("ID: %d LightNode\n", aLightNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(MaterialNode &aMaterialNode){
  printIdent();
  printf("ID: %d MaterialNode\n", aMaterialNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(ColorNode &aColorNode){
  printIdent();
  printf("ID: %d ColorNode\n", aColorNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(TextureNode &aTexNode){
  printIdent();
  printf("ID: %d TextureNode ID: %d\n", aTexNode.mID, aTexNode.mTexID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(ShadowNode &aShadowNode){
  printIdent();
  printf("ID: %d ShadowNode\n", aShadowNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(StarsNode &aStarsNode){
  printIdent();
  printf("ID: %d StarsNode min R: %.2f, delta R: %.2f, num: %d\n",
    aStarsNode.mID,
    aStarsNode.mRadiusMin,
    aStarsNode.mDeltaR,
    aStarsNode.mNumStars);
}
//----------------------------------------------------------//
void PrintVisitor::visit(RingNode &aRingNode){
  printIdent();
  printf("ID: %d RingNode minR: %.2f, maxR: %.2f, numQuads: %d\n",
        aRingNode.mID,
        aRingNode.mInnerRadius,
        aRingNode.mOuterRadius,
        aRingNode.mQuadCount);
}
//----------------------------------------------------------//
void PrintVisitor::visit(Separator &aNode){
  printIdent();
  printf("ID: %d Separator enter\n", aNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::postvisit(Separator &aNode){
  printIdent();
  printf("ID: %d Separator end\n", aNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(SwitchNode &aNode){
  printIdent();
  printf("ID: %d SwitchNode enter\n", aNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::postvisit(SwitchNode &aNode){
  printIdent();
  printf("ID: %d SwitchNode end\n", aNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(ToggleNode &aNode){
  printIdent();
  printf("ID: %d ToggleNode enter\n", aNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::postvisit(ToggleNode &aNode){
  printIdent();
  printf("ID: %d ToggleNode end\n", aNode.mID);
}
//----------------------------------------------------------//
void PrintVisitor::visit(AbstractNode &aNode) { }
void PrintVisitor::postvisit(AbstractNode &aNode){ }
