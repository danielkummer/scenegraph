#ifndef _H_SPHERENODE
#define _H_SPHERENODE

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include "nodes/abstractnode.h"

class SphereNode:public AbstractNode{
public:
  SphereNode(double aRadius, int aSlices = 16, int aStacks = 16, GLboolean aUseTexCoord=GL_FALSE);
  virtual ~SphereNode();
  virtual void accept(AbstractVisitor &aVisitor);

  static GLUquadric* mQuadric;
  double mRadius;
  int mSlices;
  int mStacks;
  GLboolean mUseTexCoord;
};

#endif // _H_SPHERENODE


