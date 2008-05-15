#ifndef _SHOTSPAWN_H
#define _SHOTSPAWN_H
#include "nodes/abstractspawn.h"

class ShotSpawn: public AbstractSpawn {
public:
	virtual void spawn();
	ShotSpawn(GroupNode* aGroupNode):AbstractSpawn(aGroupNode){};
};
#endif
