#ifndef _H_SHADOWNODE
#define _H_SHADOWNODE

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"

class ShadowNode:public AbstractNode{
public:
  ShadowNode(float* aLightPos, float* aNormal, float* aPointInPlane, float* aColor);
  virtual ~ShadowNode();
  virtual void accept(AbstractVisitor &aVisitor);
  void setNodeToShadow(AbstractNode* aNode);
  AbstractNode* getNodeToShadow();

  void draw(AbstractVisitor &aVisitor);

private:
  void buildShadowMatrix(float* shadowMatrix, float* lightPos, float* normal, float* p);
  AbstractNode* mNode;
  float* mLightPos;
  float* mNormal;
  float* mPointInPlane;
  float* mColor;
};

#endif // _H_SHADOWNODE


