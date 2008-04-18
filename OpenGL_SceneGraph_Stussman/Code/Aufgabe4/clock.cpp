#include "clock.h"


Clock* Clock::mDefaultClock = NULL;
//-------------------------------------------------------//
void Clock::tick(){
  int now = SDL_GetTicks();
  double dt = (now - mOldNow) * mDilatation * 0.001f;
  mOldNow = now;

  mTime += dt;
  if(dt > 100){
     dt = 100.0f;
  }

  std::vector<ClockListener*>::iterator vItr;
  for(vItr = mListeners.begin(); vItr < mListeners.end(); vItr++){
    (*vItr)->update((float)dt, mTime);
  }
}
//-------------------------------------------------------//
void Clock::setDilatation(float aFactor){
  mDilatation = aFactor;
}
//-------------------------------------------------------//
float Clock::getDilatation(){
  return mDilatation;
}
//-------------------------------------------------------//
void Clock::addListener(ClockListener* aListener){
  mListeners.push_back(aListener);
}
//-------------------------------------------------------//
void Clock::removeListener(ClockListener* aListener){
  std::vector<ClockListener*>::iterator vItr;
  for(vItr = mListeners.begin(); vItr < mListeners.end(); vItr++){
    if((*vItr) == aListener){
      mListeners.erase(vItr);
      break;
    }
  }
}
//-------------------------------------------------------//
Clock* Clock::getDefaultClock(){
  if(mDefaultClock==NULL){
    mDefaultClock = new Clock();
  }
  return mDefaultClock;
}
//-------------------------------------------------------//
Clock::~Clock(){ 
}
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//
//-------------------------------------------------------//
/*********************************************************/
//-------------------------------------------------------//


