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
  void realAdd();
  void realRemove();
  virtual void visitChildren(AbstractVisitor &aVisitor);
  std::vector<AbstractNode*> mChildren;
  std::vector<AbstractNode*> mToRemove;
  std::vector<AbstractNode*> mToAdd;
};

#endif // _H_GROUPNODE


