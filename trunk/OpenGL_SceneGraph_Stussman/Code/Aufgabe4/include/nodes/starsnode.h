#ifndef _H_STARSNODE
#define _H_STARSNODE

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#include "nodes/abstractnode.h"

class StarsNode:public AbstractNode{
public:
  StarsNode(float aRadiusMin, float aDeltaR, unsigned aNumStars);
  virtual ~StarsNode();
  virtual void accept(AbstractVisitor &aVisitor);

  float mRadiusMin;
  float mDeltaR;
  unsigned mNumStars;
  float* mVertices;
  float* mSizes;
};

#endif // _H_STARSNODE


