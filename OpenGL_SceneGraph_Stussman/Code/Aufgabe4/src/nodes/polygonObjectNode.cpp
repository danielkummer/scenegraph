#include "nodes/polygonObjectNode.h"


PolygonObjectNode::PolygonObjectNode(char* objFileName, char* matFileName):AbstractNode(){
  groupcount		=0;										// Number of groups in ".obj"-file							
	triangleCount	=0;									// Number of Triangles
	groupcounter	=0;										// A counter to go trough the groups
	groups 			  =0;
	PolygonObjectNode::loadObjFile( objFileName, matFileName );		
}
//-------------------------------------------------------//
PolygonObjectNode::~PolygonObjectNode() {
  for(int i=0; i<groupcount; i++){
    delete[] groups->triangle;
  }
  delete[] groups;
  delete[] gsize;
}
//-------------------------------------------------------//
inline void PolygonObjectNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void PolygonObjectNode::loadObjFile( char* objFileName, char* matFileName )// objFileName contains the filename of the ".obj"-file
{														// matFileName contains the filename of the corresponding ".mtl"-file

	// initialize objloader and arrays
	///////////////////////////////////////////////
	TextureManager* texMan = TextureManager::getReference();
	
	ObjLoader* obj = new ObjLoader();					// create an instance of ObjLoader
	obj->open(objFileName,matFileName);					// open the Files, this will initialise some public variables with useful values

	gsize = new int[obj->numGeom];						// create an array for the sizes of the Groups (number of triangles) using a variable from the loader
	groups = new group[obj->numGeom];					// create an array to hold the definitions of the groups with the same size 

	obj->groupsizes(&gsize[0]);							// get the number of polygons of each group

	triangleCount = obj->numTriangles;					// get the number of triangles used for the object		
	groupcount = obj->numGeom;							// get the number of groups
	
//	g_Texture = new GLuint[groupcount];					// create a texture-array for the materials
	
	for (int g=0; g<groupcount; g++)					
	{
		groups[g].triangle = new triang[gsize[g]];		// create the arrays to store the triangle definitions into
		groups[g].size = gsize[g];						// and set the number of triangles for each group
		groups[g].textureName = 0;
	}

	// load all object groups
	// (coordinates, materials and textures)
	///////////////////////////////////////////////

	for (groupcounter = 0; groupcounter<groupcount; groupcounter++) {	// do the following for each group
														//
		// (re-)setting variables						//
		///////////////////////////////////////////		//
														//
//		g_Texture[groupcounter]=0;						// initialize the texture for this group to zero
														//
		// load all values of a group					//
		///////////////////////////////////////////     //
														//
		obj->load(										// Load an object-group (material definition, triangles, texture-filename
				groupcounter+1,							// First parameter: group number of the group you want to load
				groups );								// Second parameter: group-array to store the loaded data
														//
		// assigning texture							//
		///////////////////////////////////////////		//
		if(groups[groupcounter].textureName!=0)			// && strlen(groups[groupcounter].textureName) > 1)
		{												//
			/*texMan->createTexture(								//  create the texture from this bitmap-file
				g_Texture,								//  texture-array to store the texture
				groups[groupcounter].textureName,		//  filename of the texture (CreateTexture() will only load BMP's!)
				groupcounter);							//  groupnumber*/
			groups[groupcounter].textureID = texMan->createTexture(groups[groupcounter].textureName);
		}												//	
														//
	}
	
	// closing the files
	///////////////////////////////////////////////

	obj->close();										// After all data is loaded close the files
  delete obj; 											// Free the beast!!

}
//-------------------------------------------------------//
