#include "nodes/rotornode.h"


//-------------------------------------------------------//
RotorNode::RotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, Clock* aClock):
RotationNode(aAngle, aAxisX, aAxisY, aAxisZ), ClockListener()
{
  if(NULL != aClock){
    aClock->addListener(this);
  }else{
    Clock::getDefaultClock()->addListener(this);
  }
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
//----------------------------------------------------------//

