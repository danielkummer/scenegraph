#ifndef _H_CAM
#define _H_CAM

#include "nodes/movenode.h"

// see: http://www.flipcode.com/archives/OpenGL_Camera.shtml

class CamNode:public MoveNode{
public:
  CamNode();
  virtual ~CamNode();

  virtual void accept(AbstractVisitor& aVisitor);


  float mTransform[16];


};



#endif // _H_CAM

