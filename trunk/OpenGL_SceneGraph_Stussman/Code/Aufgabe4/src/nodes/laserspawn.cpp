#include "nodes/laserspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void LaserSpawn::fire(){
}
//----------------------------------------------------------//
void LaserSpawn::fire(float aPosX, float aPosY, float aPosZ, float aDirX, float aDirY, float aDirZ){
     Builder vBuilder(new DestructorNode(0.1f,mGroupNode));
     vBuilder.buildColorNode(0.0f,1.0f,0.0f);
     // TODO: laser texture or 'material' ;-)
     vBuilder.buildLineNode(aPosX, aPosY, aPosZ, aPosX+100*aDirX, aPosY+100*aDirY, aPosZ+100*aDirZ, 4);	
     add(vBuilder.getResult());
}