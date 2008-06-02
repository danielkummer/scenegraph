#ifndef _H_BILLBOARD
#define _H_BILLBOARD

#include "nodes/quad.h"


class Billboard:public Quad{
public:
  Billboard(float aWidth, float aHeight,
            float aPosX, float aPosY, float aPosZ,
            float aOffX=0, float aOffY=0, float aOffZ=0);
  virtual ~Billboard();

  virtual void accept(AbstractVisitor &aVisitor);


  float mWidth;
  float mHeight;
};





#endif // _H_BILLBOARD

