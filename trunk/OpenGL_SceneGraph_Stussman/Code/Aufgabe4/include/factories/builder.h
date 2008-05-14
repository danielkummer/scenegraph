#ifndef _BUILDER_H
#define _BUILDER_H

#include "main.h"
#include "nodes/allnodes.h"
#include "planetdefs.h"
#include "actions/actionbase.h"

//for the spaceship builder:
#include "factories/actionfactory.h"

//-------------------------------------------------------//
class Builder{
public:
//  Builder();
  Builder(GroupNode* aRootNode, ActionBase* aAction=NULL);
  ~Builder();
  AbstractNode* getResult();
  AbstractNode* getLast(){ return mLastAdded; }
//  void setRootNode(GroupNode* aNode);

  void buildGroupNode(ActionBase* aAction=NULL);
  void buildTransformSeparator(ActionBase* aAction=NULL);

  void buildSphereNode(double aRadius, int aSlices = 16, int aStacks = 16, GLboolean aUseTexCoord=GL_FALSE, ActionBase* aAction=NULL);
  void buildLineNode(float aVert1X,
                     float aVert1Y, 
                     float aVert1Z, 
                     float aVert2X, 
                     float aVert2Y, 
                     float aVert2Z, 
                     float aWidth=1.0,
                     ActionBase* aAction=NULL);
  void buildTranslationNode(float aX, float aY, float aZ, ActionBase* aAction=NULL);
  void buildRotationNode(float aAngle, float aAxisX, float aAxisY, float aAxisZ, ActionBase* aAction=NULL);
  void buildScaleNode(float aScaleX=1.0f, float aScaleY=1.0f, float aScaleZ=1.0f, ActionBase* aAction=NULL);
  void buildRotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, ActionBase* aAction=NULL);
  void buildLightNode(GLenum aLightNr, ActionBase* aAction=NULL);
  void buildMaterialNode(GLenum aFace, ActionBase* aAction=NULL);
  void buildMaterialNode(GLenum aFace, Material* aMaterial, ActionBase* aAction=NULL);
  void buildColorNode(float aRed, float aGreen, float aBlue, float aAlpha=1.0f, ActionBase* aAction=NULL);
  void buildTextureNode(GLint aTexID, GLenum aTarget=GL_TEXTURE_2D, ActionBase* aAction=NULL);
  void buildTextureNode(GLint aTexID, GLenum aTarget, GLenum aSFactor, GLenum aDFactor, ActionBase* aAction=NULL);
  void buildShadowNode(float* aLightPos, float* aNormal, float* aPointInPlane, float* aColor, ActionBase* aAction=NULL);
  void buildToggleNode(ActionBase* aAction=NULL);
  void buildLineNode(float aVert1X, float aVert1Y, float aVert1Z, float aVert2X, float aVert2Y, float aVert2Z, float aWidth, float ,ActionBase* aAction=NULL);
  void buildPolygonObjectNode(char* objFileName, char* matFileName, ActionBase* aAction=NULL);
  void buildMoveNode(std::vector<ActionBase*> aActions = std::vector<ActionBase*>());
  void buildCamNode(std::vector<ActionBase*> aActions);
  void append(ActionBase* aAction, AbstractNode* aNode);

private:

  GroupNode* mCurrent;
  AbstractNode* mLastAdded;
};
//-------------------------------------------------------//
/*
class Director{
public:
  AbstractNode* createPlanet(PlanetDef* aPlanterDef, AbstractNode** aNodelist=NULL, unsigned aNodeCount=0);
  AbstractNode* createSun();
  AbstractNode* createSolarSystem();
  AbstractNode* createAxis(float aLength=1.0);
  AbstractNode* createSaturnRings(PlanetDef* aPlanetDef, char* aTextureName, float aInnerFactor=1.5f, float aOuterFactor=2.5f);
private:
  Builder mBuilder;

};
*/
//-------------------------------------------------------//


#endif

