#include "nodes/nodes.h"
#include "visitors/visitors.h"


//-------------------------------------------------------//
AbstractNode::AbstractNode():mID(getID()),mRefCount(0){
}
//-------------------------------------------------------//
AbstractNode::~AbstractNode(){
}
//-------------------------------------------------------//
void AbstractNode::ref(){
  mRefCount++;
}
//-------------------------------------------------------//
void AbstractNode::unref(){
  mRefCount--;
  if(mRefCount <= 0){
    delete this;
  }
}
//-------------------------------------------------------//
unsigned int AbstractNode::getID(){
  mIDCount += 1;
  return mIDCount;
}
//-------------------------------------------------------//
unsigned AbstractNode::mIDCount = 0;
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
GroupNode::~GroupNode(){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->unref();
  }
  mChildren.clear();
}
//-------------------------------------------------------//
void GroupNode::add(AbstractNode* aNode){
  aNode->ref();
  mChildren.push_back(aNode);
}
//-------------------------------------------------------//
void GroupNode::remove(AbstractNode* aNode){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    if(*vItr == aNode){
      aNode->unref();
      vItr = mChildren.erase(vItr);
      break;
    }
  }
}
//-------------------------------------------------------//
void GroupNode::clear(){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->unref();
  }
  mChildren.clear();
}
//-------------------------------------------------------//
inline void GroupNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  visitChildren(aVisitor);
  aVisitor.postvisit(*this);
}
//-------------------------------------------------------//
void GroupNode::visitChildren(AbstractVisitor &aVisitor){
  std::vector<AbstractNode*>::iterator vItr;
  for(vItr = mChildren.begin(); vItr < mChildren.end(); vItr++){
    (*vItr)->accept(aVisitor);
  }
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void TransformSeparator::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  glPushMatrix();
  TransformSeparator::visitChildren(aVisitor);
  glPopMatrix();
  aVisitor.postvisit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
ToggleNode::ToggleNode():GroupNode(), mState(false){
}
//-------------------------------------------------------//

ToggleNode::~ToggleNode(){
}
//-------------------------------------------------------//
bool ToggleNode::isOn(){
  return mState;
}
//-------------------------------------------------------//

void ToggleNode::on(){ 
  mState = true; 
}

//-------------------------------------------------------//
void ToggleNode::off(){ 
  mState = false; 
}
//-------------------------------------------------------//
bool ToggleNode::toggle(){
  if(true == mState){
    mState = false;
  }else{
    mState = true;
  }
  return mState;
}

//-------------------------------------------------------//
void ToggleNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  if(true == mState){
    ToggleNode::visitChildren(aVisitor);
  }
  aVisitor.postvisit(*this);
}

//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
void SwitchNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  if(mCurrent >= 0 && mCurrent<(int)mChildren.size()){
    mChildren[mCurrent]->accept(aVisitor);
  }
  aVisitor.postvisit(*this);
}
//-------------------------------------------------------//
Separator::Separator() { }
Separator::~Separator() { }
void Separator::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void SwitchNode::switchTo(unsigned int aChildNr){
  if(aChildNr >= 0 && aChildNr <(unsigned)mChildren.size()){
    mCurrent = aChildNr;
  }else{
    mCurrent = -1;
  }
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
SphereNode::SphereNode(double aRadius, int aSlice, int aStacks, GLboolean aUseTexCoord):AbstractNode(){
  mRadius = aRadius;
  mSlices = aSlice;
  mStacks = aStacks;
  mUseTexCoord = aUseTexCoord;
}
//-------------------------------------------------------//
GLUquadric* SphereNode::mQuadric = gluNewQuadric();
//-------------------------------------------------------//
inline void SphereNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
LineNode::LineNode(float aVert1X,
                   float aVert1Y, 
                   float aVert1Z, 
                   float aVert2X, 
                   float aVert2Y, 
                   float aVert2Z, 
                   float aWidth):
mVert1X(aVert1X),
mVert1Y(aVert1Y),
mVert1Z(aVert1Z),
mVert2X(aVert2X),
mVert2Y(aVert2Y),
mVert2Z(aVert2Z),
mWidth(aWidth){
}
//-------------------------------------------------------//
inline void LineNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
TranslationNode::TranslationNode(float aX, float aY, float aZ):
AbstractNode(){
  mX = aX;
  mY = aY;
  mZ = aZ;
}
//-------------------------------------------------------//
inline void TranslationNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
RotationNode::RotationNode(float aAngle, float aAxisX, float aAxisY, float aAxisZ):
AbstractNode(){
  mAxisX = aAxisX;
  mAxisY = aAxisY;
  mAxisZ = aAxisZ;
  setAngle(aAngle);
}
//-------------------------------------------------------//
void RotationNode::setAngle(float aAngle){
  mGradAngle = aAngle;
}
//-------------------------------------------------------//
inline void RotationNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
ScaleNode::ScaleNode(float aScaleX, float aScaleY, float aScaleZ):
mScaleX(aScaleX), mScaleY(aScaleY), mScaleZ(aScaleZ){
}
//-------------------------------------------------------//
inline void ScaleNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
/*********************************************************/
//-------------------------------------------------------//
RotorNode::RotorNode(float aAngleVel, float aAngle, float aAxisX, float aAxisY, float aAxisZ, Clock* aClock):
RotationNode(aAngle, aAxisX, aAxisY, aAxisZ), ClockListener()
{
  if(NULL != aClock){
    aClock->addListener(this);
  }else{
    Clock::getDefaultClock()->addListener(this);
  }
  mAngleVel = aAngleVel;
}
//-------------------------------------------------------//
inline void RotorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void RotorNode::update(float aDt, double aTime){
  mGradAngle += (mAngleVel * aDt);
  if(mGradAngle > 360.0f){
    mGradAngle -= 360.0f;
  }
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
LightNode::LightNode(GLenum aLightNr){
  mLightNr = aLightNr;
  mPos = new float[4];
}
//-------------------------------------------------------//
LightNode::~LightNode(){
  delete[] mPos;
}
//-------------------------------------------------------//
void LightNode::setParam(GLenum aParamType, float aA, float aB, float aC, float aD){
  float vValues[] = {aA, aB, aC, aD};
  if(GL_POSITION){
    mPos[0] = aA;
    mPos[1] = aB;
    mPos[2] = aC;
    mPos[3] = aD;
  }
  glLightfv(mLightNr, aParamType, vValues);
}
//-------------------------------------------------------//
inline void LightNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void LightNode::setPos(){
  glLightfv(mLightNr, GL_POSITION, mPos);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
MaterialNode::MaterialNode(GLenum aFace): mFace(aFace){
}
//-------------------------------------------------------//
MaterialNode::MaterialNode(GLenum aFace, Material* aMaterial){
    mFace = aFace;
    setParam(GL_AMBIENT, aMaterial->ambient);
	  setParam(GL_DIFFUSE, aMaterial->diffuse);
    setParam(GL_SPECULAR, aMaterial->specular);
    setParam(GL_EMISSION, aMaterial->emission);
    setParam(GL_SHININESS, aMaterial->shininess);
}
//-------------------------------------------------------//
MaterialNode::~MaterialNode(){
  std::map<GLenum, float*>::const_iterator vItr;
  for(vItr=mParams.begin(); vItr != mParams.end(); vItr++){
    delete[] (vItr->second);
  }
  mParams.clear();
}
//-------------------------------------------------------//
inline void MaterialNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void MaterialNode::setParam(GLenum aParamName, float aV1, float aV2, float aV3, float aV4){
  float* vParams = new float[4];
  vParams[0] = aV1;
  vParams[1] = aV2;
  vParams[2] = aV3;
  vParams[3] = aV4;
  std::map<GLenum, float*>::iterator vRes = mParams.find(aParamName);
  if(vRes != mParams.end()){
    delete[] vRes->second;
  }
  mParams[aParamName] = vParams;
}
//-------------------------------------------------------//
void MaterialNode::setParam(GLenum aParamName, float* aValues3){
  assert(NULL != aValues3);
  setParam(aParamName, aValues3[0], aValues3[1], aValues3[2], 0.0f);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
ColorNode::ColorNode(float aRed, float aGreen, float aBlue):
mRed(aRed), mGreen(aGreen), mBlue(aBlue){
}
//-------------------------------------------------------//
//-------------------------------------------------------//
inline void ColorNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
TextureNode::TextureNode(GLint aTexID, GLenum aTarget, bool aBlend):
mTexID(aTexID), mTarget(aTarget), mBlending(aBlend){
}
//-------------------------------------------------------//
inline void TextureNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
ShadowNode::ShadowNode(float* aLightPos, float* aNormal, float* aPointInPlane, float* aColor):
mNode(NULL), mLightPos(aLightPos), mNormal(aNormal), mPointInPlane(aPointInPlane), mColor(aColor)
{
  mLightPos = new float[3];
  mLightPos[0] = aLightPos[0];
  mLightPos[1] = aLightPos[1];
  mLightPos[2] = aLightPos[2];

  mNormal = new float[3];
  mNormal[0] = aNormal[0];
  mNormal[1] = aNormal[1];
  mNormal[2] = aNormal[2];

  mPointInPlane = new float[3];
  mPointInPlane[0] = aPointInPlane[0];
  mPointInPlane[1] = aPointInPlane[1];
  mPointInPlane[2] = aPointInPlane[2];

  mColor = new float[3];
  mColor[0] = aColor[0];
  mColor[1] = aColor[1];
  mColor[2] = aColor[2];
}
//-------------------------------------------------------//
ShadowNode::~ShadowNode(){
  if(mNode != NULL){
    mNode->unref();
  }
  mNode = NULL;
  delete[] mLightPos;
  delete[] mNormal;
  delete[] mPointInPlane;
  delete[] mColor;
}
//-------------------------------------------------------//
void ShadowNode::setNodeToShadow(AbstractNode* aNode){
  if(mNode != NULL){
    mNode->unref();
  }
  mNode = aNode; 
  mNode->ref();
}

//-------------------------------------------------------//
inline void ShadowNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
void ShadowNode::draw(AbstractVisitor &aVisitor){
  if(NULL != mNode){
    float shadowMatrix[16];
    buildShadowMatrix(shadowMatrix, mLightPos, mNormal, mPointInPlane);

  //    glDisable(GL_DEPTH_TEST);							// Disable depth test to see the shadow also from below
    glDisable(GL_LIGHTING);								// Disable light effects
    glColor3fv(mColor);						// Shadow's color
	  glPolygonMode(GL_FRONT, GL_FILL);
    glPushMatrix();
      glMultMatrixf(shadowMatrix);
      mNode->accept(aVisitor);
    glPopMatrix();
	  glEnable(GL_DEPTH_TEST);							// Enable depth test to sea the shadow also from below
    glEnable(GL_LIGHTING);								// Enable light effects
	  glDisable(GL_BLEND);								// Disable blending
  }
}
//-------------------------------------------------------//
void ShadowNode::buildShadowMatrix(float* shadowMatrix, float* lightPos, float* normal, float* p){
    float d = normal[0]*lightPos[0] + normal[1]*lightPos[1] + normal[2]*lightPos[2];
	  float c = p[0]*normal[0] + p[1]*normal[1] + p[2]*normal[2] - d; 
	
    shadowMatrix[0]  = c + lightPos[0] * normal[0];	    // First row
    shadowMatrix[4]  =	   lightPos[0] * normal[1];
    shadowMatrix[8]  =	   lightPos[0] * normal[2];
    shadowMatrix[12] =	  -lightPos[0] * (c+d);
	
    shadowMatrix[1]  =	   lightPos[1] * normal[0];		// Second row
    shadowMatrix[5]  = c + lightPos[1] * normal[1];
    shadowMatrix[9]  =	   lightPos[1] * normal[2];
    shadowMatrix[13] =	  -lightPos[1] * (c+d);
	
    shadowMatrix[2]  =	   lightPos[2] * normal[0];		// Third row
    shadowMatrix[6]  =	   lightPos[2] * normal[1];
    shadowMatrix[10] = c + lightPos[2] * normal[2];
    shadowMatrix[14] =	  -lightPos[2] * (c+d);
	
    shadowMatrix[3]  = normal[0];		// Fourth row
    shadowMatrix[7]  = normal[1];
    shadowMatrix[11] = normal[2];
    shadowMatrix[15] = -d;
  	for (int i=0;i<16;i++) shadowMatrix[i] /= shadowMatrix[15];
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
inline float randf(){
  return float(rand()/(float)RAND_MAX);
}
//-------------------------------------------------------//
StarsNode::StarsNode(float aRadiusMin, float aDeltaR, unsigned aNumStars):
mRadiusMin(aRadiusMin), mDeltaR(aDeltaR), mNumStars(aNumStars)
{ 
  mVertices = new float[3*aNumStars];
  float vRadius;
  float x, y, z;
  float alpha;
  float beta;
  for(unsigned i=0; i<mNumStars; i++){
    vRadius = mRadiusMin + mDeltaR * randf();
    alpha = 2 *  (float)M_PI * randf();
    beta = 2 * (float)M_PI * (randf() - 0.5f);
    x = vRadius;
    y = 0.0f;
    z = 0.0f;

    x = vRadius * cos(alpha);// + y * sin(alpha);
    y = vRadius * sin(alpha);// + y * cos(alpha);

    float tx = x * cos(beta);
    float tz = x * sin(beta);
    mVertices[3 * i] = tx;
    mVertices[3 * i + 1] = y;
    mVertices[3 * i + 2] = tz;
  }
}

inline void StarsNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}

//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
RingNode::RingNode(float fOuterRadius, float fInnerRadius, unsigned iQuadCount){
  mOuterRadius = fOuterRadius;
  mInnerRadius = fInnerRadius;
  mQuadCount = iQuadCount;   
  mVertexCount = iQuadCount * 2; //2 vertices overlap on edges -> re-use
 
  float phi = 2*(float)M_PI / (float)mQuadCount;
 
  //init vertices
  mVertices = new float*[mVertexCount];   
  for(int i = 0; i < mVertexCount ; i++) {
      mVertices[i] = new float[3];   
  }
 
  //calculate vertices
  for(int i = 0; i < mVertexCount / 2 ; i++) {
      //inner vertex
      mVertices[i][0] = mInnerRadius*cos(i*phi);
      mVertices[i][1] = 0;
      mVertices[i][2] = -mInnerRadius*sin(i*phi);                       
  }
  for(int i = mVertexCount / 2 ; i < mVertexCount ; i++) {
      //outer vertex
      mVertices[i][0] = mOuterRadius*cos(i*phi);
      mVertices[i][1] = 0;
      mVertices[i][2] = -mOuterRadius*sin(i*phi);                       
  }     
}

//-------------------------------------------------------//
void RingNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
RingNode::~RingNode(){
  for(int i=0; i<mVertexCount; i++){
    delete[] mVertices[i];
  }
  delete[] mVertices;
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//



