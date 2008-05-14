#ifndef _H_ROTORNODE
#define _H_ROTORNODE

#include "clock.h"
#include "abstractnode.h"
#include "groupnode.h"

class DestructorNode:public GroupNode, public ClockListener{
public: 
	DestructorNode(float aLifetime,GroupNode* aParent,Clock* aClock=NULL);
// virtual void accept(AbstractVisitor &aVisitor);
  virtual void update(float aDt, double aTime);
 ~DestructorNode();
  float mLifetime;
  Clock* mClock;
  GroupNode* mParent;
};

#endif // _H_ROTORNODE


