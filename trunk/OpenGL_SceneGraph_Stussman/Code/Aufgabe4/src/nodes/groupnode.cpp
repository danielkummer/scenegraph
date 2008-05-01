#include "nodes/groupnode.h"


//----------------------------------------------------------//
GroupNode::~GroupNode(){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->unref();
  }
  mChildren.clear();
}
//----------------------------------------------------------//
void GroupNode::add(AbstractNode* aNode){
  aNode->ref();
  mChildren.push_back(aNode);
}
//----------------------------------------------------------//
void GroupNode::remove(AbstractNode* aNode){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    if(*vItr == aNode){
      aNode->unref();
      vItr = mChildren.erase(vItr);
      break;
    }
  }
}
//----------------------------------------------------------//
void GroupNode::clear(){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->unref();
  }
  mChildren.clear();
}
//----------------------------------------------------------//
void GroupNode::visitChildren(AbstractVisitor &aVisitor){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->accept(aVisitor);
  }
}
//----------------------------------------------------------//
inline void GroupNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  visitChildren(aVisitor);
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

