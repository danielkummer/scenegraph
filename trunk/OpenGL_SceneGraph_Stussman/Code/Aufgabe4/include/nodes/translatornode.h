#ifndef TRANSLATORNODE_H_
#define TRANSLATORNODE_H_

#include "clock.h"
#include "nodes/translationnode.h"

class TranslatorNode:public TranslationNode, public ClockListener{
public: 
  TranslatorNode(float aXVel, float aYVel, float aZVel, float aX, float aY, float aZ, Clock* aClock=NULL);
  virtual void accept(AbstractVisitor &aVisitor);
  virtual void update(float aDt, double aTime);
  ~TranslatorNode();
  
  Clock *mClock;
  float mXVel, mYVel, mZVel;
//  float mX, mY, mZ;
};

#endif /*TRANSLATORNODE_H_*/
