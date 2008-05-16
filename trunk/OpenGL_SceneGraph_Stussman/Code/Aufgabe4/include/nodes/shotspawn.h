#ifndef _SHOTSPAWN_H
#define _SHOTSPAWN_H
#include "nodes/abstractspawn.h"

class ShotSpawn: public AbstractSpawn {
public:
	virtual void fire();
  virtual void fire(float aPosX, float aPosY, float aPosZ, float aDirX, float aDirY, float aDirZ);
  ShotSpawn(GroupNode* aGroupNode):AbstractSpawn(aGroupNode){};
};
#endif
