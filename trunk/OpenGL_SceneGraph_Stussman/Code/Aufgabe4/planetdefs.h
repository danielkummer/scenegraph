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


class Material{
public:
  Material(){
    set(GL_AMBIENT, 0.0f, 0.0f, 0.0f);
	  set(GL_DIFFUSE, 0.0f, 0.0f, 0.0f);
    set(GL_SPECULAR, 0.0f, 0.0f, 0.0f);
    set(GL_EMISSION, 0.0f, 0.0f, 0.0f);
    set(GL_SHININESS, 0.0f, 0.0f, 0.0f);
	  set(GL_AMBIENT_AND_DIFFUSE,	0.0f, 0.0f, 0.0f);
    ambientAndDiffuse = false;
  }
  float ambient[4];
  float diffuse[4];
  float specular[4];
  float emission[4];
  float shininess[4];
  bool ambientAndDiffuse;
  void set(GLenum aParamName, float a, float b, float c, float d=1.0f){
    switch(aParamName){
      case GL_AMBIENT:
        {
          ambient[0] = a;
          ambient[1] = b;
          ambient[2] = c;
          ambient[3] = d;
        }break;
      case GL_DIFFUSE:
        {
          diffuse[0] = a;
          diffuse[1] = b;
          diffuse[2] = c;
          diffuse[3] = d;
        }break;
      case GL_SPECULAR:
        {
          specular[0] = a;
          specular[1] = b;
          specular[2] = c;
          specular[3] = d;
        }break;
      case GL_EMISSION:
        {
          emission[0] = a;
          emission[1] = b;
          emission[2] = c;
          emission[3] = d;
        }break;
      case GL_SHININESS:
        {
          shininess[0] = a;
          shininess[1] = b;
          shininess[2] = c;
          shininess[3] = d;
        }break;
    }
    ambientAndDiffuse = false;
    if(ambient[0] == diffuse[0] &&
      ambient[1] == diffuse[1] &&
      ambient[2] == diffuse[2] &&
      ambient[3] == diffuse[3]){
      ambientAndDiffuse = true;
    }
  }
};


class PlanetDef{
public:
  PlanetDef(float aDiameter,       // in earths
         float aRotationPeriod, // in earthdays
         float aTilt,           // in degrees
         float aSemiMajorAxis,  // in AU
         float aOrbitPeriod,    // in earthyears
         float aOrbitInclination, // in degrees to suns equator
         char* aTextureName,
         bool aAntiRot=true);  // name of texture to use
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
  Material material;

  bool mAntiRot;
};

class EarthDef:public PlanetDef{
public:
  EarthDef();//:PlanetDef(1.0f, 1.0f, 23.45f, 1.0f, 1.0f, 0.0f, NULL){}
};
class MoonDef:public PlanetDef{
public:
  MoonDef();//:PlanetDef(0.546f, 27.32f, 6.6f, 2.57f, 27.32f, 5.145f, NULL, false){}
};
class MarsDef:public PlanetDef{
public:
  MarsDef();
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