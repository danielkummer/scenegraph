#include "nodes/shotspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void ShotSpawn::spawn(){
	Builder vBuilder(new DestructorNode(100.0,mGroupNode));
		vBuilder.buildColorNode(0.8,0,0);
		vBuilder.buildTranslatorNode(0,0,0,1,1,1);
		vBuilder.buildSphereNode(2,20,20,0);	
	add(vBuilder.getResult());
}
