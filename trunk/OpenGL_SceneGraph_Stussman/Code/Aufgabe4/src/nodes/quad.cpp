#include "nodes/Quad.h"
#include <math.h>

//TODO: idea: orientationNode and orientator: given an orientation, all after
// this node would have this orientation
// orientator: object after this node would always point to camera

SPoint3D::SPoint3D():x(0), y(0), z(0){}
//-------------------------------------------------------//
SPoint3D::SPoint3D(float aX, float aY, float aZ){
    x = aX; 
    y = aY;
    z = aZ; 
  }
//-------------------------------------------------------//
inline SPoint3D SPoint3D::cross(SPoint3D other){
  return SPoint3D(y * other.z - other.y * z,
                  z * other.x - other.z * x,
                  x * other.y - other.x * y);
}
//-------------------------------------------------------//
inline SPoint3D SPoint3D::normalize(){
  float vL = sqrt(x * x + y * y + z * z);
  if(0!=vL){
    x /= vL;
    y /= vL;
    z /= vL;
  }
  return *this;
}
//-------------------------------------------------------//
Quad::Quad(float aOffX, float aOffY, float aOffZ){
  mOffset = SPoint3D(aOffX, aOffY, aOffZ);
  mModelMatrix[12] += aOffX;
  mModelMatrix[13] += aOffY;
  mModelMatrix[14] += aOffZ;
  mModelMatrix[0] = 1;
  mModelMatrix[5] = 1;
  mModelMatrix[10] = 1;
  mModelMatrix[15] = 1;

  // counterclockwise, n shoud be z+
  mP1 = SPoint3D(1, 1, 0);
  mP2 = SPoint3D(-1, 1, 0);
  mP3 = SPoint3D(-1, -1, 0);
  mP4 = SPoint3D(1, -1, 0);
}
//-------------------------------------------------------//
Quad::Quad(float aNormX, float aNormY, float aNormZ,
           float aUpX, float aUpY, float aUpZ,
           float aOffX, float aOffY, float aOffZ){

  // counterclockwise, n shoud be z+
  mP1 = SPoint3D(1, 1, 0);
  mP2 = SPoint3D(-1, 1, 0);
  mP3 = SPoint3D(-1, -1, 0);
  mP4 = SPoint3D(1, -1, 0);

  mModelMatrix[12] += aOffX;
  mModelMatrix[13] += aOffY;
  mModelMatrix[14] +=  aOffZ;
  mModelMatrix[0] = 1;
  mModelMatrix[5] = 1;
  mModelMatrix[10] = 1;
  mModelMatrix[15] = 1;
  // normal is the local z axis
  mNormal = SPoint3D(aNormX, aNormY, aNormZ);
  mModelMatrix [8] = aNormX;
  mModelMatrix [9] = aNormY;
  mModelMatrix[10] = aNormZ;

  SPoint3D vUp = SPoint3D(aUpX, aUpY, aUpZ).normalize();
  SPoint3D vXAxis = vUp.cross(mNormal).normalize();
  SPoint3D vYAxis = mNormal.cross(vXAxis).normalize();

  mModelMatrix[0] = vXAxis.x;
  mModelMatrix[1] = vXAxis.y;
  mModelMatrix[2] = vXAxis.z;

  mModelMatrix[4] = vYAxis.x;
  mModelMatrix[5] = vYAxis.y;
  mModelMatrix[6] = vYAxis.z;

  
}
//-------------------------------------------------------//
Quad::Quad(float aWidth, float aHeight,
           float aNormX, float aNormY, float aNormZ,
           float aUpX, float aUpY, float aUpZ,
           float aOffX, float aOffY, float aOffZ){

  // counterclockwise, n shoud be z+
  float vW = aWidth/2;
  float vH = aHeight/2;
  mP1 = SPoint3D(vW, vH, 0);
  mP2 = SPoint3D(-vW, vH, 0);
  mP3 = SPoint3D(-vW, -vH, 0);
  mP4 = SPoint3D(vW, -vH, 0);

  mModelMatrix[12] += aOffX;
  mModelMatrix[13] += aOffY;
  mModelMatrix[14] += aOffZ;
  mModelMatrix[0] = 1;
  mModelMatrix[5] = 1;
  mModelMatrix[10] = 1;
  mModelMatrix[15] = 1;
  // normal is the local z axis
  mNormal = SPoint3D(aNormX, aNormY, aNormZ);
  mModelMatrix [8] = aNormX;
  mModelMatrix [9] = aNormY;
  mModelMatrix[10] = aNormZ;

  SPoint3D vUp = SPoint3D(aUpX, aUpY, aUpZ).normalize();
  SPoint3D vXAxis = vUp.cross(mNormal).normalize();
  SPoint3D vYAxis = mNormal.cross(vXAxis).normalize();

  mModelMatrix[0] = vXAxis.x;
  mModelMatrix[1] = vXAxis.y;
  mModelMatrix[2] = vXAxis.z;

  mModelMatrix[4] = vYAxis.x;
  mModelMatrix[5] = vYAxis.y;
  mModelMatrix[6] = vYAxis.z;

  
}


//-------------------------------------------------------//
Quad::Quad(float aP1X, float aP1Y, float aP1Z, 
           float aP2X, float aP2Y, float aP2Z, 
           float aP3X, float aP3Y, float aP3Z, 
           float aP4X, float aP4Y, float aP4Z, 
           float aOffX, float aOffY, float aOffZ){
  mOffset = SPoint3D(aOffX, aOffY, aOffZ);
  mP1 = SPoint3D(aP1X, aP1Y, aP1Z);
  mP2 = SPoint3D(aP2X, aP2Y, aP2Z);
  mP3 = SPoint3D(aP3X, aP3Y, aP3Z);
  mP4 = SPoint3D(aP4X, aP4Y, aP4Z);
  mModelMatrix[12] += aOffX;
  mModelMatrix[13] += aOffY;
  mModelMatrix[14] += aOffZ;
  mModelMatrix[0] = 1;
  mModelMatrix[5] = 1;
  mModelMatrix[10] = 1;
  mModelMatrix[15] = 1;
}
//-------------------------------------------------------//
Quad::Quad(float aP1X, float aP1Y, float aP1Z, 
           float aP2X, float aP2Y, float aP2Z, 
           float aP3X, float aP3Y, float aP3Z, 
           float aP4X, float aP4Y, float aP4Z, 
           float aNormX, float aNormY, float aNormZ,
           float aUpX, float aUpY, float aUpZ,
           float aOffX, float aOffY, float aOffZ){
  mP1 = SPoint3D(aP1X, aP1Y, aP1Z);
  mP2 = SPoint3D(aP2X, aP2Y, aP2Z);
  mP3 = SPoint3D(aP3X, aP3Y, aP3Z);
  mP4 = SPoint3D(aP4X, aP4Y, aP4Z);
//0 4  8 12
//1 5  9 13
//2 6 10 14
//3 7 11 15

  mModelMatrix[12] += aOffX;
  mModelMatrix[13] += aOffY;
  mModelMatrix[14] += aOffZ;
  mModelMatrix[0] = 1;
  mModelMatrix[5] = 1;
  mModelMatrix[10] = 1;
  mModelMatrix[15] = 1;
  // normal is the local z axis
  mNormal = SPoint3D(aNormX, aNormY, aNormZ);
  mModelMatrix [8] = aNormX;
  mModelMatrix [9] = aNormY;
  mModelMatrix[10] = aNormZ;

  SPoint3D vUp = SPoint3D(aUpX, aUpY, aUpZ).normalize();
  SPoint3D vXAxis = vUp.cross(mNormal).normalize();
  SPoint3D vYAxis = mNormal.cross(vXAxis).normalize();

  mModelMatrix[0] = vXAxis.x;
  mModelMatrix[1] = vXAxis.y;
  mModelMatrix[2] = vXAxis.z;

  mModelMatrix[4] = vYAxis.x;
  mModelMatrix[5] = vYAxis.y;
  mModelMatrix[6] = vYAxis.z;

}
//-------------------------------------------------------//
Quad::~Quad(){
}
//-------------------------------------------------------//
void Quad::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//

