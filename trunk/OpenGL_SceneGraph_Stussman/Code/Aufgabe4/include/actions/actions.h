#ifndef _ACTIONS_H
#define _ACTIONS_H

#include "nodes/nodes.h"
#include "visitors/visitors.h"

//-------------------------------------------------------//
class ActionBase:public GroupNode{
public:
  virtual ~ActionBase();
  inline virtual void accept(AbstractVisitor &aVisitor);
  inline void fire() { if(isEnabled()){ apply(); } }
  virtual void apply() = 0; // action specific code goes here
  inline void enable() { mEnabled = true; }
  inline void disable() { mEnabled = false; }
  inline bool isEnabled() { return mEnabled; }
private:
  bool mEnabled;
};
//-------------------------------------------------------//




#endif // _ACTIONS_H

