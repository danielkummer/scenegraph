#include "planetdefs.h"







PlanetDef::PlanetDef(float aDiameter,       // in earths
               float aRotationPeriod, // in earthdays
               float aTilt,           // in degrees
               float aSemiMajorAxis,  // in AU
               float aOrbitPeriod,    // in earthyears
               float aOrbitInclination, // in degrees to suns equator
               char* aTextureName,
               bool aAntiRot){
  radius = aDiameter/2.0f * 0.50f;
  rotVelocity = 360.0f/aRotationPeriod;
  tilt = aTilt;
  orbitRadius = aSemiMajorAxis * 10.0f;
  orbitInclination = aOrbitInclination;
  orbitVelocity = 1.0f/aOrbitPeriod * 360.0f/365.25f;
  textureName = aTextureName;
  mAntiRot = aAntiRot;
}


EarthDef::EarthDef():PlanetDef(1.0f, 1.0f, 23.45f, 1.0f, 1.0f, 0.0f, "Textures/Earth.bmp"){}
MoonDef::MoonDef():PlanetDef(0.546f, (float)INFINITE, 1.54f, 0.257f, 0.0747f, 5.145f, "Textures/Moon.bmp", false){}
MarsDef::MarsDef():PlanetDef(0.532f, 1.03f, 23.98f, 1.52f, 1.88f, 0.0f, "Textures/Mars.bmp"){}



