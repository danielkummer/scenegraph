#ifndef _H_COLORNODE
#define _H_COLORNODE

#include "nodes/abstractnode.h"

class ColorNode:public AbstractNode{
public: 
  ColorNode(float aRed=1.0f, float aGreen=1.0f, float aBlue=1.0f, float aAlpha=1.0f);
  virtual ~ColorNode();
  virtual void accept(AbstractVisitor &aVisitor);

  float mRed;
  float mGreen;
  float mBlue;
  float mAlpha;
};

#endif // _H_COLORNODE


