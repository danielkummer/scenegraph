#include "nodes/laserspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void LaserSpawn::fire(){
}
//----------------------------------------------------------//
void LaserSpawn::fire(float aPosX, float aPosY, float aPosZ, float aDirX, float aDirY, float aDirZ){
     Builder vBuilder(new DestructorNode(15.0f,mGroupNode));
     Builder vB(new TransformSeparator(), NULL);
     vB.buildTranslatorNode(aPosX-4*aDirX, aPosY-4*aDirY, aPosZ-4*aDirZ, 100*aDirX, 100*aDirY, 100*aDirZ, NULL);
     vB.buildColorNode(0.0f,1.0f,0.0f);
     // TODO: laser texture or 'material' ;-)
     vB.buildLineNode(0, 0, 0, 10*aDirX, 10*aDirY, 10*aDirZ, 2);
     vB.getLast()->mCollidable = 3;
     vBuilder.append(NULL, vB.getResult());
     add(vBuilder.getResult());
}