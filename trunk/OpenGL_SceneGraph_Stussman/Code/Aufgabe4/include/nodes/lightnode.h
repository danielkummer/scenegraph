#ifndef _H_LIGHTNODE
#define _H_LIGHTNODE

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include "nodes/abstractnode.h"

class LightNode:public AbstractNode{
public:
  LightNode(GLenum aLightNr);
  virtual ~LightNode();
  void setParam(GLenum aParamType, float aA, float aB, float aC, float aD);
  virtual void accept(AbstractVisitor &aVisitor);
  void setPos();
  void on();
  void off();
  void toggle();
private:
  GLenum mLightNr;
  float* mPos;
};

#endif // _H_LIGHTNODE


