#ifndef _ABSTRACTSPAWN_H_
#define _ABSTRACTSPAWN_H_

#include "nodes/abstractnode.h"
#include "nodes/groupnode.h"


class AbstractSpawn:public AbstractNode {
public:
  virtual void fire(){};
  virtual void fire(float aPosX, float aPosY, float aPosZ, float aDirX, float aDirY, float aDirZ) { }

  bool mFire;
  void spawn(); 
  virtual void accept(AbstractVisitor&);

protected:
  AbstractSpawn(GroupNode* aGroupNode);
  GroupNode* mGroupNode;
  void add(AbstractNode* aNode);	
};

#endif // _ABSTRACTSPAWN_H_
