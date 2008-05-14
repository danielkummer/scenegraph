#include "nodes/destructornode.h"


//-------------------------------------------------------//
DestructorNode::DestructorNode(float aLifetime,GroupNode* aParent, Clock* aClock):
GroupNode(), ClockListener()
{
  if(NULL != aClock){
    mClock = aClock;
  }else{
    mClock =  Clock::getDefaultClock();
  }
  mClock->addListener(this);
  mLifetime = aLifetime;
  mParent = aParent;
}

void DestructorNode::update(float aDt, double aTime){
	if(aTime > mLifetime){
		mParent->remove(this); // remove me from parent, will auto delete this
	}
}
DestructorNode::~DestructorNode(){
	clear();	
}
//----------------------------------------------------------//

