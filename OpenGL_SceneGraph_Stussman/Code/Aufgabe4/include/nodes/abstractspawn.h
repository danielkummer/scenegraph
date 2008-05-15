#ifndef _ABSTRACTSPAWN_H_
#define _ABSTRACTSPAWN_H_

#include "nodes/abstractnode.h"
#include "nodes/groupnode.h"


class AbstractSpawn:public AbstractNode {
public:
  virtual void fire(){};
  bool mFire;
  void spawn(); 
  virtual void accept(AbstractVisitor&);

protected:
  AbstractSpawn(GroupNode* aGroupNode);
  GroupNode* mGroupNode;
  void add(AbstractNode* aNode);	
};

#endif // _ABSTRACTSPAWN_H_
