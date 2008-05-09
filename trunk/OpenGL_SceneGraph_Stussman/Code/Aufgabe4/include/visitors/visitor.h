#ifndef _H_VISITOR
#define _H_VISITOR

#include "nodes/allnodes.h"
#include "visitors/abstractvisitor.h"

class Visitor:public AbstractVisitor{
public:
  Visitor();
  virtual ~Visitor();

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
  virtual void visit(Separator &aNode);
  virtual void postvisit(Separator &aNode);
  virtual void visit(TransformSeparator &aNode);
  virtual void postvisit(TransformSeparator &aNode);
  virtual void visit(MoveNode &aNode);
  virtual void visit(PolygonObjectNode &aPolygonObjectNode);
};

#endif // _H_VISITOR

