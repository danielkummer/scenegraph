#include "material.h"





//-------------------------------------------------------//
Material::Material(){
    set(GL_AMBIENT, 0.0f, 0.0f, 0.0f);
	  set(GL_DIFFUSE, 0.0f, 0.0f, 0.0f);
    set(GL_SPECULAR, 0.0f, 0.0f, 0.0f);
    set(GL_EMISSION, 0.0f, 0.0f, 0.0f);
    set(GL_SHININESS, 0.0f, 0.0f, 0.0f);
	  set(GL_AMBIENT_AND_DIFFUSE,	0.0f, 0.0f, 0.0f);
    ambientAndDiffuse = false;
  }
//-------------------------------------------------------//
void Material::set(GLenum aParamName, float a, float b, float c, float d){
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
//-------------------------------------------------------//
SunMaterial::SunMaterial():Material(){
  set(GL_EMISSION, 0.5, 0.5, 0.5);
  set(GL_COLOR, 1, 1, 0);
}
//-------------------------------------------------------//
DefaultMaterial::DefaultMaterial():Material(){
  set(GL_COLOR, 1, 1, 1);
}





