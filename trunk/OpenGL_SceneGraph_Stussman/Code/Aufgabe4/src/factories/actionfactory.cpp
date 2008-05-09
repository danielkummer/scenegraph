#include "factories/actionfactory.h"
#include <assert.h>



ActionFactory::ActionFactory(unsigned int *aActionMapping, unsigned int aCount){
  mMapping = new unsigned[aCount];
  mActionInstances = new ActionBase*[aCount];
  // copy mapping and init instances
  for(unsigned i=0; i<aCount; i++){
    if(0 < aActionMapping[i]){
      mMapping[i] = aActionMapping[i];
    }else{
      mMapping[i] = 0;
    }
    mActionInstances[i] = NULL;
  }
  mCount = aCount;
}
//-------------------------------------------------------//
ActionFactory::~ActionFactory(){
  delete[] mMapping;
  for(unsigned i=0; i<mCount; i++){
    delete mActionInstances[i];
  }
  delete[] mActionInstances;
}
//-------------------------------------------------------//
ActionBase* ActionFactory::getAction(unsigned int aActionName){
  assert(mCount > aActionName);
  if(NULL == mActionInstances[aActionName]){
    mActionInstances[aActionName] = createAction(aActionName);
  }
  assert(NULL != mActionInstances[aActionName]);
  return mActionInstances[aActionName];
}
//-------------------------------------------------------//
ActionBase* ActionFactory::createAction(unsigned int aActionName){
  assert(mCount > aActionName);
  unsigned vActionNr = mMapping[aActionName];
  ActionBase* vInstance = NULL;
  float vDist = 0.1f;
  float vAngle = 0.2f;
  switch(vActionNr){
    // TODO: insert all new actions
    case EToggleAction:
      {
        vInstance = new OnOffAction();
      }break;
    case EShipMoveBackAction:
      {
        vInstance = new MoveAction(BACKWARD, vDist);
      }break;
    case EShipMoveFwdAction:
      {
        vInstance = new MoveAction(FORWARD, vDist);
      }break;
    case EShipStrafeLeftAction:
      {
        vInstance = new MoveAction(LEFT, vDist);
      }break;
    case EShipStraveRightAction:
      {
        vInstance = new MoveAction(RIGHT, vDist);
      }break;
    case EShipMoveUpAction:
      {
        vInstance = new MoveAction(UP, vDist);
      }break;
    case EShipMoveDownAction:
      {
        vInstance = new MoveAction(DOWN, vDist);
      }break;

    case EShipRollClkAction:
      {
        vInstance = new RotationAction(ROLL, vAngle);
      }break;
    case EShipRollCClkAction:
      {
        vInstance = new RotationAction(ROLLCC, vAngle);
      }break;
    case EShipPitchClkAction:
      {
        vInstance = new RotationAction(PITCH, vAngle);
      }break;
    case EShipPitchCClkAction:
      {
        vInstance = new RotationAction(PITCHCC, vAngle);
      }break;
    case EShipYawClkAction:
      {
        vInstance = new RotationAction(YAW, vAngle);
      }break;
    case EShipYawCClkAction:
      {
        vInstance = new RotationAction(YAWCC, vAngle);
      }break;
  }
  return vInstance;

}
//-------------------------------------------------------//
//-------------------------------------------------------//
