#ifndef _H_TRANSLATIONNODE
#define _H_TRANSLATIONNODE

#include "nodes/abstractnode.h"

class TranslationNode:public AbstractNode{
public:
  TranslationNode(float aX, float aY, float aZ);
  virtual void accept(AbstractVisitor &aVisitor);

  float mX, mY, mZ;
};

#endif // _H_TRANSLATIONNODE


