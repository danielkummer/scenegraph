#ifndef _H_TEXTUREANIMATOR_
#define _H_TEXTUREANIMATOR_

#include "nodes/texturenode.h"
#include "clock.h"


class TextureAnimator:public TextureNode, public ClockListener{
public:
  TextureAnimator(unsigned aNumFrames, 
                  unsigned* aFrames, 
                  GLenum aSFactor, 
                  GLenum aDFactor, 
                  GLenum aTarget=GL_TEXTURE_2D,                  
                  float aFPS=30.0f, 
                  Clock* aClock=NULL);
  virtual ~TextureAnimator();

  virtual void update(float dt, double time);
  virtual void accept(AbstractVisitor& aVisitor);

private:
  Clock* mClock;
  float mFramePeriod;
  unsigned mNumFrames;
  unsigned* mFrames;
  double mNextTime;
  unsigned mCurIdx;


};




#endif // _H_TEXTUREANIMATOR_

