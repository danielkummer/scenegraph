#ifndef _H_ROTACTION
#define _H_ROTACTION

#include "actions/actionbase.h"
#include "nodes/movenode.h"

class RotationAction:ActionBase{
public:
  RotationAction(EAxis aAxis, float aAngle);
  virtual ~RotationAction();
  virtual void apply();


private:
  EAxis mAxis;
  float mAngle;
};





#endif // _H_ROTACTION


