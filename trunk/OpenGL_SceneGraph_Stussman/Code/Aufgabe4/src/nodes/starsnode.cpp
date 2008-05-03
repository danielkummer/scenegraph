#include "nodes/starsnode.h"


//-------------------------------------------------------//
inline float randf(){
  return float(rand()/(float)RAND_MAX);
}
//-------------------------------------------------------//
//-------------------------------------------------------//

StarsNode::StarsNode(float aRadiusMin, float aDeltaR, unsigned aNumStars):
mRadiusMin(aRadiusMin), mDeltaR(aDeltaR), mNumStars(aNumStars)
{ 
  mVertices = new float[3*aNumStars];
  mSizes = new float[aNumStars];
  float vRadius;
  float x, y, z;
  float alpha;
  float beta;
/*  for(unsigned i=0; i<mNumStars; i++){
    vRadius = mRadiusMin + mDeltaR * randf();
    alpha = 1.0f *  (float)M_PI * randf();
    beta = 2.5f * (float)M_PI * randf();
    x = vRadius;
    y = 0.0f;
    z = 0.0f;

    x = vRadius * sin(beta) * cos(alpha);// + y * sin(alpha);
    y = vRadius * sin(beta) * sin(alpha);// + y * cos(alpha);
    z = vRadius * cos(beta);

//    float tx = x * cos(beta);
//    float tz = x * sin(beta);

    mVertices[3 * i] = x;
    mVertices[3 * i + 1] = y;
    mVertices[3 * i + 2] = z;
    mSizes[i] = randf() * 1.5;
  }*/
  float vRadiusMax = aRadiusMin + aDeltaR;
  unsigned vNum = 0;
  while(aNumStars > vNum){
    x = vRadiusMax * (2 * randf() - 1.0f);
    y = vRadiusMax * (2 * randf() - 1.0f);
    z = vRadiusMax * (2 * randf() - 1.0f);
    float vSqRad = x*x + y*y + z*z;
    if ( aRadiusMin * aRadiusMin < vSqRad && vSqRad < vRadiusMax * vRadiusMax){
      mVertices[3 * vNum] = x;
      mVertices[3 * vNum + 1] = y;
      mVertices[3 * vNum + 2] = z;
      mSizes[vNum] = randf() * 1.51f;
      vNum++;
    }

  }
}
//-------------------------------------------------------//
StarsNode::~StarsNode(){ 
  delete[] mVertices; 
  delete[] mSizes;
}
//-------------------------------------------------------//

inline void StarsNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}

//-------------------------------------------------------//



