#include "nodes/shotspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void ShotSpawn::fire(){
  Builder vBuilder(new TransformSeparator());
		vBuilder.buildColorNode(0.8,0,0);
		vBuilder.buildTranslatorNode(0,0,0,20,20,20);
		vBuilder.buildSphereNode(0.2,20,20,0);	
    DestructorNode* vDestr = new DestructorNode(5.0,mGroupNode);
    vDestr->add(vBuilder.getResult());
    add( vDestr );
}
