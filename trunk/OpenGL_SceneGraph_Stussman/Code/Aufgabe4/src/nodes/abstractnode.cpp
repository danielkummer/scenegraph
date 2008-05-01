#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"


//----------------------------------------------------------//
AbstractNode::AbstractNode():mID(getID()),mRefCount(0){
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

