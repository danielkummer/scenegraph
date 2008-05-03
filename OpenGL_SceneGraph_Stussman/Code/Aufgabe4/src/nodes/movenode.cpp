#include "nodes/movenode.h"


//----------------------------------------------------------//
MoveNode::MoveNode(){
}
//----------------------------------------------------------//
MoveNode::~MoveNode(){
}
//----------------------------------------------------------//
void MoveNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//
void MoveNode::move(EDirection aDir, float aDist){
  unsigned vIdx;
  int vDirSign = 1;
  switch(aDir){
    case UP:       vIdx = 4; break;     
    case DOWN:     vIdx = 4; vDirSign = -1; break;
    case LEFT:     vIdx = 0; break;     
    case RIGHT:    vIdx = 0; vDirSign = -1; break;
    case FORWARD:  vIdx = 8; vDirSign = -1; break;  
    case BACKWARD: vIdx = 8; break;
  }
  mDeltaX += vDirSign * aDist * mModelMatrix[vIdx];
  mDeltaY += vDirSign * aDist * mModelMatrix[vIdx + 1];
  mDeltaZ += vDirSign * aDist * mModelMatrix[vIdx + 2];
  mChanged = true;
}
//----------------------------------------------------------//
void MoveNode::rotate(EAxis aAxis, float aAngle){
  switch(aAxis){
    case ROLL: mDeltaRoll += aAngle; break;
    case YAW: mDeltaYaw += aAngle; break;
    case PITCH: mDeltaPitch += aAngle; break;
    case ROLLCC: mDeltaRoll -= aAngle; break;
    case YAWCC: mDeltaYaw -= aAngle; break;
    case PITCHCC: mDeltaPitch -= aAngle; break;
  }
  mChanged = true;
}
//----------------------------------------------------------//
float MoveNode::getX(){
  return mDeltaX;
}
//----------------------------------------------------------//
float MoveNode::getY(){
  return mDeltaY;
}
//----------------------------------------------------------//
float MoveNode::getZ(){
  return mDeltaZ;
}
//----------------------------------------------------------//
float MoveNode::getRoll(){
  return mDeltaRoll;
}
//----------------------------------------------------------//
float MoveNode::getYaw(){
  return mDeltaYaw;
}
//----------------------------------------------------------//
float MoveNode::getPitch(){
  return mDeltaPitch;
}
//----------------------------------------------------------//
bool MoveNode::getChanged(){
  return mChanged;
}
//----------------------------------------------------------//
void MoveNode::setChanged(bool aYesOrNo){
  mChanged = aYesOrNo;
}
//----------------------------------------------------------//
void MoveNode::reset(){
    mDeltaX = 0.0f;
    mDeltaY = 0.0f;
    mDeltaZ = 0.0f;
    mDeltaRoll = 0.0f;
    mDeltaYaw = 0.0f;
    mDeltaPitch = 0.0f;
    mChanged = false;
}
//----------------------------------------------------------//
void MoveNode::activate(){
  mActive = true;
}
//----------------------------------------------------------//
void MoveNode::deactivate(){
  mActive = false;
}
//----------------------------------------------------------//
bool MoveNode::isActive(){
  return mActive;
}
//----------------------------------------------------------//


