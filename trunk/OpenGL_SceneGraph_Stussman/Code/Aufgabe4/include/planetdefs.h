#ifndef _PLANETDEFS_H
#define _PLANETDEFS_H

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <vector>

#include "material.h"


class PlanetDef{
public:
  PlanetDef(float aDiameter,       // in earths
         float aRotVelocity, 	// in earthdays (360°/rotPeriod)
         float aTilt,           // in degrees
         float aSemiMajorAxis,  // in AU
         float aOrbitPeriod,    // in earthyears
         float aOrbitInclination, // in degrees to suns equator
         const char* aTextureName,
         bool aAntiRot=true,
         float aAlpha=1.0f,
         Material* aMaterial = new DefaultMaterial());  // name of texture to use
  virtual ~PlanetDef();
  // planet
  float radius;
  float rotVelocity;
  float tilt;
  // orbit
  float orbitRadius;
  float orbitVelocity;
  float orbitInclination;
  // texture
  char* textureName;
  // color
  float red;
  float green;
  float blue;
  // material
  Material* material;
  float mAlpha;

  bool mAntiRot;

  std::vector<PlanetDef*> mMoons;
};

class MercuryDef:public PlanetDef{
public:
	MercuryDef();	
};
class VenusDef:public PlanetDef{
public:
  VenusDef();
};
class EarthDef:public PlanetDef{
public:
  EarthDef();
};
class EarthCloudsDef:public PlanetDef{
public:
  EarthCloudsDef();
};
class LunaDef:public PlanetDef{
public:
  LunaDef();
};
class MarsDef:public PlanetDef{
public:
  MarsDef();
};
class JupiterDef:public PlanetDef{
public:
  JupiterDef();
};
class SaturnDef:public PlanetDef{
public:
  SaturnDef();
};
class UranusDef:public PlanetDef{
public:
  UranusDef();
};
class NeptuneDef:public PlanetDef{
public:
  NeptuneDef();
};
class PlutoDef:public PlanetDef{
public:
  PlutoDef();
};
class TitanDef:public PlanetDef{
public:
  TitanDef();
};


class RingDef:public PlanetDef{
public:
  RingDef(PlanetDef* aPlanetDef, const char* aTextureName, float aInnerFactor=1.5f, float aOuterFactor=2.5f);

  float mInnerFactor;
  float mOuterFactor;
//  char* textureName;
  PlanetDef* mPlanetDef;
};

class SunDef:public PlanetDef{
public:
  SunDef();
};

class SunTransDef:public PlanetDef{
public:
  SunTransDef();
};

#endif

// form here: http://www.windows.ucar.edu/tour/link=/our_solar_system/planets_table.html

//                            Mercury Venus   Earth   Mars    Jupiter Saturn  Uranus  Neptune Pluto  Moon
//diameter(Earth=1)           0.382   0.949   1       0.532   11.209  9.44    4.007   3.883   0.180  0.546
//rotationperiod(inEarthdays) 58.65   -243*   1       1.03    0.41    0.44    -0.72*  0.72    -6.38* 27.32
//inclinationofaxis(degrees)  0.0     177.4   23.45   23.98   3.08    26.73   97.92   28.8    122    1.54

//meandistancefromSun(AU)     0.39    0.72    1       1.52    5.20    9.54    19.18   30.06   39.44  0.00257
//orbitalperiod(Earthyears)   0.24    0.62    1       1.88    11.86   29.46   84.01   164.8   247.7  27.32
//orbitinclination(to sun)            0                                                              5.14

//orbitaleccentricity         0.2056  0.0068  0.0167  0.0934  0.0483  0.0560  0.0461  0.0097  0.2482 
//meanorbitalvelocity(km/sec) 47.89   35.03   29.79   24.13   13.06   9.64    6.81    5.43    4.74
//numberofmoons               0       0       1       2       63      59      27      13      3
//rings?                      no      no      no      no      yes     yes     yes     yes     no


