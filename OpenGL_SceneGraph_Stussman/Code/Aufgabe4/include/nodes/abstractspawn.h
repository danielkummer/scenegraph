#ifndef _ABSTRACTSPAWN_H_
#define _ABSTRACTSPAWN_H_
#include "nodes/abstractnode.h"
#include "nodes/groupnode.h"

class AbstractSpawn {
public:
	virtual void spawn(){};
	void add(AbstractNode* aNode){mGroupNode->add(aNode));};
protected:
	AbstractSpawn(GroupNode* aGroupNode){mGroupNode = aGroupNode;};
	GroupNode* mGroupNode;
};

#endif // _ABSTRACTSPAWN_H_
