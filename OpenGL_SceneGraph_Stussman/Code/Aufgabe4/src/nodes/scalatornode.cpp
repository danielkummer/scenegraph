#include "nodes/scalatornode.h"


//-------------------------------------------------------//
ScalatorNode::ScalatorNode(float aScaleX, float aScaleY, float aScaleZ,
float aScaleVelX, float aScaleVelY,float aScaleVelZ, Clock* aClock):
ScaleNode(aScaleX, aScaleY, aScaleZ), ClockListener()
{
  if(NULL != aClock){
    aClock->addListener(this);
  }else{
    Clock::getDefaultClock()->addListener(this);
  }
  mScaleVelX = aScaleVelX;
  mScaleVelY = aScaleVelY;
  mScaleVelZ = aScaleVelZ;
}
//----------------------------------------------------------//
inline void ScalatorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void ScalatorNode::update(float aDt, double aTime){
  mScaleX = (mScaleVelX * aDt);
  mScaleY = (mScaleVelY * aDt);
  mScaleZ = (mScaleVelZ * aDt);
}
//----------------------------------------------------------//

