#ifndef CAMFOLLOWNODE_H_
#define CAMFOLLOWNODE_H_


#include "nodes/groupnode.h"
#include "nodes/cam.h"

class CamFollowNode:public CamNode{
public:
  CamFollowNode(AbstractNode* aGlueNode);
  virtual ~CamFollowNode();
  AbstractNode* mGlueNode;
  virtual void accept(AbstractVisitor& aVisitor);  
};

#endif /*CAMFOLLOWNODE_H_*/
