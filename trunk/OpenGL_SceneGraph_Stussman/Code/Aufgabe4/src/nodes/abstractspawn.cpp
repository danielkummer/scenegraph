#include "nodes/abstractspawn.h"

AbstractSpawn::AbstractSpawn(GroupNode* aGroupNode):AbstractNode(){
    mGroupNode = aGroupNode;
    mFire = false;
}

void AbstractSpawn::spawn(){
   mFire = true;
}

void AbstractSpawn::add(AbstractNode* aNode){
   mGroupNode->add(aNode);
}

void AbstractSpawn::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
