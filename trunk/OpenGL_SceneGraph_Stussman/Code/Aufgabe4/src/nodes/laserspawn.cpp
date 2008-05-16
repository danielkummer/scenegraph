#include "nodes/laserspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void LaserSpawn::fire(){
     Builder vBuilder(new DestructorNode(0.2,mGroupNode));
     vBuilder.buildColorNode(0.0f,1.0f,0.0f);
     // TODO: laser texture or 'material' ;-)
     vBuilder.buildLineNode(0,0,0,100,0,0, 4);	
     add(vBuilder.getResult());
}
