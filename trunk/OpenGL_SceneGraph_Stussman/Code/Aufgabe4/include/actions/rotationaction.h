#ifndef _H_ROTACTION
#define _H_ROTACTION

#include "actions/actionbase.h"
#include "nodes/movenode.h"  // for axis enum

class RotationAction:public ActionBase{
public:
  RotationAction(EAxis aAxis, float aAngle);
  virtual ~RotationAction();
  virtual void fire();
  virtual void fire(float aAngle);


private:
  EAxis mAxis;
  float mAngle;
};





#endif // _H_ROTACTION


