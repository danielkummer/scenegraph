#ifndef _H_SWITCHNODE
#define _H_SWITCHNODE

#include "nodes/groupnode.h"

class SwitchNode:public GroupNode{
public:
  SwitchNode():GroupNode(), mCurrent(-1) { }
  virtual void accept(AbstractVisitor &aVisitor);
  void switchTo(unsigned aChildNr);
private:
  int mCurrent;
};

#endif // _H_SWITCHNODE


