#ifndef _LASERSPAWN_H
#define _LASERSPAWN_H
#include "nodes/abstractspawn.h"

class LaserSpawn: public AbstractSpawn {
public:
	LaserSpawn(GroupNode* aGroupNode):AbstractSpawn(aGroupNode){};
	virtual void fire();
  virtual void fire(float aPosX, float aPosY, float aPosZ, float aDirX, float aDirY, float aDirZ);
};
#endif
