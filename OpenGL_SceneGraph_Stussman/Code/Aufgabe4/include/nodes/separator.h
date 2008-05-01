#ifndef _H_SEPARATOR
#define _H_SEPARATOR

#include "nodes/groupnode.h"

class Separator:public GroupNode{
public:
  Separator();
  virtual ~Separator();
  virtual void accept(AbstractVisitor &aVisitor);
};

#endif // _H_SEPARATOR


