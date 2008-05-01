#ifndef _H_GROUPNODE
#define _H_GROUPNODE


#include <vector>

#include "nodes/abstractnode.h"

class GroupNode:public AbstractNode{
public:
  virtual ~GroupNode();
  virtual void add(AbstractNode* aNode);
  virtual void remove(AbstractNode* aNode);
  virtual void clear();
  virtual void accept(AbstractVisitor &aVisitor);
protected:
  virtual void visitChildren(AbstractVisitor &aVisitor);
  std::vector<AbstractNode*> mChildren;
};

#endif // _H_GROUPNODE


