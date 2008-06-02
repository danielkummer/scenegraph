#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"


//----------------------------------------------------------//
AbstractNode::AbstractNode():mID(getID()),mRefCount(0), mCollidable(0){
  for(unsigned i=0; i<16; i++){
    mModelMatrix[i] = 0.0f;
  }
  mModelMatrix[0]  = 1.0f;
  mModelMatrix[5]  = 1.0f;
  mModelMatrix[10] = 1.0f;
  mModelMatrix[15] = 1.0f;
}
//----------------------------------------------------------//
AbstractNode::~AbstractNode(){
}
//----------------------------------------------------------//
void AbstractNode::ref(){
  mRefCount++;
}
//----------------------------------------------------------//
void AbstractNode::unref(){
  mRefCount--;
  if(mRefCount <= 0){
    delete this;
  }
}
//----------------------------------------------------------//
unsigned int AbstractNode::getID(){
  mIDCount += 1;
  return mIDCount;
}
//-------------------------------------------------------//
unsigned AbstractNode::mIDCount = 0;
//-------------------------------------------------------//

