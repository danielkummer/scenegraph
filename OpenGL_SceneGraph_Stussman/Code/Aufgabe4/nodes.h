#ifndef _NODES_H
#define _NODES_H

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <vector>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include "clock.h"

class AbstractVisitor;




//-------------------------------------------------------//
class AbstractNode{
public:
  AbstractNode():mRefCount(0){ }
  virtual ~AbstractNode() { }
  void ref();
  void unref();
  virtual void accept(AbstractVisitor &) = 0;

private:
  int mRefCount;
};
//-------------------------------------------------------//
/**** Grouping *****/
class GroupNode:public AbstractNode{
public:
  virtual ~GroupNode();
  virtual void add(AbstractNode* aNode);
  virtual void remove(AbstractNode* aNode);
  virtual void clear();
  virtual void accept(AbstractVisitor &aVisitor);
protected:
  virtual void visitChildren(AbstractVisitor &aVisitor);
  std::vector<AbstractNode*> mChildren;
};
//-------------------------------------------------------//
class TransformSeparator:public GroupNode{
public:
  virtual void accept(AbstractVisitor &aVisitor);
};
//-------------------------------------------------------//
class ToggleNode:public GroupNode{
public:
//  ToggleNode():GroupNode(), mState(true) { }
  bool isOn() { return mState; }
  bool toggle(); // return new state
  void on() { mState = true; }
  void off() { mState = false; }
  virtual void accept(AbstractVisitor &aVisitor);

private:
  bool mState;
 
};
//-------------------------------------------------------//
#define SWITCH_NONE (-1)

class SwitchNode:public GroupNode{
public:
  SwitchNode():GroupNode(), mCurrent(-1) { }
  virtual void accept(AbstractVisitor &aVisitor);
  void switchTo(unsigned aChildNr);
private:
  int mCurrent;
};
//-------------------------------------------------------//
/**** Shapes *****/
class SphereNode:public AbstractNode{
public:
  SphereNode(double aRadius, int aSlices = 16, int aStacks = 16, GLboolean aUseTexCoord=GL_FALSE);
  virtual void accept(AbstractVisitor &aVisitor);

  static GLUquadric* mQuadric;
  double mRadius;
  int mSlices;
  int mStacks;
  GLboolean mUseTexCoord;
};
//-------------------------------------------------------//
class LineNode:public AbstractNode{
public:
  LineNode(float aVert1X,
           float aVert1Y, 
           float aVert1Z, 
           float aVert2X, 
           float aVert2Y, 
           float aVert2Z, 
           float aWidth=1.0);
  virtual void accept(AbstractVisitor &aVisitor);

  float mVert1X;
  float mVert1Y;
  float mVert1Z;
  float mVert2X;
  float mVert2Y;
  float mVert2Z;
  float mWidth;
};
//-------------------------------------------------------//
/**** Transformations *****/
class TranslationNode:public AbstractNode{
public:
  TranslationNode(float aX, float aY, float aZ);
  virtual void accept(AbstractVisitor &aVisitor);

  float mX, mY, mZ;
};
//-------------------------------------------------------//
class RotationNode:public AbstractNode{
public:
  RotationNode(float aAngle, float aAxisX, float aAxisY, float aAxisZ);
  virtual void accept(AbstractVisitor &aVisitor);

  // aAngle in radians
  void setAngle(float aAngle);
  // return the angle in degrees
  inline float getAngle() { return mGradAngle; }
  inline float getRadAngle() { return (float)(mGradAngle * M_PI / 180.0f); }

  float mAxisX, mAxisY, mAxisZ;
  float mGradAngle; // degrees
};
//-------------------------------------------------------//
class ScaleNode:public AbstractNode{
public:
  ScaleNode(float aScaleX=1.0f, float aScaleY=1.0f, float aScaleZ=1.0f);
  virtual void accept(AbstractVisitor &aVisitor);

  float mScaleX, mScaleY, mScaleZ;
};
//-------------------------------------------------------//
/**** Timed transformations *****/
class RotorNode:public RotationNode, public ClockListener{
public: 
  RotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, Clock* aClock=NULL);
  virtual void accept(AbstractVisitor &aVisitor);
  virtual void update(float aDt, double aTime);

  float mAngleVel;
};

//-------------------------------------------------------//
/**** Properties ****/
class LightNode:public AbstractNode{
public:
  LightNode(GLenum aLightNr);
  virtual ~LightNode();
  void setParam(GLenum aParamType, float aA, float aB, float aC, float aD);
  virtual void accept(AbstractVisitor &aVisitor);
  void setPos();
private:
  GLenum mLightNr;
  float* mPos;
};
//-------------------------------------------------------//
class MaterialNode:public AbstractNode{
public:
  MaterialNode(GLenum aFace);
  virtual ~MaterialNode();
  virtual void accept(AbstractVisitor &aVisitor);
  void setParam(GLenum aParamName, float aV1, float aV2, float aV3, float aV4);

  std::map<GLenum, float*> mParams;
  GLenum mFace;
};
//-------------------------------------------------------//
class ColorNode:public AbstractNode{
public: 
  ColorNode(float aRed=1.0f, float aGreen=1.0f, float aBlue=1.0f);
  virtual ~ColorNode() { }
  virtual void accept(AbstractVisitor &aVisitor);

  float mRed;
  float mGreen;
  float mBlue;
};
//-------------------------------------------------------//
class TextureNode:public AbstractNode{
public:
  TextureNode(GLint aTexID, GLenum aTarget=GL_TEXTURE_2D);
  virtual ~TextureNode() { }
  virtual void accept(AbstractVisitor &aVisitor);

  GLint mTexID;
  GLenum mTarget;
};
//-------------------------------------------------------//
class ShadowNode:public AbstractNode{
public:
  ShadowNode(float* aLightPos, float* aNormal, float* aPointInPlane, float* aColor);
  virtual ~ShadowNode();
  virtual void accept(AbstractVisitor &aVisitor);
  void setNodeToShadow(AbstractNode* aNode);
  AbstractNode* getNodeToShadow(){ return mNode; }

  void draw(AbstractVisitor &aVisitor);

private:
  void buildShadowMatrix(float* shadowMatrix, float* lightPos, float* normal, float* p);
  AbstractNode* mNode;
  float* mLightPos;
  float* mNormal;
  float* mPointInPlane;
  float* mColor;
};
//-------------------------------------------------------//
class StarsNode:public AbstractNode{
public:
  StarsNode(float aRadiusMin, float aDeltaR, unsigned aNumStars);
  virtual ~StarsNode() { delete[] mVertices; }
  virtual void accept(AbstractVisitor &aVisitor);

  float mRadiusMin;
  float mDeltaR;
  unsigned mNumStars;
  float* mVertices;
};
//-------------------------------------------------------//

class RingNode:public AbstractNode{
public:
  RingNode(float fOuterRadius, float fInnerRadius, unsigned iQuadCount);
  virtual ~RingNode();
  virtual void accept(AbstractVisitor &aVisitor);

  float** mVertices;
  float mOuterRadius;
  float mInnerRadius;
  unsigned mQuadCount;
  int mVertexCount;

};

//-------------------------------------------------------//
class ActionBase:public GroupNode{
  inline virtual void accept(AbstractVisitor &aVisitor);
  inline void fire() { if(isEnabled()){ apply(); } }
  virtual void apply() = 0; // action specific code goes here
  inline void enable() { mEnabled = true; }
  inline void disable() { mEnabled = false; }
  inline bool isEnabled() { return mEnabled; }
private:
  bool mEnabled;
};
//-------------------------------------------------------//
//-------------------------------------------------------//

#endif
