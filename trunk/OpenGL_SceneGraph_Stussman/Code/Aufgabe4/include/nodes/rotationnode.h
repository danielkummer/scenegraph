#ifndef _H_ROTATIONNODE
#define _H_ROTATIONNODE

#define _USE_MATH_DEFINES
#include <math.h>

#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"

class RotationNode:public AbstractNode{
public:
  RotationNode(float aAngle, float aAxisX, float aAxisY, float aAxisZ);
  virtual void accept(AbstractVisitor &aVisitor);

  // aAngle in radians
  void setAngle(float aAngle);
  // return the angle in degrees
  inline float getAngle() { return mGradAngle; }
  inline float getRadAngle() { return (float)(mGradAngle * M_PI / 180.0f); }

  float mAxisX, mAxisY, mAxisZ;
  float mGradAngle; // degrees
};

#endif // _H_ROTATIONNODE


