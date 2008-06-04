#include "nodes/billboard.h"


Billboard::Billboard(float aWidth, float aHeight, 
                     float aOffX, float aOffY, float aOffZ):
Quad(aOffX, aOffY, aOffZ), 
mWidth(aWidth), 
mHeight(aHeight)
{
  float vW = mWidth/2.0f;
  float vH = mHeight/2.0f;
  mP1 = SPoint3D(vW, vH, 0);
  mP2 = SPoint3D(-vW, vH, 0);
  mP3 = SPoint3D(-vW, -vH, 0);
  mP4 = SPoint3D(vW, -vH, 0);
}
//----------------------------------------------------------//
Billboard::~Billboard(){

}
//----------------------------------------------------------//
void Billboard::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//
//----------------------------------------------------------//



