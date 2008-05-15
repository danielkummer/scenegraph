#include "nodes/laserspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void LaserSpawn::fire(){
     Builder vBuilder(new DestructorNode(100.0,mGroupNode));
     vBuilder.buildColorNode(0.8,1,1);
     vBuilder.buildLineNode(0,0,0,10,0,0);	
     add(vBuilder.getResult());
}
