#ifndef POLYGONOBJECTNODE_H_
#define POLYGONOBJECTNODE_H_


#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include "nodes/abstractnode.h"
#include "factories/ObjLoader.h"

class PolygonObjectNode:public AbstractNode{
public:
  PolygonObjectNode(char* objFileName, char* matFileName);
  virtual void accept(AbstractVisitor &aVisitor);
  virtual ~PolygonObject();

private:
	void loadObjFile(char* objFileName, char* matFileName);	
	int groupcount;
	int groupcounter;
	int* gsize;									// Number of triangles in a group
	GLuint *g_Texture;							// Pointer to a texture array
	group* groups;								// Pointer to an array of groups
	int triangleCount;
};

#endif /*POLYGONOBJECTNODE_H_*/
