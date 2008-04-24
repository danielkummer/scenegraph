#ifndef _VISITORS_H
#define _VISITORS_H


#include "nodes/nodes.h"

//-------------------------------------------------------//
class AbstractVisitor{
public:
  AbstractVisitor() { }
  virtual ~AbstractVisitor() { }

  virtual void visit(GroupNode &aGroupNode ) { }
  virtual void postvisit(GroupNode &aGroupNode ) { }
  virtual void visit(TransformSeparator &aTransformSeparatorNode) { }
  virtual void postvisit(TransformSeparator &aTransformSeparatorNode) { }

  virtual void visit(ToggleNode &aToggleNode) { }
  virtual void postvisit(ToggleNode &aToggleNode) { }
  virtual void visit(SwitchNode &aSwitchNode) { }
  virtual void postvisit(SwitchNode &aSwitchNode) { }


  virtual void visit(SphereNode &aSphereNode ) { }
  virtual void visit(LineNode &aLineNode ) { }
  virtual void visit(TranslationNode &aTranslationNode) { }
  virtual void visit(RotationNode &aRotationNode ) { }
  virtual void visit(ScaleNode &aScaleNode) { }
  virtual void visit(RotorNode &RotorNode ) { }
  virtual void visit(LightNode &aLightNode) { }
  virtual void visit(MaterialNode &aMaterialNode) { }
  virtual void visit(ColorNode &aColorNode) { }
  virtual void visit(TextureNode &aTexNode) { }
  virtual void visit(ShadowNode &aShadow) { }
  virtual void visit(StarsNode &aStarNode) { }
  virtual void visit(RingNode &aRingNode) { }

  void apply(AbstractNode* aAbstractNode);
protected:
  AbstractNode* mRootNode;
};
//-------------------------------------------------------//
class Visitor:public AbstractVisitor{
public:
  Visitor(): AbstractVisitor() { }
  virtual ~Visitor() { }
  virtual void visit(SphereNode &aSphereNode);
  virtual void visit(LineNode &aLineNode );
  virtual void visit(TranslationNode &aTranslationNode);
  virtual void visit(RotationNode &aRotationNode);
  virtual void visit(ScaleNode &aScaleNode);
  virtual void visit(RotorNode &aRotorNode);
  virtual void visit(LightNode &aLightNode);
  virtual void visit(MaterialNode &aMaterialNode);
  virtual void visit(ColorNode &aColorNode);
  virtual void visit(TextureNode &aTexNode);
  virtual void visit(ShadowNode &aShadow);
  virtual void visit(StarsNode &aStarNode);
  virtual void visit(RingNode &aRingNode);
};
//-------------------------------------------------------//
class DestructorVisitor:public AbstractVisitor{
public:
  DestructorVisitor(): AbstractVisitor() { }
  virtual ~DestructorVisitor() { }
  virtual void postvisit(GroupNode &aGroupNode);
  virtual void postvisit(TransformSeparator &aTransformSep);
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
//-------------------------------------------------------//
class EventVisitor:public AbstractVisitor{
public:
  EventVisitor():AbstractVisitor() { }
  void apply(AbstractNode* aAbstractNode, SDL_Event &aEvent);
  virtual void visit(AbstractNode &aAbstractNode);

private:
  SDL_Event mEvent;
};



#endif
