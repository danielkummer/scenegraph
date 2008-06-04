#include "nodes/scalatornode.h"


//-------------------------------------------------------//
ScalatorNode::ScalatorNode(float aScaleX, 
                           float aScaleY, 
                           float aScaleZ,
                           float aScaleVelX, 
                           float aScaleVelY,
                           float aScaleVelZ, 
                           Clock* aClock):
ScaleNode(aScaleX, aScaleY, aScaleZ), 
ClockListener()
{
  if(NULL != aClock){
    mClock = aClock;
  }else{
    mClock =  Clock::getDefaultClock();
  }
  mClock->addListener(this);
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
  mScaleX += (mScaleVelX * aDt);
  mScaleY += (mScaleVelY * aDt);
  mScaleZ += (mScaleVelZ * aDt);
}
//----------------------------------------------------------//
ScalatorNode::~ScalatorNode(){
	mClock->removeListener(this);
}
//----------------------------------------------------------//

