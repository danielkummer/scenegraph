#include "nodes/rotornode.h"


//-------------------------------------------------------//
RotorNode::RotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, Clock* aClock):
RotationNode(aAngle, aAxisX, aAxisY, aAxisZ), ClockListener()
{
  if(NULL != aClock){
    mClock = aClock;
  }else{
    mClock = Clock::getDefaultClock();
  }
  mClock->addListener(this);
  mAngleVel = aAngleVel;
}
//----------------------------------------------------------//
inline void RotorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void RotorNode::update(float aDt, double aTime){
  mGradAngle += (mAngleVel * aDt);
  if(mGradAngle > 360.0f){
    mGradAngle -= 360.0f;
  }
}
RotorNode::~RotorNode(){
	mClock->removeListener(this);
}
//----------------------------------------------------------//

