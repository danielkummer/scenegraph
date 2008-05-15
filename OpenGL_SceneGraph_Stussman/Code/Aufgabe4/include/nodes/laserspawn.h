#ifndef _LASERSPAWN_H
#define _LASERSPAWN_H
#include "nodes/abstractspawn.h"

class LaserSpawn: public AbstractSpawn {
public:
	virtual void fire();
	LaserSpawn(GroupNode* aGroupNode):AbstractSpawn(aGroupNode){};
};
#endif
