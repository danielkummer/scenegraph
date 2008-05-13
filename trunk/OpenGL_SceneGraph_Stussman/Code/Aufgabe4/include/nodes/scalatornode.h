#ifndef _H_ROTORNODE
#define _H_ROTORNODE

#include "clock.h"
#include "nodes/scalenode.h"

class ScalatorNode:public ScaleNode, public ClockListener{
public: 
	ScalatorNode(float aScaleX, float aScaleY, float aScaleZ,float aScaleVelX, float aScaleVelY,float aScaleVelZ, Clock* aClock) ;
virtual void accept(AbstractVisitor &aVisitor);
  virtual void update(float aDt, double aTime);

  float mScaleVelX,mScaleVelY,mScaleVelZ;
};

#endif // _H_ROTORNODE


