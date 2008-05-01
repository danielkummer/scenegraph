#ifndef _H_ABSTRACTNODE
#define _H_ABSTRACTNODE


//class AbstractVisitor;
#include "visitors/abstractvisitor.h"

class AbstractNode{
public:
  AbstractNode();
  virtual ~AbstractNode();
  void ref();
  void unref();
  virtual void accept(AbstractVisitor &) = 0;

  const unsigned mID;

private:
  static unsigned getID();
  static unsigned mIDCount;

  int mRefCount;
};

#endif // _H_ABSTRACTNODE


