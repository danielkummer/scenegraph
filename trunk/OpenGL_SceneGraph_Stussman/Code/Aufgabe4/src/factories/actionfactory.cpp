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
  float vDist = 0.05f;
  float vAngle = 1.0f;
  switch(vActionNr){
    // TODO: insert all new actions
    case EToggleAction:
      {
        vInstance = new OnOffAction();
      }break;
    // Ship actions      
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
    case EShipStrafeRightAction:
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
    case EShipShootAction:
      {
        vInstance = new ShootAction();
      }break;
	// Camera actions
    case ECamMoveBackAction:
      {
        vInstance = new MoveAction(BACKWARD, vDist);
      }break;
    case ECamMoveFwdAction:
      {
        vInstance = new MoveAction(FORWARD, vDist);
      }break;
    case ECamStrafeLeftAction:
      {
        vInstance = new MoveAction(LEFT, vDist);
      }break;
    case ECamStrafeRightAction:
      {
        vInstance = new MoveAction(RIGHT, vDist);
      }break;
    case ECamMoveUpAction:
      {
        vInstance = new MoveAction(UP, vDist);
      }break;
    case ECamMoveDownAction:
      {
        vInstance = new MoveAction(DOWN, vDist);
      }break;

    case ECamRollClockwiseAction:
      {
        vInstance = new RotationAction(ROLL, vAngle);
      }break;
    case ECamRollCClockwiseAction:
      {
        vInstance = new RotationAction(ROLLCC, vAngle);
      }break;
    case ECamPitchClockwiseAction:
      {
        vInstance = new RotationAction(PITCH, vAngle);
      }break;
    case ECamPitchCClockwiseAction:
      {
        vInstance = new RotationAction(PITCHCC, vAngle);
      }break;
    case ECamYawClockwiseAction:
      {
        vInstance = new RotationAction(YAW, vAngle);
      }break;
    case ECamYawCClockwiseAction:
      {
        vInstance = new RotationAction(YAWCC, vAngle);
      }break;
    case ECamSwitchTypeAction:
      {
        vInstance = new SwitchAction();
      }break;
  }
  return vInstance;

}
//-------------------------------------------------------//
//-------------------------------------------------------//
