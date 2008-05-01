#include "planetdefs.h"

//HACK: remove this HACK!! -> change how PlanetDef works
/*#ifndef WIN32
#define INFINITE 0xFFFFFFFF
#endif*/



PlanetDef::PlanetDef(float aDiameter,       // in earths
               float aRotVelocity, // in earthdays
               float aTilt,           // in degrees
               float aSemiMajorAxis,  // in AU
               float aOrbitVelocity,    // in earthyears
               float aOrbitInclination, // in degrees to suns equator
               const char* aTextureName,
               bool aAntiRot,
               Material* aMaterial):material(aMaterial){
  radius = aDiameter/2.0f * 0.50f;
  //rotVelocity = 360.0f/aRotationPeriod;
  rotVelocity = aRotVelocity;
  tilt = aTilt;
  orbitRadius = aSemiMajorAxis * 10.0f;
  orbitInclination = aOrbitInclination;
  orbitVelocity = aOrbitVelocity * 360.0f/365.25f;
  textureName = strdup(aTextureName);
  mAntiRot = aAntiRot;
}
PlanetDef::~PlanetDef(){
  free(textureName);
  for(unsigned i=0; i<mMoons.size(); i++){
    delete mMoons[i];
  }
  if(NULL != material){
    delete material;
    material = NULL;
  }
}

//Rings
RingDef::RingDef(PlanetDef* aPlanetDef, const char* aTextureName, float aInnerFactor, float aOuterFactor):
PlanetDef(0, 0, 0, 0, 0, 0, aTextureName){
  mPlanetDef = aPlanetDef;
  mInnerFactor = aInnerFactor;
  mOuterFactor = aOuterFactor;
}


                                //diameter  RotVelocity  tilt SemiMajorAxis aOrbitPeriod OrbitIncl        TextureName         aAntiRot
                                //earths     earthdays    deg      AU        earthyears    deg to sunequator
//Moons
LunaDef::LunaDef():PlanetDef(       0.546f,    0.0f,    1.54f,    0.257f,     13.369f,    5.145f, "Textures/Moon.bmp", false){}
TitanDef::TitanDef():PlanetDef(     0.404f,    0.0f,    0.34854f, 0.832f,    0.004738f,   0.0f,   "Textures/Titan.bmp", false){}
//Planets
MercuryDef::MercuryDef():PlanetDef( 0.382f,    6.13f,   0.0f,     0.39f,       4.166f,    0.0f,   "Textures/Mercury.bmp"){}
VenusDef::VenusDef():PlanetDef(     0.949f,   -1.48f, 177.4f,     0.72f,       1.6129f,   0.0f,   "Textures/Venus.bmp"){}
EarthDef::EarthDef():PlanetDef(     1.0f,    360.0f,   23.45f,    1.0f,        1.0f,      0.0f,   "Textures/Earth.bmp"){mMoons.push_back(new LunaDef());}
MarsDef::MarsDef():PlanetDef(       0.532f,  349.51f,  23.98f,    1.52f,       0.5319f,   0.0f,   "Textures/Mars.bmp"){}
JupiterDef::JupiterDef():PlanetDef(11.209f,  878.04f,   3.08f,    5.20f,      0.08432f,   0.0f,   "Textures/Jupiter.bmp"){}
SaturnDef::SaturnDef():PlanetDef(   9.44f,   818.18f,  26.73f,    9.45f,      0.03394f,   0.0f,   "Textures/Saturn.bmp"){
  mMoons.push_back(new TitanDef());
  mMoons.push_back(new RingDef(this, "Textures/Saturnring.bmp"));
}
UranusDef::UranusDef():PlanetDef(   4.007f, -500.0f,   97.92f,   19.18f,      0.0119033f, 0.0f,   "Textures/Uranus.bmp"){}
NeptuneDef::NeptuneDef():PlanetDef( 3.883f,  500.0f,   28.8f,    30.06f,     0.006067f,   0.0f,   "Textures/Neptune.bmp"){}
PlutoDef::PlutoDef():PlanetDef(     0.180f,  -56.42f, 122.0f,    39.44f,     0.00403714f, 0.0f,   "Textures/Pluto.bmp"){}

SunDef::SunDef():PlanetDef(         1.0f,     0.00024f, 0.0f,     0.0f,        0.0f,      0.0f,   "Textures/Sun.bmp", false, new SunMaterial()){
  mMoons.push_back(new MercuryDef());
  mMoons.push_back(new VenusDef());
  mMoons.push_back(new EarthDef());
  mMoons.push_back(new MarsDef());
  mMoons.push_back(new JupiterDef());
  mMoons.push_back(new SaturnDef());
  mMoons.push_back(new UranusDef());
  mMoons.push_back(new NeptuneDef());
  mMoons.push_back(new PlutoDef());
}




// form here: http://www.windows.ucar.edu/tour/link=/our_solar_system/planets_table.html

//                            Mercury Venus   Earth   Mars    Jupiter Saturn  Uranus    Neptune   Pluto       Moon
//diameter(Earth=1)           0.382   0.949   1       0.532   11.209  9.44    4.007     3.883     0.180       0.546
//rotationperiod(inEarthdays) 58.65   -243*   1       1.03    0.41    0.44    -0.72*    0.72      -6.38*      0
//inclinationofaxis(degrees)  0.0     177.4   23.45   23.98   3.08    26.73   97.92     28.8      122         1.54

//meandistancefromSun(AU)     0.39    0.72    1       1.52    5.20    9.54    19.18     30.06     39.44       0.00257
//orbitalperiod(Earthyears)   0.24    0.62    1       1.88    11.86   29.46   84.01     164.8     247.7       0.074799(27.32 days)
//                            4.166   1.6129  1       0.5319  0.08432 0.03394 0.0119033 0.006067  0.00403714  13.369
//orbitinclination(to sun)            0                                                                       5.14


//orbitaleccentricity         0.2056  0.0068  0.0167  0.0934  0.0483  0.0560  0.0461    0.0097    0.2482 
//meanorbitalvelocity(km/sec) 47.89   35.03   29.79   24.13   13.06   9.64    6.81      5.43      4.74
//numberofmoons               0       0       1       2       63      59      27        13        3
//rings?                      no      no      no      no      yes     yes     yes       yes       no




