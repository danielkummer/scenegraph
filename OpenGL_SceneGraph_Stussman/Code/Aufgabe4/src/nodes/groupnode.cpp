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
  mToAdd.push_back(aNode);
}
//----------------------------------------------------------//
void GroupNode::remove(AbstractNode* aNode){
  mToRemove.push_back(aNode);
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
  // add
  for(vItr = mToAdd.begin(); vItr < mToAdd.end(); vItr++){
    mChildren.push_back(*vItr);
  }
  mToAdd.clear();
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->accept(aVisitor);
  }
  // remove 
  std::vector<AbstractNode*>::iterator vRmItr;
  for(vRmItr = mToRemove.begin(); vRmItr < mToRemove.end(); vRmItr++){
    for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
      if(*vItr == *vRmItr){
        (*vRmItr)->unref();
        vItr = mChildren.erase(vItr);
        break;
      }
    }
  }
  mToRemove.clear();

}
//----------------------------------------------------------//
inline void GroupNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  visitChildren(aVisitor);
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

