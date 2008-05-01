#ifndef _H_LINENODE
#define _H_LINENODE

#include "nodes/abstractnode.h"

class LineNode:public AbstractNode{
public:
  LineNode(float aVert1X,
           float aVert1Y, 
           float aVert1Z, 
           float aVert2X, 
           float aVert2Y, 
           float aVert2Z, 
           float aWidth=1.0);
  virtual void accept(AbstractVisitor &aVisitor);

  float mVert1X;
  float mVert1Y;
  float mVert1Z;
  float mVert2X;
  float mVert2Y;
  float mVert2Z;
  float mWidth;
};

#endif // _H_LINENODE


