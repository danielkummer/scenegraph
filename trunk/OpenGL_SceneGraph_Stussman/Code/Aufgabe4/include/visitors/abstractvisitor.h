#ifndef _H_ABSTRACTVISITOR
#define _H_ABSTRACTVISITOR

class AbstractNode;
class GroupNode;
class ColorNode;
class LightNode;
class LineNode;
class MaterialNode;
class RingNode;
class RotationNode;
class RotorNode;
class ScaleNode;
class Separator;
class ShadowNode;
class SphereNode;
class StarsNode;
class SwitchNode;
class ToggleNode;
class TransformSeparator;
class TranslationNode;
class TextureNode;

class AbstractVisitor{
public:
  AbstractVisitor() { }
  virtual ~AbstractVisitor() { }

  virtual void visit(AbstractNode &aNode) { }
  virtual void visit(GroupNode &aGroupNode ) { }
  virtual void postvisit(GroupNode &aGroupNode ) { }
/*
  virtual void visit(TransformSeparator &aTransformSeparatorNode) { }
  virtual void postvisit(TransformSeparator &aTransformSeparatorNode) { }

  virtual void visit(ToggleNode &aToggleNode) { }
  virtual void postvisit(ToggleNode &aToggleNode) { }
  virtual void visit(SwitchNode &aSwitchNode) { }
  virtual void postvisit(SwitchNode &aSwitchNode) { }
*/
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

#endif // _H_ABSTRACTVISITOR


