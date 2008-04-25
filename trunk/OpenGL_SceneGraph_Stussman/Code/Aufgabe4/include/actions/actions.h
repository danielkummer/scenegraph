#ifndef _ACTIONS_H
#define _ACTIONS_H

#include "nodes/nodes.h"
#include "visitors/visitors.h"

//-------------------------------------------------------//
class ActionBase{
public:
  ActionBase();
  virtual ~ActionBase();
  void fire();
  virtual void apply() = 0; // action specific code goes here
  void enable();
  void disable();
  bool isEnabled();
  void add(AbstractNode* aNode);
  void remove(AbstractNode* aNode);
protected:
  std::vector<AbstractNode*> mListeners;
private:
  bool mEnabled;
};
//-------------------------------------------------------//




#endif // _ACTIONS_H

