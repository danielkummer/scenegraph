#include "nodes/camfollownode.h"


CamFollowNode::CamFollowNode(AbstractNode* aGlueNode):CamNode(){
	mGlueNode = aGlueNode;
	mGlueNode->ref(); 
}

CamFollowNode::~CamFollowNode(){
	mGlueNode->unref();
}

void CamFollowNode::accept(AbstractVisitor& aVisitor){
	aVisitor.visit(*this);
}
