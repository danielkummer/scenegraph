#ifndef _ABSTRACTSPAWN_H_
#define _ABSTRACTSPAWN_H_

#include "nodes/abstractnode.h"
#include "nodes/groupnode.h"


class AbstractSpawn:public AbstractNode {
public:
  virtual void fire(){};
  bool mFire;
  void spawn();
protected:
  AbstractSpawn(GroupNode* aGroupNode):AbstractNode() {mGroupNode = aGroupNode;}
  GroupNode* mGroupNode;
  void add(AbstractNode* aNode);	
};

#endif // _ABSTRACTSPAWN_H_
