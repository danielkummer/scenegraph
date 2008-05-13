#ifndef _H_ROTORNODE
#define _H_ROTORNODE

#include "clock.h"
#include "nodes/rotationnode.h"

class RotorNode:public RotationNode, public ClockListener{
public: 
  RotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, Clock* aClock=NULL);
  virtual void accept(AbstractVisitor &aVisitor);
  virtual void update(float aDt, double aTime);
  ~RotorNode();
  Clock* mClock;
  float mAngleVel;
};

#endif // _H_ROTORNODE


