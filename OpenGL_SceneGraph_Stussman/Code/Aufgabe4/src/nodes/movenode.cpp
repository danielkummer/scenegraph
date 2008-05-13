#include "nodes/movenode.h"


//----------------------------------------------------------//
MoveNode::MoveNode():
  AbstractNode(), 
  mChanged(true), 
  mActive(true), 
  mDeltaPitch(0),
  mDeltaRoll(0),
  mDeltaX(0),
  mDeltaY(0),
  mDeltaYaw(0),
  mDeltaZ(0)
{
  for(unsigned i=0; i<16; i++){
    mModelMatrix[i] = 0.0f;
  }
  mModelMatrix[0] = 1.0f;
  mModelMatrix[5] = 1.0f;
  mModelMatrix[10] = 1.0f;
  mModelMatrix[15] = 1.0f;
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
  //unsigned vIdx;
   //float vDirSign = 1.0f;
  switch(aDir){
    //case UP:       vIdx = 4; break;     
    //case DOWN:     vIdx = 4; vDirSign = -1.0f; break;
    //case LEFT:     vIdx = 0; break;     
    //case RIGHT:    vIdx = 0; vDirSign = -1.0f; break;
    //case FORWARD:  vIdx = 8; vDirSign = -1.0f; break;  
    //case BACKWARD: vIdx = 8; break;
    case UP:       mDeltaY += aDist; break;     
    case DOWN:     mDeltaY -= aDist; break;
    case LEFT:     mDeltaX += aDist; break;     
    case RIGHT:    mDeltaX -= aDist; break;
    case FORWARD:  mDeltaZ -= aDist; break;  
    case BACKWARD: mDeltaZ += aDist; break;
  }

  //mDeltaX += vDirSign * aDist * mModelMatrix[vIdx];
  //mDeltaY += vDirSign * aDist * mModelMatrix[vIdx + 1];
  //mDeltaZ += vDirSign * aDist * mModelMatrix[vIdx + 2];
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


