#ifndef _H_PRINTVISITOR
#define _H_PRINTVISITOR

#include "nodes/allnodes.h"
#include "visitors/abstractvisitor.h"


class PrintVisitor:public AbstractVisitor{
public:
  PrintVisitor(): AbstractVisitor(), mIdent(0), glMatrixStackPos(0) { }
  virtual ~PrintVisitor() { }

  virtual void visit(AbstractNode &aNode);
  virtual void postvisit(AbstractNode &aNode);


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

  virtual void visit(Separator &aNode);
  virtual void postvisit(Separator &aNode);

  virtual void visit(SwitchNode &aNode);
  virtual void postvisit(SwitchNode &aNode);

  virtual void visit(ToggleNode &aNode);
  virtual void postvisit(ToggleNode &aNode);
  virtual void visit(MoveNode &aNode);

private:
  void printIdent();
  unsigned mIdent;
  int glMatrixStackPos;
};


#endif // _H_PRINTVISITOR

