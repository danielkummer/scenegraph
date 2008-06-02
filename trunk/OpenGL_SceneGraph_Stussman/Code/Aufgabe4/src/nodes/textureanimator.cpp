#include "nodes/textureanimator.h"

//----------------------------------------------------------//
TextureAnimator::TextureAnimator(unsigned aNumFrames, 
                                 unsigned* aFrames, 
                                 GLenum aSFactor, 
                                 GLenum aDFactor, 
                                 GLenum aTarget,                  
                                 float aFPS, 
                                 Clock* aClock):
mNumFrames(aNumFrames), 
mFramePeriod(1.0f/aFPS), 
mNextTime(0.0), 
mCurIdx(0),
TextureNode(aFrames[0], aSFactor, aDFactor, aTarget) 
{
  if(NULL != aClock){
    mClock = aClock;
  }else{
    mClock = Clock::getDefaultClock();
  }
  mClock->addListener(this);
  mFrames = new unsigned[mNumFrames];
  for(unsigned i=0; i<mNumFrames; i++){
    mFrames[i] = aFrames[i];
  }
}
//----------------------------------------------------------//
TextureAnimator::~TextureAnimator(){
	mClock->removeListener(this);
  delete[] mFrames;
}
//----------------------------------------------------------//
void TextureAnimator::accept(AbstractVisitor& aVisitor){
  mTexID = mFrames[mCurIdx];
  aVisitor.visit(*this);
}
//----------------------------------------------------------//
void TextureAnimator::update(float dt, double time){
  if(time >= mNextTime){
    mNextTime += mFramePeriod;
    mCurIdx += 1;
    if(mCurIdx >= mNumFrames){
      mCurIdx = 0;
    }
  }
}
//----------------------------------------------------------//
