#ifndef _H_TOGGLENODE
#define _H_TOGGLENODE

#include "nodes/groupnode.h"

class ToggleNode:public GroupNode{
public:
  ToggleNode();
  virtual ~ToggleNode();
  bool isOn();
  bool toggle(); // return new state
  void on();
  void off();
  virtual void accept(AbstractVisitor &aVisitor);

private:
  bool mState;
 
};

#endif // _H_TOGGLENODE


