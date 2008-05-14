#ifndef _H_BILLBOARD
#define _H_BILLBOARD

#include "nodes/abstractnode.h"


class Billboard:public AbstractNode{
public:
  Billboard(float aWidth, 
            float aHeight,
            float aNormX,
            float aNormY,
            float aNormZ,
            int aTexID);
  virtual ~Billboard();

  virtual void accept(AbstractVisitor &aVisitor);


  float mWidth;
  float mHeight;
  float mNormX;
  float mNormY;
  float mNormZ;
  int mTexID;
};





#endif // _H_BILLBOARD

