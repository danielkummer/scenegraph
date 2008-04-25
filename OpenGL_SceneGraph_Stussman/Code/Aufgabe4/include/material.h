#ifndef _MATERIAL_H
#define _MATERIAL_H

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
  Material();
  float ambient[4];
  float diffuse[4];
  float specular[4];
  float emission[4];
  float shininess[4];
  bool ambientAndDiffuse;
  void set(GLenum aParamName, float a, float b, float c, float d=1.0f);
};


class SunMaterial:public Material{
public:
  SunMaterial();
};


class DefaultMaterial:public Material{
public:
  DefaultMaterial();
};

#endif // _MATERIAL_H

