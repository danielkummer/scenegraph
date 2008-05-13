#ifndef _H_ACTIONBASE
#define _H_ACTIONBASE

#include <vector>

#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"

class ActionBase{
public:
  ActionBase();
  virtual ~ActionBase();
  virtual void fire() = 0;
  virtual void fire(float aValue) = 0;
  void enable();
  void disable();
  bool isEnabled();
  void toggle();
  virtual void add(AbstractNode* aNode);
  void remove(AbstractNode* aNode);
protected:
  std::vector<AbstractNode*> mListeners;
  bool mEnabled;
};

#endif // _H_ACTIONBASE


