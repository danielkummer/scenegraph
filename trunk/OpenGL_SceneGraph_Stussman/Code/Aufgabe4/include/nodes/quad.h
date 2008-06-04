#ifndef _H_Quad_
#define _H_Quad_

#include "nodes/abstractnode.h"

struct SPoint3D{
  SPoint3D();
  SPoint3D(float aX, float aY, float aZ);
  float x, y, z;
  SPoint3D cross(SPoint3D other);
  SPoint3D normalize();
};

class Quad: public AbstractNode{
public:
  Quad(float aOffX=0, float aOffY=0, float aOffZ=0);
  Quad(float aNormX, float aNormY, float aNormZ,
       float aUpX, float aUpY, float aUpZ,
       float aOffX, float aOffY, float aOffZ);
  Quad(float aWidth, float aHeight,
       float aNormX, float aNormY, float aNormZ,
       float aUpX, float aUpY, float aUpZ,
       float aOffX=0, float aOffY=0, float aOffZ=0);
  Quad(float aP1X, float aP1Y, float aP1Z,
       float aP2X, float aP2Y, float aP2Z,
       float aP3X, float aP3Y, float aP3Z,
       float aP4X, float aP4Y, float aP4Z,
       float aOffX=0, float aOffY=0, float aOffZ=0);
  Quad(float aP1X, float aP1Y, float aP1Z,
       float aP2X, float aP2Y, float aP2Z,
       float aP3X, float aP3Y, float aP3Z,
       float aP4X, float aP4Y, float aP4Z,
       float aNormX, float aNormY, float aNormZ,
       float aUpX, float aUpY, float aUpZ,
       float aOffX=0, float aOffY=0, float aOffZ=0);
  virtual ~Quad();

  virtual void accept(AbstractVisitor &aVisitor);


  SPoint3D mNormal;
  SPoint3D mOffset;
  SPoint3D mP1;
  SPoint3D mP2;
  SPoint3D mP3;
  SPoint3D mP4;

};


#endif // _H_Quad_


