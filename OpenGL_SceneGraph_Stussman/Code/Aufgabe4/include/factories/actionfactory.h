#ifndef _ACTION_FACTORY_H
#define _ACTION_FACTORY_H


#include "actions/actionbase.h"
#include "actions/onoffaction.h"

// TODO: add all action classes
enum EActions{
  EToggleAction,

  EActionCount,
};




class ActionFactory{
public:
  ActionFactory(unsigned* aActionMapping, unsigned aCount);
  ~ActionFactory();
  ActionBase* getAction(unsigned aActionName);


private:
  ActionBase* createAction(unsigned aActionName);
  unsigned* mMapping;
  ActionBase** mActionInstances;
  unsigned mCount;
};



#endif // _ACTION_FACTORY_H
