#ifndef _H_SWITCHACTION_
#define _H_SWITCHACTION_

#include "actions/actionbase.h"
#include "nodes/switchnode.h"

class SwitchAction:public ActionBase{
public:
  //SwitchAction();
  //virtual ~SwitchAction();

  virtual void fire();
  virtual void fire(float aValue);


};


#endif //_H_SWITCHACTION_

