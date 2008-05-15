#ifndef _H_SHOOTACTION_
#define _H_SHOOTACTION_

#include "actions/actionbase.h"

class ShootAction:ActionBase{
public:
  ShootAction();
  virtual ~ShootAction();

  virtual void fire();
  virtual void fire(float aVal);
  void add(AbstractNode* aNode);

}



#endif // _H_SHOOTACTION_


