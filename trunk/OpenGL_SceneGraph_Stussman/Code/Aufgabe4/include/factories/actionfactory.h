#ifndef _ACTION_FACTORY_H
#define _ACTION_FACTORY_H


#include "actions/actionbase.h"
#include "actions/onoffaction.h"
#include "actions/moveaction.h"
#include "actions/rotationaction.h"
#include "nodes/movenode.h"

// TODO: add all action classes
enum EActions{
  EToggleAction,

  EShipShootAction,
  EShipMoveFwdAction,
  EShipMoveBackAction,
  EShipStrafeLeftAction,
  EShipStraveRightAction,
  EShipMoveUpAction,
  EShipMoveDownAction,
  EShipRollClkAction,
  EShipRollCClkAction,
  EShipPitchClkAction,
  EShipPitchCClkAction,
  EShipYawClkAction,
  EShipYawCClkAction,
  
  ECamSwitchTypeAction,
  ECamMoveFwdAction,
  ECamMoveBackAction,
  ECamStrafeRightAction,
  ECamStrafeLeftAction,
  ECamMoveUpAction,
  ECamMoveDownAction,
  ECamRollClockwiseAction,
  ECamRollCClockwiseAction,
  ECamPitchClockwiseAction,
  ECamPitchCClockwiseAction,
  ECamYawClockwiseAction,
  ECamYawCClockwiseAction,



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
