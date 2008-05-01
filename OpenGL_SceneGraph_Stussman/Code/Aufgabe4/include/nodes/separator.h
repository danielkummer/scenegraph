#ifndef _H_SEPARATOR
#define _H_SEPARATOR


#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 


#include "nodes/groupnode.h"

class Separator:public GroupNode{
public:
//  Separator();
//  virtual ~Separator();
  virtual void accept(AbstractVisitor &aVisitor);
};

#endif // _H_SEPARATOR


