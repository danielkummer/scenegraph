#include "nodes/translatornode.h"

  float mXVel, mYVel, mZVel;
  float mX, mY, mZ;


TranslatorNode::TranslatorNode(float aXVel, float aYVel, float aZVel, float aX, float aY, float aZ, Clock* aClock):
TranslationNode(aX, aY, aZ), ClockListener()
{
  if(NULL != aClock){
    mClock = aClock;
  }else{
    mClock = Clock::getDefaultClock();
  }	
  mClock->addListener(this);
  mXVel = aXVel;
  mYVel = aYVel;
  mZVel = aZVel;
}

inline void TranslatorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}

void TranslatorNode::update(float aDt, double aTime){
	mX += mXVel * aDt;
	mY += mYVel * aDt;
	mZ += mZVel * aDt;
}

TranslatorNode::~TranslatorNode(){
	mClock->removeListener(this);
}
