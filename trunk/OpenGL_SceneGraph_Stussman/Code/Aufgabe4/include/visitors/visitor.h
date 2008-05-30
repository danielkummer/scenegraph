#ifndef _H_VISITOR
#define _H_VISITOR

#include "nodes/allnodes.h"
#include "visitors/abstractvisitor.h"
#include <vector>
#include <algorithm> 




struct SBlendInfo{
  float mModelView[16];
  TextureNode* mTextureNode;
  AbstractNode* mGeomNode;
  ColorNode* mColorNode;
  MaterialNode* mMatNode;
  bool operator<(const SBlendInfo& other) const {
    return mModelView[14] < other.mModelView[14];
  } 
};



class Visitor:public AbstractVisitor{
public:
  Visitor();
  virtual ~Visitor();

  virtual void visit(SphereNode &aSphereNode);
  virtual void visit(LineNode &aLineNode );
  virtual void visit(TranslationNode &aTranslationNode);
  virtual void visit(RotationNode &aRotationNode);
  virtual void visit(ScaleNode &aScaleNode);
//  virtual void visit(RotorNode &aRotorNode);
//  virtual void visit(TranslatorNode &aTranslatorNode);
  virtual void visit(LightNode &aLightNode);
  virtual void visit(MaterialNode &aMaterialNode);
  virtual void visit(ColorNode &aColorNode);
  virtual void visit(TextureNode &aTexNode);
  virtual void visit(ShadowNode &aShadow);
  virtual void visit(StarsNode &aStarNode);
  virtual void visit(RingNode &aRingNode);
  virtual void visit(Separator &aNode);
  virtual void postvisit(Separator &aNode);
  virtual void visit(TransformSeparator &aNode);
  virtual void postvisit(TransformSeparator &aNode);
  virtual void visit(MoveNode &aNode);
  virtual void visit(CamNode &aNode);
  virtual void visit(CamFollowNode &aNode);
  virtual void visit(AbstractSpawn &aNode);
  
  virtual void visit(PolygonObjectNode &aPolygonObjectNode);

  void drawBlended();
  std::vector<SBlendInfo> mBlendInfos;

  virtual void apply(AbstractNode* aAbstractNode);


private:
  void loadIdentity();
  void rotate(float aDeg, float aAxisX, float aAxisY, float aAxisZ);
  void translate(float aX, float aY, float aZ);
  void scale(float aX, float aY, float aZ);
  void push();
  void pop();
  void mult(float* aMatrix);
  void copy(float* aToMatrix);
  void loadMatrix(float* aMatrix);
  
  float* mCurrentMatrix;
  float* mMatrixStack[32];
  unsigned mStackIdx;

  CamNode* mCurrentCam;
  SBlendInfo mCurBlendInfo;
  bool mBlendInfoSet;
};

#endif // _H_VISITOR


