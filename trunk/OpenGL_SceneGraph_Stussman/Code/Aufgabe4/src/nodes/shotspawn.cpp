#include "nodes/shotspawn.h"
#include "factories/builder.h"
#include "nodes/allnodes.h"

void ShotSpawn::fire(){
  //Builder vBuilder(new TransformSeparator());
		//vBuilder.buildColorNode(0.8,0,0);
		//vBuilder.buildTranslatorNode(0,0,0,20,20,20);
		//vBuilder.buildSphereNode(0.2,20,20,0);	
  //  DestructorNode* vDestr = new DestructorNode(5.0,mGroupNode);
  //  vDestr->add(vBuilder.getResult());
  //  add( vDestr );
}


void ShotSpawn::fire(float aPosX, float aPosY, float aPosZ, float aDirX, float aDirY, float aDirZ){
  Builder vBuilder(new TransformSeparator());
		vBuilder.buildColorNode(0.8f,0,0);
		vBuilder.buildTranslatorNode(aPosX, aPosY, aPosZ, 20.0f*aDirX, 20.0f*aDirY, 20.0f*aDirZ);
		vBuilder.buildSphereNode(0.2f,20,20,0);	
    DestructorNode* vDestr = new DestructorNode(15.0,mGroupNode);
    vDestr->add(vBuilder.getResult());
    add( vDestr );
}
