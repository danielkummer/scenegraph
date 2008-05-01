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
  virtual void visit(AbstractNode &aNode) { }
  virtual void postvisit(AbstractNode &aNode) { }
  };

#endif // _H_DESTRUCTORVISITOR


