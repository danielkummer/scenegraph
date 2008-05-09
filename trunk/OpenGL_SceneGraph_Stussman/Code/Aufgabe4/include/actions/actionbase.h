#ifndef _H_ACTIONBASE
#define _H_ACTIONBASE

#include <vector>

#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"

class ActionBase{
public:
  ActionBase();
  virtual ~ActionBase();
  virtual void fire();
  virtual void apply() = 0; // action specific code goes here
  void enable();
  void disable();
  bool isEnabled();
  void toggle();
  virtual void add(AbstractNode* aNode);
  void remove(AbstractNode* aNode);
protected:
  std::vector<AbstractNode*> mListeners;
private:
  bool mEnabled;
};

#endif // _H_ACTIONBASE


