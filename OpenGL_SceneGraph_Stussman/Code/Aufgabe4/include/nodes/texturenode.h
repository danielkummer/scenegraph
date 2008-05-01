#ifndef _H_TEXTURENODE
#define _H_TEXTURENODE


#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 

#include "nodes/abstractnode.h"

class TextureNode:public AbstractNode{
public:
  TextureNode(GLint aTexID, GLenum aTarget=GL_TEXTURE_2D, bool aBlend=false);
  virtual ~TextureNode() { }
  virtual void accept(AbstractVisitor &aVisitor);

  GLenum sfactor;
  GLenum dfactor;
    
  GLuint mTexID;
  GLenum mTarget;
  bool mBlending;
};

#endif // _H_TEXTURENODE


