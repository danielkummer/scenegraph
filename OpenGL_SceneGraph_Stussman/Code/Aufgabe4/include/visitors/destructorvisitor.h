#ifndef _H_DESTRUCTORVISITOR
#define _H_DESTRUCTORVISITOR

#include "visitors/abstractvisitor.h"
#include "nodes/allnodes.h"

class DestructorVisitor:public AbstractVisitor{
public:
  DestructorVisitor(): AbstractVisitor() { }
  virtual ~DestructorVisitor() { }
  virtual void postvisit(GroupNode &aGroupNode);
  virtual void postvisit(TransformSeparator &aTransformSep);
  virtual void visit(TextureNode &aNode);
  };
//-------------------------------------------------------//
class PrintVisitor:public AbstractVisitor{
public:
  PrintVisitor(): AbstractVisitor(), mIdent(0), glMatrixStackPos(0) { }
  virtual ~PrintVisitor() { }
  virtual void visit(GroupNode &aGroupNode);
  virtual void postvisit(GroupNode &aGroupNode);
  virtual void visit(TransformSeparator &aTransformSeparatorNode);
  virtual void postvisit(TransformSeparator &aTransformSeparatorNode);
  virtual void visit(SphereNode &aSphereNode);
  virtual void visit(LineNode &aLineNode);
  virtual void visit(TranslationNode &aTranslationNode);
  virtual void visit(RotationNode &aRotationNode);
  virtual void visit(ScaleNode &aScaleNode);
  virtual void visit(RotorNode &aRotorNode);
  virtual void visit(LightNode &aLightNode);
  virtual void visit(MaterialNode &aMateialNode);
  virtual void visit(ColorNode &aColorNode);
  virtual void visit(TextureNode &aTexNode);
  virtual void visit(ShadowNode &aShadowNode);
  virtual void visit(StarsNode &aStarNode);
  virtual void visit(RingNode &aRingNode);

private:
  void printIdent();
  unsigned mIdent;
  int glMatrixStackPos;
};

#endif // _H_DESTRUCTORVISITOR


