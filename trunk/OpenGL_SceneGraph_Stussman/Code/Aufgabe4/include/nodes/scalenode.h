#ifndef _H_SCALENODE
#define _H_SCALENODE

#include "visitors/abstractvisitor.h"
#include "nodes/abstractnode.h"

class ScaleNode:public AbstractNode{
public:
  ScaleNode(float aScaleX=1.0f, float aScaleY=1.0f, float aScaleZ=1.0f);
  virtual void accept(AbstractVisitor &aVisitor);

  float mScaleX, mScaleY, mScaleZ;
};

#endif // _H_SCALENODE


