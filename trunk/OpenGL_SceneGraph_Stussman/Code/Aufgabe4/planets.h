#ifndef _PLANETS_H
#define _PLANETS_H

//-------------------------------------------------------//
struct Planet{
  Planet(float aRadius, 
         float aRotVel, 
         float aTilt, 
         float aOrbitRadius, 
         float aVel, 
         float aInclination, 
         char* aTextureName, 
         unsigned aTextureID, 
         float aOffsetAngle, 
         float* aOffsetAxis){
    mPlanetRadius = aRadius;
    mPlanetVel = aRotVel;
    mPlanetTilt = aTilt;

    mOrbitRadius = aOrbitRadius;
    mOrbitVel = aVel;
    mOrbitInclination = aInclination;

    mTextureName = aTextureName;
    mTextureID = aTextureID;
    mOffsetAngle = aOffsetAngle;
    mOffsetAxis = aOffsetAxis;
  }
  ~Planet(){ delete[] mOffsetAxis; }
  // planet/physical characteristic
  float mPlanetRadius;
  float mPlanetVel;
  float mPlanetTilt;
  // orbital parameters
  float mOrbitRadius;
  float mOrbitVel;
  float mOrbitInclination;
  char* mTextureName;
  unsigned mTextureID;
  float mOffsetAngle;
  float* mOffsetAxis[3];
};
//-------------------------------------------------------//



#endif