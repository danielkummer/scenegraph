#ifndef _H_MATERIALNODE
#define _H_MATERIALNODE

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include <map>
#include "assert.h"

#include "material.h"
#include "nodes/abstractnode.h"
#include "visitors/abstractvisitor.h"


class MaterialNode:public AbstractNode{
public:
  MaterialNode(GLenum aFace);
  MaterialNode(GLenum aFace, Material* aMaterial);
  virtual ~MaterialNode();
  virtual void accept(AbstractVisitor &aVisitor);
  void setParam(GLenum aParamName, float aV1, float aV2, float aV3, float aV4);
  void setParam(GLenum aParamName, float* aValues3);

  std::map<GLenum, float*> mParams;
  GLenum mFace;
};

#endif // _H_MATERIALNODE


