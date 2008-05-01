#ifndef _H_TRANSFORMSEPARATOR
#define _H_TRANSFORMSEPARATOR

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include "nodes/groupnode.h"

class TransformSeparator:public GroupNode{
public:
  virtual void accept(AbstractVisitor &aVisitor);
};

#endif // _H_TRANSFORMSEPARATOR


