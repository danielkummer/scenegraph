#ifndef _H_RINGNODE
#define _H_RINGNODE

#define _USE_MATH_DEFINES
#include <math.h>

#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"


class RingNode:public AbstractNode{
public:
  RingNode(float fOuterRadius, float fInnerRadius, unsigned iQuadCount);
  virtual ~RingNode();
  virtual void accept(AbstractVisitor &aVisitor);

  float** mVertices;
  float mOuterRadius;
  float mInnerRadius;
  unsigned mQuadCount;
  int mVertexCount;

};

#endif // _H_RINGNODE


