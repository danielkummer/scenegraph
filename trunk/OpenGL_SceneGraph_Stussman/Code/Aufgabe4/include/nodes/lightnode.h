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

//#include "nodes/abstractnode.h"
#include "nodes/togglenode.h"

class LightNode:public ToggleNode{
public:
  LightNode(GLenum aLightNr);
  LightNode::LightNode(GLenum aLightNr, 
                       float posX, 
                       float posY, 
                       float posZ, 
                       float posW, 
                       float ambA, 
                       float ambB, 
                       float ambC, 
                       float ambD, 
                       float diffA, 
                       float diffB, 
                       float diffC, 
                       float diffD);
  virtual ~LightNode();
  void setParam(GLenum aParamType, float aA, float aB, float aC, float aD);
  virtual void accept(AbstractVisitor &aVisitor);
  void setPos();
  void on();
  void off();
  bool toggle();
private:
  GLenum mLightNr;
  float* mPos;
};

#endif // _H_LIGHTNODE


